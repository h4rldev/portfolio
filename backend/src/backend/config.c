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

  char *email_buf = (char *)malloc(255);
  email_buf = NULL;

  local_ssl.email = email_buf;
  local_ssl.ssl = false;

  networkConfig local_network;

  char *ip_buf = (char *)malloc(16);
  strlcpy(ip_buf, "127.0.0.1", 16);

  local_network.ip = ip_buf;
  local_network.port = 8080;

  local_config.ssl = local_ssl;
  local_config.network = local_network;

  *config = local_config;

  puts(config->network.ip);

  return 0;
}

int write_config(Config *config) {
  char *default_path = DEFAULT_PATH;
  char *cwd = get_cwd();
  char *path = (char *)malloc(1024);

  if (!cwd || !path)
    return -1;

  if (config == NULL)
    return -1;

  sslConfig local_ssl = config->ssl;
  networkConfig local_network = config->network;

  snprintf(path, 1024, "%s%s", cwd, default_path);
  free(cwd);

  if (path_exist(path) == false) {
    if (make_dir(path) != 0) {
      free(path);
      return -1;
    }
  }

  strlcat(path, "config.json", 1024);

  json_t *root = json_object();
  json_t *ssl_object = json_object();
  json_t *network_object = json_object();

  char *email;
  bool ssl = local_ssl.ssl;

  if (local_ssl.email == NULL)
    email = "";
  else
    email = local_ssl.email;

  json_object_set_new(ssl_object, "email", json_string(email));

  if (ssl == true)
    json_object_set_new(ssl_object, "ssl", json_true());
  else
    json_object_set_new(ssl_object, "ssl", json_false());

  json_object_set_new(root, "ssl", ssl_object);

  char *ip = local_network.ip;
  unsigned int port = local_network.port;

  json_object_set_new(network_object, "ip", json_string(ip));
  json_object_set_new(network_object, "port", json_integer(port));

  json_object_set_new(root, "network", network_object);

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

  root = json_load_file(path, 0, &error);
  if (!root) {
    fprintf(stderr, "Error parsing json on line %d: %s\n", error.line,
            error.text);
    free(path);
    return -1;
  }

  free(path);

  json_t *ssl_object = json_object_get(root, "ssl");
  if (!json_is_object(ssl_object)) {
    json_decref(root);
    return -1;
  }

  json_t *email_string = json_object_get(ssl_object, "email");

  char *email = (char *)malloc(255);
  if (!email) {
    json_decref(root);
    return -1;
  }

  if (json_is_string(email_string))
    strlcpy(email, json_string_value(email_string), 255);

  json_t *ssl_bool = json_object_get(ssl_object, "ssl");

  bool ssl;
  if (json_is_boolean(ssl_bool))
    ssl = json_boolean_value(ssl_bool);

  json_t *network_object = json_object_get(root, "network");
  if (!json_is_object(network_object)) {
    free(email);
    json_decref(root);
    return -1;
  }

  json_t *ip_string = json_object_get(network_object, "ip");
  char *ip = (char *)malloc(16);
  if (!ip) {
    free(email);
    json_decref(root);
    return -1;
  }

  if (json_is_string(ip_string))
    strlcpy(ip, json_string_value(ip_string), 16);

  json_t *port_integer = json_object_get(network_object, "port");

  unsigned int port;
  if (json_is_integer(port_integer))
    port = json_integer_value(port_integer);

  Config local_config;

  sslConfig local_ssl;
  local_ssl.email = email;
  local_ssl.ssl = ssl;

  networkConfig local_network;
  local_network.ip = ip;
  local_network.port = port;

  local_config.ssl = local_ssl;
  local_config.network = local_network;

  *config = local_config;

  json_decref(root);

  return 0;
}

int free_config(Config *config) {
  sslConfig local_ssl = config->ssl;
  networkConfig local_network = config->network;

  free(local_ssl.email);
  free(local_network.ip);

  return 0;
}
