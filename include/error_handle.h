#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include "utils.h"

typedef struct {
    const char *file;
    int line;
    int column;
} Location;

typedef void (*Error)(const char *fmt, ...);
typedef void (*VerboseError)(Location loc, String source_line, uint32_t length, const char *fmt, ...);
typedef void (*Fatal)(int __status);

__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void error(const char *fmt, ...);
void verror(Location loc, String source_line, uint32_t length, const char *fmt, ...);

__attribute__((format(printf, 1, 2))) void log_warning(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void log_note(const char *fmt, ...);

void dummy_exit(int __status);

#endif