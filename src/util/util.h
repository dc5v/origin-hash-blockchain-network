#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdarg.h>

#define LOG_PATH "./log.txt"

void logmsg(const char *format, ...);
void logmsgf(const char *format, ...);

#endif 
