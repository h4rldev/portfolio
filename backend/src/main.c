#include <microhttpd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/http.h"

static enum MHD_Result callback(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **ptr) {
  char *page;
  char *mime = malloc(256);

  static int dummy;
  struct MHD_Response *response;
  int ret;

  if (strncmp(method, "GET", 3) != 0)
    return MHD_NO; /* unexpected method */
  if (&dummy != *ptr) {
    /* The first time only the headers are valid,
       do not respond in the first round... */
    *ptr = &dummy;
    return MHD_YES;
  }
  if (*upload_data_size != 0)
    return MHD_NO; /* upload data in a GET!? */

  *ptr = NULL; /* clear context pointer */

  page = route((char *)url, mime, 256);
  response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                             MHD_RESPMEM_MUST_COPY);
  MHD_add_response_header(response, "Content-Type", mime);
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);

  free(page);
  free(mime);

  return ret;
}

void signal_handler(int sig) {
  char character;

  signal(sig, SIG_IGN);
  printf("\nDo you really want to quit? [y/N]: ");
  character = getchar();
  if (character == 'y' || character == 'Y')
    return;
  else
    signal(SIGINT, signal_handler);
}

int main(int argc, char **argv) {
  struct MHD_Daemon *daemon;

  int port = atoi(argv[1]);
  if (argc != 2 || port == 0) {
    printf("USAGE: %s [PORT]\n", argv[0]);
    return -1;
  }

  daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, port, NULL, NULL,
                            &callback, NULL, MHD_OPTION_END);
  if (daemon == NULL)
    return -1;

  printf("libmicrohttpd: running on localhost port %d\n", port);
  puts("CTRL-C to exit");

  signal(SIGINT, signal_handler);
  pause();

  printf("Exiting gracefully c:\n");
  MHD_stop_daemon(daemon);
  return 0;
}
