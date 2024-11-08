#include <fcntl.h>
#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/file.h"
#include "../include/http.h"

static ssize_t file_reader(void *cls, uint64_t pos, char *buf, size_t max) {
  FILE *file = cls;

  (void)fseek(file, pos, SEEK_SET);
  return fread(buf, 1, max, file);
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

  response = MHD_create_response_from_callback(
      stat_buf.st_size, 32 * 1024, &file_reader, file, &file_free_callback);
  mime = get_mime(path);
  MHD_add_response_header(response, "Content-Type", mime);

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

int main(int argc, char **argv) {
  struct MHD_Daemon *daemon;

  int port = atoi(argv[1]);
  if (argc != 2 || port == 0) {
    printf("USAGE: %s [PORT] :3\n", argv[0]);
    return -1;
  }

  daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, port, NULL, NULL,
                            &callback, NULL, MHD_OPTION_END);
  if (daemon == NULL)
    return -1;

  printf("libmicrohttpd: running on localhost port %d c:\n", port);
  puts("CTRL-C to exit");

  // Will implement logging through this maybe sooner or later somehow :3
  while (1)
    ;

  printf("Exiting gracefully c:\n");
  MHD_stop_daemon(daemon);
  return 0;
}
