#ifndef HTTP_H_IMPLEMENTATION
#define HTTP_H_IMPLEMENTATION

#include <stddef.h>
#include <time.h>

typedef enum {
  Page,
  NotFound,
  Asset,
  Api,
} Pages;

char *route(char *route);
char *get_api_resp(char *route, struct tm start_date, size_t *resp_len);

#endif // !HTTP_H_IMPLEMENTATION
