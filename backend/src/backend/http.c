#include "../../include/http.h"
#include "../../include/file.h"

#include <magic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int populate_mime(char *path, char mime[], size_t mime_len) {
  magic_t magic = magic_open(MAGIC_MIME_TYPE);
  magic_load(magic, NULL);

  char *mime_type = (char *)magic_file(magic, path);
  if (strncmp(mime_type, "image/vnd.microsoft.icon", 24) == 0)
    mime_type = "image/x-icon";
  printf("mime_type for path %s is: %s\n", path, mime_type);

  strlcpy(mime, mime_type, mime_len);

  magic_close(magic);
  return 0;
}

Pages get_page_enum(char *route) {
  if (strlen(route) == 1)
    return Index;

  if (strlen(route) > 1)
    return Asset;

  return NotFound;
}

static char *get_asset(char *route, char mime[], size_t mime_len) {
  char path[1024] = {0};
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  populate_mime(path, mime, mime_len);

  char *asset_content = read_file(path);
  if (asset_content == NULL)
    return 0;
  return asset_content;
}

static char *get_page(Pages page) {
  char path[1024] = {0};
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site", cwd);
  free(cwd);

  switch (page) {
  case Index:
    strlcat(path, "/index.html", 1024);
    break;
  case NotFound:
    strlcat(path, "/not-found.html", 1024);
    break;
  case Asset:
    fprintf(stderr, "Invalid use of get_page c:\n");
    return 0;
  }

  char *page_content = read_file(path);
  if (page_content == NULL)
    return 0;
  return page_content;
}

char *route(char *route, char mime[], size_t mime_len) {
  Pages page_type = get_page_enum(route);
  char *returnable;

  if (page_type != Asset) {
    returnable = get_page(page_type);
    strlcpy(mime, "text/html", mime_len);
    return returnable;
  }

  returnable = get_asset(route, mime, mime_len);
  return returnable;
}
