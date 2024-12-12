#ifndef LOG_H_IMPLEMENTATION
#define LOG_H_IMPLEMENTATION

typedef enum { Error, Warning, Info, Debug } LogLevel;

int flscio_log(LogLevel level, char *fmt, ...);

#endif // !LOG_H_IMPLEMENTATION
