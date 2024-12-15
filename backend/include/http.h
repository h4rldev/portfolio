#ifndef HTTP_H_IMPLEMENTATION
#define HTTP_H_IMPLEMENTATION

#include <stddef.h>
#include <time.h>

typedef enum {
  NotFound,
  File,
  Api,
} Pages;

char *route(const char *route);
char *get_api_resp(const char *route, struct tm start_date, size_t *resp_len);

#endif // !HTTP_H_IMPLEMENTATION
