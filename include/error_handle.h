#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdarg.h>

typedef void (*ThrowError)(const char *fmt, ...);

typedef struct {
    const char *file;
    int line;
    int ch;
} Location;

__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void log_error(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void log_warning(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void log_note(const char *fmt, ...);

#endif