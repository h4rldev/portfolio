#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../include/api.h"
#include "../../include/file.h"
#include "../../include/http.h"
#include "../../include/log.h"

static Pages get_page_enum(char *route) {

  char path[1024] = {0};
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  if (strlen(route) == 1 || (strncmp(route, "/index.html", 11) == 0))
    return Page;

  if (path_exist(path))
    return Asset;

  if (strncmp(route, "/api", 4) == 0)
    return Api;

  return NotFound;
}

static char *get_asset(char *route) {
  char *path = (char *)malloc(1024);
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  return path;
}

static char *get_route(Pages page) {
  char *path = (char *)malloc(1024);
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site", cwd);
  free(cwd);

  switch (page) {
  case Page:
    strlcat(path, "/index.html", 1024);
    break;
  case NotFound:
    strlcat(path, "/notfound.html", 1024);
    break;
  default:
    flscio_log(Error, "Invalid use of get_page");
    return NULL;
  }

  if (path == NULL)
    return NULL;
  return path;
}

char *get_api_resp(char *route, struct tm start_date, size_t *resp_len) {
  if (strncmp(route, "/api/uptime", 11) == 0) {
    return get_uptime(start_date, resp_len);
  } else if (strncmp(route, "/api/server-info", 16) == 0) {
    return get_server_info(start_date, resp_len);
  }

  return NULL;
}

char *route(char *route) {
  Pages page_type = get_page_enum(route);
  char *returnable;

  if (page_type != Asset && page_type != Api) {
    returnable = get_route(page_type);
  } else if (page_type != Api) {
    returnable = get_asset(route);
  } else {
    // Api route
    returnable = NULL;
  }

  return returnable;
}
