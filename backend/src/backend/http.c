#include "../../include/http.h"
#include "../../include/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pages get_page_enum(char *route) {
  if (strncmp(route, "/", 1) == 0)
    return Index;

  if (strncmp(route, "/assets/", 8) == 0)
    return Asset;

  return NotFound;
}

static char *get_asset(char *route) {
  char path[1024] = {0};
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site/assets%s", cwd, route);
  free(cwd);

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
