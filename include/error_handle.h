#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H

#include <stdio.h>
#include <stdlib.h>

typedef void (*ThrowError)(const char *msg);

__attribute__((noreturn)) void exit_fatal(const char *msg);

#endif