#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../include/api.h"
#include "../../include/file.h"
#include "../../include/http.h"
#include "../../include/log.h"

static Pages get_page_enum(const char *route) {

  char path[1024] = {0};
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  if (path_exist(path))
    return File;

  if (strncmp(route, "/api", 4) == 0)
    return Api;

  return NotFound;
}

static char *get_asset(const char *route) {
  char *path = (char *)malloc(1024);
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site%s", cwd, route);
  free(cwd);

  if (!path_exist(path)) {
    flscio_log(Error, "Can't find path: %s", path);
    return NULL;
  }

  if (!is_file(path)) {
    strlcat(path, "/index.html", 1024);
  }

  return path;
}

static char *get_not_found() {
  char *path = (char *)malloc(1024);
  char *cwd = get_cwd();

  snprintf(path, 1024, "%s/site/notfound.html", cwd);
  free(cwd);

  return path;
}

char *get_api_resp(const char *route, struct tm start_date, size_t *resp_len) {
  if (strncmp(route, "/api/uptime", 11) == 0) {
    return get_uptime(start_date, resp_len);
  } else if (strncmp(route, "/api/server-info", 16) == 0) {
    return get_server_info(start_date, resp_len);
  }

  return NULL;
}

char *route(const char *route) {
  Pages page_type = get_page_enum(route);
  char *returnable;

  if (page_type == File) {
    returnable = get_asset(route);
  } else if (page_type == NotFound) {
    returnable = get_not_found();
  } else {
    // Api route
    returnable = NULL;
  }

  return returnable;
}
