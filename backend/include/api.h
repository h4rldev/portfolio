#ifndef API_H_IMPLEMENTATION
#define API_H_IMPLEMENTATION

#include <time.h>

typedef enum {
  Uptime,
  ServerInfo,
} ApiRoute;

char *get_uptime(struct tm start_time, size_t *resp_len);
char *get_server_info(struct tm start_date, size_t *resp_len);

#endif // !API_H_IMPLEMENTATION
