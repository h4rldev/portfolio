#include <magic.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../include/file.h"
#include "../../include/log.h"

char *get_mime(char *path) {
  char *mime = (char *)malloc(1024);

  regex_t regex_js;
  regex_t regex_css;

  regcomp(&regex_js, "^.*\\.(js)$", REG_EXTENDED);
  regcomp(&regex_css, "^.*\\.(css)$", REG_EXTENDED);

  magic_t magic = magic_open(MAGIC_MIME_TYPE);
  magic_load(magic, NULL);

  char *mime_type = (char *)magic_file(magic, path);
  if (strncmp(mime_type, "image/vnd.microsoft.icon", 24) == 0)
    mime_type = "image/x-icon";
  else if (regexec(&regex_js, path, 0, NULL, 0) == 0)
    mime_type = "text/javascript";
  else if (regexec(&regex_css, path, 0, NULL, 0) == 0)
    mime_type = "text/css";

  strlcpy(mime, mime_type, 1024);

  regfree(&regex_css);
  regfree(&regex_js);
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
    flscio_log(Error, "Failed to create directory");
    return -1;
  }
  return 0;
}

bool path_exist(char *path) {
  struct stat sb;
  return (stat(path, &sb) == 0);
}

char *read_file(char *path) {
  size_t file_size = 0;
  FILE *fp = fopen(path, "r");

  if (!fp)
    return NULL;

  (void)fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  (void)fseek(fp, 0L, SEEK_SET);

  char *buf = (char *)malloc(file_size + 1);

  size_t amount_read = fread(buf, 1, file_size + 1, fp);
  if (file_size != amount_read) {
    flscio_log(Error, "Amount read is more or less than file_size, quitting");
    free(buf);
    return NULL;
  }

  return buf;
}
