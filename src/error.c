#include "error_handle.h"

__attribute__((noreturn)) void exit_fatal(const char *msg) {
    fprintf(stderr, "crashed with message: %s\n", msg);
    exit(EXIT_FAILURE);
}