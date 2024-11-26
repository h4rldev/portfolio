#ifndef CONFIG_H_IMPLEMENTATION
#define CONFIG_H_IMPLEMENTATION

#include <stdbool.h>

typedef struct {
  char *email;
  bool ssl;
} sslConfig;

typedef struct {
  char *ip;
  unsigned int port;
} networkConfig;

typedef struct {
  sslConfig ssl;
  networkConfig network;
} Config;

int init_config(Config *config);
int write_config(Config *config);
int read_config(Config *config);
int free_config(Config *config);

#endif // ! CONFIG_H_IMPLEMENTATION
