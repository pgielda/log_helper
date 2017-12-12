#ifndef __log_helper_h__
#define __log_helper_h__

#include <stdarg.h>

#define LOGGER_COLORS 1
#define LOGGER_SILENT 0
#define LOGGER_USE_THREADS

void log_msg(int level, const char *type, int color, const char* source, const char* text, ...);
void vlog_msg(int level, const char *type, int color, const char* source, const char* text, va_list argList);

#define ERR 0, "ERR", 31
#define WARN 1, "WARN", 32
#define INFO 2, "INFO", 33
#define DEBUG 3, "DEBUG", 34

#define LOGGER_MAX_LEVEL 2 /* DEBUG is not printed by default */

#endif
