#ifndef HTTP_H_IMPLEMENTATION
#define HTTP_H_IMPLEMENTATION

typedef enum {
  Index,
  NotFound,
  Asset,
} Pages;

Pages get_page_enum(char *route);
char *route(char *route);

#endif // !HTTP_H_IMPLEMENTATION
