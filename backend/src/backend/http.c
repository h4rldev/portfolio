#include "../../include/http.h"
#include "../../include/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static Pages get_page_enum(char *route) {
  struct stat stat_buf;

  char path[1024] = {0};
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  if (strlen(route) == 1 || (strncmp(route, "/index.html", 11) == 0))
    return Index;

  if (strlen(route) > 1) {
    if (stat(path, &stat_buf) == 0)
      return Asset;
  }

  return NotFound;
}

static char *get_asset(char *route) {
  char *path = (char *)malloc(1024);
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  return path;
}

static char *get_page(Pages page) {
  char *path = (char *)malloc(1024);
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

  if (path == NULL)
    return 0;
  return path;
}

char *route(char *route) {
  Pages page_type = get_page_enum(route);
  char *returnable;

  if (page_type != Asset) {
    returnable = get_page(page_type);
    return returnable;
  }

  returnable = get_asset(route);
  return returnable;
}
