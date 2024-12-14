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

#include "../include/api.h"
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

  (void)fseek(file, pos, SEEK_SET);
  size_t length_read = fread(buf, 1, max, file);
  return length_read;
}

static ssize_t file_reader_compress(void *cls, uint64_t pos, char *buf,
                                    size_t max) {
  FILE *file = cls;
  size_t new_size;

  char *compressed_buf;

  (void)fseek(file, pos, SEEK_SET);
  size_t ret_code = fread(buf, 1, max - 1, file);
  if (ret_code != max) {
    if (feof(file)) {
      fprintf(stderr, "Error reading file: unexpected end of file\n");
      return ret_code;
    } else if (ferror(file)) {
      perror("Error reading file");
      return ret_code;
    }
  }

  if (ret_code > 100) {
    compressed_buf = compress_gzip(buf, ret_code, &new_size);
    if (!compressed_buf) {
      fprintf(stderr, "Failed to compress entirely..\n");
      return ret_code;
    }
    memcpy(buf, compressed_buf, new_size);
    free(compressed_buf);
  }

  return ret_code;
}

static void file_free_callback(void *cls) {
  FILE *file = cls;
  fclose(file);
}

static enum MHD_Result callback(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **ptr) {
  char *path;
  char *mime;
  char *api_resp;
  FILE *file;

  struct stat stat_buf;
  static int dummy;
  struct MHD_Response *response;
  int ret;

  const union MHD_ConnectionInfo *ci;
  struct sockaddr *client_addr;
  char client_ip[INET_ADDRSTRLEN];
  uint16_t client_port;

  ci = MHD_get_connection_info(connection, MHD_CONNECTION_INFO_CLIENT_ADDRESS);
  if (ci && ci->client_addr) {
    client_addr = ci->client_addr;
    struct sockaddr_in *addr = (struct sockaddr_in *)client_addr;
    inet_ntop(AF_INET, &addr->sin_addr, client_ip, INET_ADDRSTRLEN);
    client_port = ntohs(addr->sin_port);
  } else {
    strlcpy(client_ip, "Unknown", INET_ADDRSTRLEN);
    client_port = 0;
  }

  Config config;
  read_config(&config);

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
    flscio_log(Error, "%s:%lu tried to upload data to: %s", client_ip,
               client_port, url);
    return MHD_NO;
  }

  // clear context pointer
  *ptr = NULL;

  bool api_route = false;

  // Get path for file by routing c:
  path = route((char *)url);
  if (!path) {
    // api route likely
    api_route = true;
  }

  if (!api_route) {
    if ((stat(path, &stat_buf) == 0) && (S_ISREG(stat_buf.st_mode)))
      file = fopen(path, "rb");
    else
      file = NULL;

    if (file == NULL) {
      free(path);
      return MHD_NO;
    }

    mime = get_mime(path);

    if (config.compress == true) {
      if (strncmp(mime, "text", 4) == 0) {
        bool is_compressable = test_compress_file(file);

        response = MHD_create_response_from_callback(
            stat_buf.st_size, 32 * 1024, &file_reader_compress, file,
            &file_free_callback);

        if (is_compressable == true)
          MHD_add_response_header(response, "Content-Encoding", "gzip");

      } else {
        response = MHD_create_response_from_callback(stat_buf.st_size,
                                                     32 * 1024, &file_reader,
                                                     file, &file_free_callback);
      }
    } else {
      response = MHD_create_response_from_callback(
          stat_buf.st_size, 32 * 1024, &file_reader, file, &file_free_callback);
    }

    MHD_add_response_header(response, "Content-Type", mime);
  } else {
    size_t api_len = 0;
    api_resp = get_api_resp((char *)url, start_date, &api_len);
    response = MHD_create_response_from_buffer_copy(api_len, api_resp);
    MHD_add_response_header(response, "Content-Type", "application/json");
  }

  MHD_add_response_header(response, "Server", __NAME__);

  if (response == NULL) {
    if (!api_route) {
      fclose(file);
      free(mime);
      free(path);
    }
    return MHD_NO;
  }

  flscio_log(Info, "%s:%lu %s", client_ip, client_port, url);

  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  if (!api_route) {
    free(mime);
    free(path);
  }

  free_config(&config);
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
        MHD_USE_AUTO_INTERNAL_THREAD | MHD_USE_TLS | MHD_ALLOW_UPGRADE, port,
        NULL, NULL, &callback, NULL, MHD_OPTION_CONNECTION_TIMEOUT, 256,
        MHD_OPTION_HTTPS_MEM_KEY, key, MHD_OPTION_HTTPS_MEM_CERT, cert,
        MHD_OPTION_END);
  } else {
    daemon = MHD_start_daemon(MHD_USE_AUTO_INTERNAL_THREAD, port, NULL, NULL,
                              &callback, NULL, MHD_OPTION_CONNECTION_TIMEOUT,
                              256, MHD_OPTION_END);
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
