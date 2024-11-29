#ifndef CONFIG_H_IMPLEMENTATION
#define CONFIG_H_IMPLEMENTATION

#include <stdbool.h>

typedef struct {
  bool ssl;
  char *email;
  char *domain;
} sslConfig;

typedef struct {
  unsigned int port;
  bool compress;
  sslConfig ssl;
} Config;

int init_config(Config *config);
int free_config(Config *config);

int read_config(Config *config);
int write_config(Config *config);

#endif // !CONFIG_H_IMPLEMENTATION
