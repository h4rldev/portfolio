#include "../../include/file.h"
#include <magic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_mime(char *path) {
  char *mime = (char *)malloc(1024);

  magic_t magic = magic_open(MAGIC_MIME_TYPE);
  magic_load(magic, NULL);

  char *mime_type = (char *)magic_file(magic, path);
  if (strncmp(mime_type, "image/vnd.microsoft.icon", 24) == 0)
    mime_type = "image/x-icon";

  strlcpy(mime, mime_type, 1024);

  magic_close(magic);
  return mime;
}

char *get_cwd(void) {
  char *cwd = malloc(1024);
  if (!cwd)
    return 0;

  if (getcwd(cwd, 1024) == NULL) {
    perror("getcwd");
    return 0;
  }

  return cwd;
}
