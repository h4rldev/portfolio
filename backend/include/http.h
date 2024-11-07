#ifndef HTTP_H_IMPLEMENTATION
#define HTTP_H_IMPLEMENTATION

#include <stddef.h>

typedef enum {
  Index,
  NotFound,
  Asset,
} Pages;

int populate_mime(char *path, char mime[], size_t mime_len);
Pages get_page_enum(char *route);
char *route(char *route, char mime[], size_t mime_len);

#endif // !HTTP_H_IMPLEMENTATION
