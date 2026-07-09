#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

char *level_str[] = {"FATAL", "ERROR", "INFO", "DEBUG", "TRACE"};

void log_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
  va_list va;
  time_t t = time(NULL);
  va_start(va, fmt);
  char time[64] = {'\0'};
  strftime(time, sizeof(time), "%F %H:%M:%S", localtime(&t));
  fprintf(stderr, "[%s] %-5s %s:%d ", time, level_str[level], file, line);
  vfprintf(stderr, fmt, va);
  fprintf(stderr, "\n");
  fflush(stderr);
  va_end(va);
}
