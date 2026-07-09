#ifndef HTTP_LOG_H
#define HTTP_LOG_H

typedef enum {
  LOG_FATAL,
  LOG_ERROR,
  LOG_INFO,
  LOG_DEBUG,
  LOG_TRACE,
} LogLevel;

#define FATAL(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#define ERROR(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define INFO(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define TRACE(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

void log_log(LogLevel level, const char *file, int line, const char *fmt, ...);

#endif
