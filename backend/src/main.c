#include <fcntl.h>
#include <microhttpd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/cli.h"
#include "../include/compress.h"
#include "../include/config.h"
#include "../include/file.h"
#include "../include/http.h"
#include "../include/meta.h"
#include "../include/ssl.h"

static ssize_t file_reader(void *cls, uint64_t pos, char *buf, size_t max) {
  FILE *file = cls;

  (void)fseek(file, pos, SEEK_SET);
  return fread(buf, 1, max, file);
}

static ssize_t file_reader_compress(void *cls, uint64_t pos, char *buf,
                                    size_t max) {
  FILE *file = cls;
  size_t new_size;
  Config config;
  read_config(&config);

  char *compressed_buf;

  (void)fseek(file, pos, SEEK_SET);
  size_t ret_code = fread(buf, 1, max, file);
  if (ret_code != max) {
    if (feof(file)) {
      fprintf(stderr, "Error reading file: unexpected end of file\n");
      return ret_code;
    } else if (ferror(file)) {
      perror("Error reading file");
      return ret_code;
    }
  }

  compressed_buf = compress_gzip(buf, ret_code, &new_size);
  if (!compressed_buf) {
    fprintf(stderr, "Failed to compress entirely..\n");
    return ret_code;
  }

  memcpy(buf, compressed_buf, new_size);
  free(compressed_buf);

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
  FILE *file;

  struct stat stat_buf;
  static int dummy;
  struct MHD_Response *response;
  int ret;

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
  if (*upload_data_size != 0)
    return MHD_NO;

  // clear context pointer
  *ptr = NULL;

  // Get path for file by routing c:
  path = route((char *)url);

  if ((stat(path, &stat_buf) == 0) && (S_ISREG(stat_buf.st_mode)))
    file = fopen(path, "rb+");
  else
    file = NULL;

  if (file == NULL) {
    free(path);
    return MHD_NO;
  }

  mime = get_mime(path);

  if (config.compress == true) {
    if (strncmp(mime, "text", 4) == 0) {
      response = MHD_create_response_from_callback(stat_buf.st_size, 32 * 1024,
                                                   &file_reader_compress, file,
                                                   &file_free_callback);
      MHD_add_response_header(response, "Content-Encoding", "gzip");
    } else {
      response = MHD_create_response_from_callback(
          stat_buf.st_size, 32 * 1024, &file_reader, file, &file_free_callback);
    }
  } else {
    response = MHD_create_response_from_callback(
        stat_buf.st_size, 32 * 1024, &file_reader, file, &file_free_callback);
  }

  MHD_add_response_header(response, "Content-Type", mime);
  MHD_add_response_header(response, "Server", __NAME__);

  if (response == NULL) {
    fclose(file);
    free(mime);
    free(path);
    return MHD_NO;
  }

  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  free(path);
  free(mime);

  return ret;
}

void signal_handler(int sig) { return; }

int main(int argc, char **argv) {
  struct MHD_Daemon *daemon;
  Config config;

  if (read_config(&config) != 0) {
    init_config(&config);
    write_config(&config);
  }

  generate_key_pair();
  return -1;

  if (parse_args(&argc, &argv, &config) != 0) {
    fprintf(stderr, "%s: failed parsing args, something is very wrong..\n",
            argv[0]);
    return -1;
  }
  unsigned int port = config.port;
  bool ssl = config.ssl.ssl;

  daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, port, NULL, NULL,
                            &callback, NULL, MHD_OPTION_END);
  if (daemon == NULL)
    return -1;

  printf("libmicrohttpd: running on localhost port %d c:\n", port);
  puts("CTRL-C to exit");

  // Will implement logging through this maybe sooner or later somehow :3
  signal(SIGINT, signal_handler);
  pause();

  puts("\nExiting gracefully c:");
  MHD_stop_daemon(daemon);

  free_config(&config);

  return 0;
}
