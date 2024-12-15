#include "gnutls/gnutls.h"
#include <jansson.h>
#include <microhttpd.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <zlib-ng.h>

#include "../../include/api.h"
#include "../../include/log.h"
#include "../../include/meta.h"

int is_leap_year(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) {
  if (month == 1)
    return is_leap_year(year) ? 29 : 28;
  static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return days[month];
}

char *format_uptime(time_t current_time, struct tm start_date) {
  char *bufptr = malloc(48);
  struct tm end_date;
  localtime_r(&current_time, &end_date);

  int years = end_date.tm_year - start_date.tm_year;
  int months = end_date.tm_mon - start_date.tm_mon + years * 12;
  int days = end_date.tm_mday - start_date.tm_mday;
  int hours = end_date.tm_hour - start_date.tm_hour;
  int minutes = end_date.tm_min - start_date.tm_min;
  int seconds = end_date.tm_sec - start_date.tm_sec;

  if (days < 0) {
    --months;
    days += days_in_month(start_date.tm_year, start_date.tm_mon);
  }

  if (seconds < 0) {
    seconds += 60;
    --minutes;
  }
  if (minutes < 0) {
    minutes += 60;
    --hours;
  }
  if (hours < 0) {
    hours += 24;
    --days;
  }

  snprintf(bufptr, 48, "%dm %dd %02d:%02d:%02d", months, days, hours, minutes,
           seconds);

  return bufptr;
}

static char *get_uptime_str(struct tm start_date) {
  time_t current_time = time(NULL);

  char *uptime_buf = format_uptime(current_time, start_date);
  return uptime_buf;
}

char *get_uptime(struct tm start_date, size_t *resplen) {
  json_t *root = json_object();

  char *uptime_buf = get_uptime_str(start_date);
  json_object_set_new(root, "uptime", json_string(uptime_buf));

  size_t size = json_dumpb(root, NULL, 0, JSON_INDENT(2));
  if (size == 0) {
    flscio_log(Error, "failed to dump json for uptime");
    return NULL;
  }

  *resplen = size;

  char *buf = malloc(size);
  (void)json_dumpb(root, buf, size, JSON_INDENT(2));

  free(uptime_buf);
  json_decref(root);
  return buf;
}

char *get_server_info(struct tm start_date, size_t *resplen) {
  json_t *root = json_object();

  const char *gnu_tls_ver = gnutls_check_version(NULL);
  char *uptime_buf = get_uptime_str(start_date);

  json_object_set_new(root, "name", json_string(__NAME__));
  json_object_set_new(root, "description", json_string(__DESCRIPTION__));
  json_object_set_new(root, "version", json_string(__PROJ_VERSION__));
  json_object_set_new(root, "gnu_tls_version", json_string(gnu_tls_ver));
  json_object_set_new(root, "jansson_version", json_string(JANSSON_VERSION));
  json_object_set_new(root, "zlib-ng_version", json_string(ZLIBNG_VERSION));
  json_object_set_new(root, "uptime", json_string(uptime_buf));

  size_t size = json_dumpb(root, NULL, 0, JSON_INDENT(2));
  if (size == 0) {
    flscio_log(Error, "failed to dump json for uptime");
    return NULL;
  }

  *resplen = size;

  char *buf = malloc(size);
  (void)json_dumpb(root, buf, size, JSON_INDENT(2));

  free(uptime_buf);
  json_decref(root);
  return buf;
}
