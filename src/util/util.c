#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

void log(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

void logf(const char *format, ...)
{
  FILE *file = fopen(LOG_PATH, "a");

  if (file == NULL)
  {
    perror("Failed to open log file");
    return;
  }

  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);
  char time_buffer[26];

  strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
  fprintf(file, "[%s] ", time_buffer);

  va_list args;
  va_start(args, format);

  vfprintf(file, format, args);
  fprintf(file, "\n");

  va_end(args);
  fclose(file);
}
