#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdarg.h>

#define LOG_PATH "./log.txt"

void log(const char *format, ...);
void logf(const char *format, ...);

#endif 
