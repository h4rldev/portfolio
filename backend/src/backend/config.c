#include <jansson.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../../include/config.h"
#include "../../include/file.h"

#define DEFAULT_PATH "/config/";

int init_config(Config *config) {
  Config local_config;

  sslConfig local_ssl;
  bool compress = true;

  char *email_buf = (char *)malloc(255);
  char *domain_buf = (char *)malloc(128);
  if (!email_buf || !domain_buf)
    return -1;

  email_buf = NULL;
  domain_buf = NULL;

  local_ssl.ssl = false;
  local_ssl.email = email_buf;
  local_ssl.domain = domain_buf;

  local_config.port = 8080;
  local_config.compress = compress;
  local_config.ssl = local_ssl;

  *config = local_config;

  return 0;
}

int write_config(Config *config) {
  char *default_path = DEFAULT_PATH;
  char *cwd = get_cwd();
  char *path = (char *)malloc(1024);

  if (!cwd || !path)
    return -1;

  if (path_exist(path) == false) {
    if (make_dir(path) != 0) {
      free(path);
      return -1;
    }
  }

  snprintf(path, 1024, "%s%s", cwd, default_path);
  free(cwd);

  strlcat(path, "config.json", 1024);

  if (config == NULL)
    return -1;

  bool compress = config->compress;
  unsigned int port = config->port;
  sslConfig local_ssl = config->ssl;

  json_t *root = json_object();
  json_t *ssl_object = json_object();

  json_object_set_new(root, "port", json_integer(port));

  if (compress == true)
    json_object_set_new(root, "compress", json_true());
  else
    json_object_set_new(root, "compress", json_false());

  bool ssl = local_ssl.ssl;
  char *email;
  char *domain;

  if (ssl == true)
    json_object_set_new(ssl_object, "ssl", json_true());
  else
    json_object_set_new(ssl_object, "ssl", json_false());

  if (local_ssl.email == NULL)
    email = "";
  else
    email = local_ssl.email;

  if (local_ssl.domain == NULL)
    domain = "";
  else
    domain = local_ssl.domain;

  json_object_set_new(ssl_object, "email", json_string(email));
  json_object_set_new(ssl_object, "domain", json_string(domain));
  json_object_set_new(root, "ssl", ssl_object);

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

  json_t *email_string = json_object_get(ssl_object, "email");

  char *email = (char *)malloc(255);
  if (!email) {
    json_decref(root);
    return -1;
  }

  if (json_is_string(email_string))
    strlcpy(email, json_string_value(email_string), 255);

  json_t *domain_string = json_object_get(ssl_object, "domain");

  char *domain = (char *)malloc(128);
  if (!domain) {
    free(email);
    json_decref(root);
    return -1;
  }

  if (json_is_string(domain_string))
    strlcpy(domain, json_string_value(domain_string), 128);

  sslConfig local_ssl;
  local_ssl.ssl = ssl;
  local_ssl.email = email;
  local_ssl.domain = domain;

  config->port = port;
  config->compress = compress;
  config->ssl = local_ssl;

  json_decref(root);

  return 0;
}

int free_config(Config *config) {
  sslConfig local_ssl = config->ssl;

  free(local_ssl.email);
  free(local_ssl.domain);

  return 0;
}
