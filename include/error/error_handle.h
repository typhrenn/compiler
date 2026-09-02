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

struct IncludeFrame;

typedef void (*Error)(const char *fmt, ...);
typedef void (*VerboseError)(struct IncludeFrame *frame, int column, uint32_t length, const char *fmt, ...);
typedef void (*Fatal)(int __status);

void verbose_err(struct IncludeFrame *frame, int column, uint32_t length, const char *fmt, ...);
__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void fatal_err(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void err(const char *fmt, ...);

__attribute__((format(printf, 1, 2))) void warning_log(const char *fmt, ...);
__attribute__((format(printf, 1, 2))) void note_log(const char *fmt, ...);

typedef struct {
    VerboseError 	verr;
    Error      		ferr;
    Error      		err;
    Fatal			fatal;

	Error			note;
	Error			warning;
} ErrorHandler;

void dummy_exit(int __status);

#endif