#ifndef CLI_H_IMPLEMENTATION
#define CLI_H_IMPLEMENTATION

#include <stdbool.h>

#include "./config.h"

int parse_args(int *argc, char ***argv, Config *populated_args);

#endif // !CLI_H_IMPLEMENTATION
