#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../../include/config.h"
#include "../../include/file.h"
#include "../../include/log.h"

int flscio_log(LogLevel level, char *fmt, ...) {
  Config config;
  va_list args;

  read_config(&config);

  time_t time_container = time(NULL);
  struct tm *time = localtime(&time_container);
  char file_time_buf[11] = {0};
  char log_time_buf[22] = {0};

  snprintf(file_time_buf, 11, "%d-%02d-%02d", time->tm_year + 1900,
           time->tm_mon + 1, time->tm_mday);

  snprintf(log_time_buf, 22, "%02d:%02d:%02d %d-%02d-%02d", time->tm_hour,
           time->tm_min, time->tm_sec, time->tm_year + 1900, time->tm_mon + 1,
           time->tm_mday);

  char fmt_buf[1024] = {0};

  char *logs_path = config.log.path;

  if (path_exist(logs_path) == false) {
    if (make_dir(logs_path) != 0) {
      free_config(&config);
      return -1;
    }
  }

  char file_path[1024] = {0};

  snprintf(file_path, 1024, "%s/flscio_log-%s.log", logs_path, file_time_buf);

  LogLevel current_level = config.log.level;

  FILE *current_file = stdout;
  if (level == Error) {
    current_file = stderr;
  }

  char *prefix;
  switch (level) {
  case Debug:
    prefix = "[DEBUG]:";
    break;
  case Info:
    prefix = "[INFO]:";
    break;
  case Warning:
    prefix = "[WARN]:";
    break;
  case Error:
    prefix = "[ERROR]:";
    break;
  default:
    flscio_log(Error, "Congratulations, you managed to make the log "
                      "function error, you're a mess uhhhhhhh Daniel! (sorry "
                      "all Daniels that exist you're to blame today)\n");
    return -1;
  }

  snprintf(fmt_buf, strlen(prefix) + strlen(fmt) + 27, "%s %s %s", log_time_buf,
           prefix, fmt);

  size_t fmt_buf_len = strlen(fmt_buf);

  // Insert a \n if none is available :3
  if (fmt_buf[fmt_buf_len - 1] != '\n') {
    fmt_buf[fmt_buf_len] = '\n';
    fmt_buf[fmt_buf_len + 1] = '\0';
  }

  va_start(args, fmt);

  if (level <= current_level)
    vfprintf(current_file, fmt_buf, args);

  FILE *file = fopen(file_path, "a+");
  vfprintf(file, fmt_buf, args);
  fclose(file);

  va_end(args);
  free_config(&config);

  return 0;
}
