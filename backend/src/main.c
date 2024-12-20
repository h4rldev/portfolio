#include <arpa/inet.h>
#include <fcntl.h>
#include <gcrypt.h>
#include <gnutls/gnutls.h>
#include <microhttpd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "../include/cli.h"
#include "../include/compress.h"
#include "../include/config.h"
#include "../include/file.h"
#include "../include/http.h"
#include "../include/log.h"
#include "../include/meta.h"
#include "../include/ssl.h"

struct tm start_date;

void init_start_date() {
  time_t now = time(NULL);
  localtime_r(&now, &start_date);
}

static ssize_t file_reader(void *cls, uint64_t pos, char *buf, size_t max) {
  FILE *file = cls;
  if (file == NULL)
    return -1;

  (void)fseek(file, pos, SEEK_SET);
  size_t length_read = fread(buf, 1, max, file);
  if (length_read != max) {
    flscio_log(Error, "amount read is more or less than file_size, quitting");
    return -2;
  }

  return length_read;
}

static char *compress_file(FILE *file, size_t file_size,
                           size_t *compressed_size) {
  char *file_content = read_file_from_fd(file);
  if (!file_content)
    return NULL;

  char *buf = compress_gzip(file_content, file_size, compressed_size);
  free(file_content);
  fclose(file);

  return buf;
}

static void file_free_callback(void *cls) {
  FILE *file = cls;
  fclose(file);
}

static char *get_connection_info(struct MHD_Connection *connection,
                                 uint16_t *client_port) {
  const union MHD_ConnectionInfo *ci =
      MHD_get_connection_info(connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS);

  char *flscio_client_ip = (char *)malloc(INET_ADDRSTRLEN);

  if (ci && ci->client_addr) {
    strlcpy(flscio_client_ip,
            inet_ntoa(((struct sockaddr_in *)ci->client_addr)->sin_addr),
            INET_ADDRSTRLEN);
    *client_port = ((struct sockaddr_in *)ci->client_addr)->sin_port;
  } else {
    strlcpy(flscio_client_ip, "Unknown", INET_ADDRSTRLEN);
    *client_port = 0;
  }

  return flscio_client_ip;
}

static enum MHD_Result callback(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **ptr) {
  char *path;
  char *mime;
  FILE *file;

  struct stat stat_buf;
  static int dummy;
  struct MHD_Response *response;
  int ret;

  uint16_t flscio_client_port = 0;
  Config *config = (Config *)cls;

  // Get connection info for logging
  char *flscio_client_ip = get_connection_info(connection, &flscio_client_port);
  flscio_log(Info, "%s:%u %s\n", flscio_client_ip, flscio_client_port, url);
  free(flscio_client_ip);

  // unexpected method
  if (strncmp(method, "GET", 3) != 0)
    return MHD_NO;

  if (&dummy != *ptr) {
    // The first time only the headers are valid,
    // do not respond in the first round...
    *ptr = &dummy;
    return MHD_YES;
  }

  // upload data in a GET!?
  if (*upload_data_size != 0) {
    char *flscio_client_ip =
        get_connection_info(connection, &flscio_client_port);
    flscio_log(Error, "%s:%u tried to upload data to: %s", flscio_client_ip,
               flscio_client_port, url);
    free(flscio_client_ip);
    return MHD_NO;
  }

  // clear context pointer
  *ptr = NULL;

  // Get path for file by routing c:
  path = route(url);
  if (!path) {
    // api route likely
    size_t api_len = 0;
    char *api_resp = get_api_resp(url, start_date, &api_len);

    response = MHD_create_response_from_buffer_copy(api_len, api_resp);

    MHD_add_response_header(response, "Content-Type", "application/json");
    free(api_resp);

    if (response == NULL)
      return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
  }

  mime = get_mime(path);

  if ((stat(path, &stat_buf) == 0) && (S_ISREG(stat_buf.st_mode)))
    file = fopen(path, "rb");
  else
    file = NULL;

  if (file == NULL) {
    free(path);
    return MHD_NO;
  }

  if (config->compress == true && strncmp(mime, "text", 4) == 0 &&
      test_compress_file(file) == true) {
    size_t compressed_size = 0;

    char *buf = compress_file(file, stat_buf.st_size, &compressed_size);
    if (!buf) {
      free(path);
      return MHD_NO;
    }

    response = MHD_create_response_from_buffer_copy(compressed_size, buf);
    MHD_add_response_header(response, "Content-Encoding", "gzip");
    free(buf);
  } else {
    response = MHD_create_response_from_callback(
        stat_buf.st_size, 32 * 1024, &file_reader, file, &file_free_callback);
  }

  MHD_add_response_header(response, "Content-Type", mime);
  MHD_add_response_header(response, "Cache-Control", "max-age=604800");
  MHD_add_response_header(response, "Server", __NAME__);

  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  free(mime);
  free(path);

  if (response == NULL) {
    return MHD_NO;
  }

  return ret;
}

void signal_handler(int sig) { return; }

int main(int argc, char **argv) {
  struct MHD_Daemon *daemon;
  Config config;
  char *key;
  char *cert;

  if (read_config(&config) != 0) {
    init_config(&config);
    write_config(&config);
  }

  if (parse_args(&argc, &argv, &config) != 0) {
    fprintf(stderr, "%s: failed parsing args, something is very wrong..\n",
            argv[0]);
    return -1;
  }

  unsigned int port = config.port;
  bool ssl = config.ssl.ssl;

  if (ssl == true) {
    gcry_control(GCRYCTL_ENABLE_QUICK_RANDOM, 0);

    key = get_key();
    cert = get_cert();

    if (!key || !cert)
      return -1;

    daemon = MHD_start_daemon(
        MHD_USE_AUTO_INTERNAL_THREAD | MHD_USE_TLS | MHD_USE_TURBO, port, NULL,
        NULL, &callback, &config, MHD_OPTION_CONNECTION_TIMEOUT, 256,
        MHD_OPTION_HTTPS_MEM_KEY, key, MHD_OPTION_HTTPS_MEM_CERT, cert,
        MHD_OPTION_END);
  } else {
    daemon = MHD_start_daemon(
        MHD_USE_AUTO_INTERNAL_THREAD | MHD_USE_TURBO, port, NULL, NULL,
        &callback, &config, MHD_OPTION_CONNECTION_TIMEOUT, 256, MHD_OPTION_END);
  }
  if (daemon == NULL)
    return -1;

  init_start_date();

  printf("libmicrohttpd: running on localhost port %d c:\n", port);
  puts("CTRL-C to exit\n");

  // Will implement logging through this maybe sooner or later somehow :3
  signal(SIGINT, signal_handler);
  pause();

  puts("\nExiting gracefully c:");
  MHD_stop_daemon(daemon);

  if (ssl == true) {
    free(key);
    free(cert);
  }

  free_config(&config);
  return 0;
}
