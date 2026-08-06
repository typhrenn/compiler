#include "error_handle.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_MAGENTA  "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_BOLD    "\x1b[1m"

__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void log_error(const char *fmt, ...) {
    va_list args;
    fprintf(stderr, COLOR_BOLD COLOR_RED "Error: " COLOR_RESET);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

__attribute__((format(printf, 1, 2))) void log_warning(const char *fmt, ...) {
    va_list args;
    fprintf(stderr, COLOR_BOLD COLOR_MAGENTA "Warning: " COLOR_RESET);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

__attribute__((format(printf, 1, 2))) void log_note(const char *fmt, ...) {
    va_list args;
    fprintf(stderr, COLOR_BOLD COLOR_CYAN "Note: " COLOR_RESET);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

