#include <jansson.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../include/config.h"
#include "../../include/file.h"
#include "../../include/log.h"

#define DEFAULT_PATH "/config/";

int init_config(Config *config) {
  Config local_config;
  logConfig local_log;
  sslConfig local_ssl;

  bool compress = true;

  local_config.port = 8080;
  local_config.compress = compress;

  local_ssl.ssl = false;
  local_ssl.cert_path = (char *)malloc(1024);
  local_ssl.key_path = (char *)malloc(1024);
  local_ssl.cert_path = NULL;
  local_ssl.key_path = NULL;

  local_log.path = (char *)malloc(1024);
  local_log.path = NULL;
  local_log.level = Warning;

  local_config.ssl = local_ssl;
  local_config.log = local_log;

  *config = local_config;

  return 0;
}

int write_config(Config *config) {
  char *default_path = DEFAULT_PATH;
  char *cwd = get_cwd();
  char *path = (char *)malloc(1024);
  char cwd_buf[1024] = {0};

  if (!cwd || !path)
    return -1;

  strlcpy(cwd_buf, cwd, 1024);
  free(cwd);

  snprintf(path, 1024, "%s%s", cwd_buf, default_path);

  if (path_exist(path) == false) {
    if (make_dir(path) != 0) {
      free(path);
      return -1;
    }
  }

  strlcat(path, "config.json", 1024);

  if (config == NULL)
    return -1;

  bool compress = config->compress;
  unsigned int port = config->port;

  json_t *root = json_object();
  json_t *log_object = json_object();
  json_t *ssl_object = json_object();

  json_object_set_new(root, "port", json_integer(port));

  if (compress == true)
    json_object_set_new(root, "compress", json_true());
  else
    json_object_set_new(root, "compress", json_false());

  if (config->ssl.ssl == true)
    json_object_set_new(ssl_object, "ssl", json_true());
  else
    json_object_set_new(ssl_object, "ssl", json_false());

  if (config->ssl.cert_path == NULL) {
    json_object_set_new(ssl_object, "cert_path", json_string(""));
    json_object_set(ssl_object, "ssl", json_false());
  } else {
    json_object_set_new(ssl_object, "cert_path",
                        json_string(config->ssl.cert_path));
  }

  if (config->ssl.key_path == NULL) {
    json_object_set_new(ssl_object, "key_path", json_string(""));
    json_object_set(ssl_object, "ssl", json_false());
  } else {
    json_object_set_new(ssl_object, "key_path",
                        json_string(config->ssl.key_path));
  }

  json_object_set_new(root, "ssl", ssl_object);

  if (config->log.path == NULL) {
    char *default_log_path = (char *)malloc(1024);
    snprintf(default_log_path, 1024, "%s/logs", cwd_buf);
    json_object_set_new(log_object, "path", json_string(default_log_path));
    free(default_log_path);
  } else {
    json_object_set_new(log_object, "path", json_string(config->log.path));
  }

  switch (config->log.level) {
  case Error:
    json_object_set_new(log_object, "level", json_string("Error"));
    break;
  case Warning:
    json_object_set_new(log_object, "level", json_string("Warning"));
    break;
  case Info:
    json_object_set_new(log_object, "level", json_string("Info"));
    break;
  case Debug:
    json_object_set_new(log_object, "level", json_string("Debug"));
    break;
  default:
    json_object_set_new(log_object, "level", json_string("Error"));
    break;
  }

  json_object_set_new(root, "log", log_object);

  FILE *file = fopen(path, "w");
  json_dumpf(root, file, JSON_INDENT(2));

  fclose(file);
  json_decref(root);
  free(path);

  return 0;
}

int read_config(Config *config) {
  json_t *root;
  json_error_t error;

  char *default_path = DEFAULT_PATH;

  char *cwd = get_cwd();
  if (!cwd) {
    return -1;
  }

  char *path = (char *)malloc(1024);
  if (!path) {
    free(cwd);
    return -1;
  }

  snprintf(path, 1024, "%s%sconfig.json", cwd, default_path);
  free(cwd);

  if (!path_exist(path)) {
    return -1;
  }

  root = json_load_file(path, 0, &error);
  if (!root) {
    fprintf(stderr, "Error parsing json on line %d: %s\n", error.line,
            error.text);
    free(path);
    return -1;
  }

  free(path);

  json_t *port_integer = json_object_get(root, "port");

  unsigned int port;
  if (json_is_integer(port_integer))
    port = json_integer_value(port_integer);

  json_t *compress_bool = json_object_get(root, "compress");

  bool compress;
  if (json_is_boolean(compress_bool))
    compress = json_boolean_value(compress_bool);

  json_t *ssl_object = json_object_get(root, "ssl");
  if (!json_is_object(ssl_object)) {
    json_decref(root);
    return -1;
  }

  json_t *ssl_bool = json_object_get(ssl_object, "ssl");

  bool ssl;
  if (json_is_boolean(ssl_bool))
    ssl = json_boolean_value(ssl_bool);

  json_t *cert_path_string = json_object_get(ssl_object, "cert_path");

  char *cert_path = (char *)malloc(1024);
  if (!cert_path) {
    json_decref(root);
    return -1;
  }

  if (json_is_string(cert_path_string))
    strlcpy(cert_path, json_string_value(cert_path_string), 1024);

  json_t *key_path_string = json_object_get(ssl_object, "key_path");

  char *key_path = (char *)malloc(1024);
  if (!key_path) {
    free(cert_path);
    json_decref(root);
    return -1;
  }

  if (json_is_string(key_path_string))
    strlcpy(key_path, json_string_value(key_path_string), 1024);

  json_t *log_object = json_object_get(root, "log");
  if (!json_is_object(log_object)) {
    json_decref(root);
    return -1;
  }

  json_t *path_string = json_object_get(log_object, "path");

  char *log_path = (char *)malloc(1024);
  if (!log_path) {
    free(cert_path);
    free(key_path);
    json_decref(root);
    return -1;
  }

  if (json_is_string(path_string))
    strlcpy(log_path, json_string_value(path_string), 1024);

  json_t *level_string = json_object_get(log_object, "level");
  char level_buf[8] = {0};
  if (json_is_string(level_string))
    strlcpy(level_buf, json_string_value(level_string), 8);

  config->ssl.ssl = ssl;
  config->ssl.cert_path = cert_path;
  config->ssl.key_path = key_path;

  config->log.path = log_path;

  if (strncmp(level_buf, "Error", 5) == 0)
    config->log.level = Error;
  else if (strncmp(level_buf, "Warning", 7) == 0)
    config->log.level = Warning;
  else if (strncmp(level_buf, "Info", 4) == 0)
    config->log.level = Info;
  else if (strncmp(level_buf, "Debug", 5) == 0)
    config->log.level = Debug;
  else
    config->log.level = Error;

  config->port = port;
  config->compress = compress;

  json_decref(root);

  return 0;
}

int free_config(Config *config) {
  free(config->log.path);
  free(config->ssl.cert_path);
  free(config->ssl.key_path);
  return 0;
}
