/*

Simple logger helper

Copyright (c) 2013-2017 Antmicro <www.antmicro.com>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <stdio.h>
#include <sys/time.h>
#include <stdarg.h>
#include "log_helper.h"

#ifdef LOGGER_USE_THREADS
#include <pthread.h>
static pthread_mutex_t log_mutex;
static int log_mutex_initialized = 0;
#endif

static void inner_log(const char* source, const char* text, va_list argList, const char *type, int color)
{
#ifdef LOGGER_USE_THREADS
    if (!log_mutex_initialized) {
        log_mutex_initialized = 1;
        pthread_mutex_init(&log_mutex, NULL);
    }
#endif
    if (!LOGGING) return;
    char color_s[10];
    if (COLORS) {
        sprintf(color_s, "\e[1;%dm", color);
    }
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm* ptm;
    ptm = localtime (&tv.tv_sec);
    char time_s[9];
    strftime (time_s, sizeof(time_s), "%H:%M:%S", ptm);
#ifdef LOGGER_USE_THREADS
    pthread_mutex_lock(&log_mutex);
#endif
    printf("[%s%s%s @ %s] %s%s%s: ", COLORS ? color_s : "", type, COLORS ? "\e[21;39m" : "", time_s, COLORS ? "\e[1;37m" : "", source, COLORS ? "\e[21;39m" : "");
    vprintf(text, argList);
    printf("\n\r");
#ifdef LOGGER_USE_THREADS
    pthread_mutex_unlock(&log_mutex);
#endif
}

void log_msg(int level, const char *type, int color, const char* source, const char* text, ...)
{
    if(level < 0)
    {
        return;
    }
    va_list argList;
    va_start(argList, text);
    inner_log(source, text, argList, type, color);
    va_end(argList);
}

void vlog_msg(int level, const char *type, int color, const char* source, const char* text, va_list argList)
{
    if(level < 0)
    {
        return;
    }
    inner_log(source, text, argList, type, color);
}


