#ifndef HTTP_H_IMPLEMENTATION
#define HTTP_H_IMPLEMENTATION

#include <stddef.h>

typedef enum {
  Index,
  NotFound,
  Asset,
} Pages;

char *route(char *route);

#endif // !HTTP_H_IMPLEMENTATION
