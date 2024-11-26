#include <magic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../include/file.h"

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
    return NULL;

  if (getcwd(cwd, 1024) == NULL) {
    free(cwd);
    perror("getcwd");
    return NULL;
  }

  return cwd;
}

int make_dir(char *path) {
  if (mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
    perror("Failed to create directory");
    return -1;
  }
  return 0;
}

bool path_exist(char *path) {
  struct stat sb;
  return (stat(path, &sb) == 0);
}

int read_file(char *path, char **buf, size_t *file_len) { return 0; }
