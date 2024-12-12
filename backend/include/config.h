#ifndef CONFIG_H_IMPLEMENTATION
#define CONFIG_H_IMPLEMENTATION

#include "log.h"
#include <stdbool.h>

typedef struct {
  bool ssl;
  char *cert_path;
  char *key_path;
} sslConfig;

typedef struct {
  char *path;
  LogLevel level;
} logConfig;

typedef struct {
  unsigned int port;
  bool compress;
  sslConfig ssl;
  logConfig log;
} Config;

int init_config(Config *config);
int free_config(Config *config);

int read_config(Config *config);
int write_config(Config *config);

#endif // !CONFIG_H_IMPLEMENTATION
