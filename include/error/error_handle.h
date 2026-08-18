#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#include "utils/utils.h"

typedef struct {
    const char *file;
    int line;
    int column;
} Location;

typedef void (*Error)(const char *fmt, ...);
typedef void (*VerboseError)(Location loc, String source_line, uint32_t length, const char *fmt, ...);
typedef void (*Fatal)(int __status);

void verbose_err(Location loc, String source_line, uint32_t length, const char *fmt, ...);
__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void fatal_err(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void err(const char *fmt, ...);

__attribute__((format(printf, 1, 2))) void warning_log(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void note_log(const char *fmt, ...);

struct ErrorHandler {
    VerboseError 	verr;
    Error      		ferr;
    Error      		err;
    Fatal			fatal;

	Error			note;
	Error			warning;
};

void dummy_exit(int __status);

#endif