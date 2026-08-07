#include "error_handle.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_MAGENTA  "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_BOLD    "\x1b[1m"

void verror(Location loc, String source_line, const char *fmt, ...) {
    fprintf(stderr, COLOR_BOLD "%s:%d:%d: " COLOR_RED "error: " COLOR_RESET COLOR_BOLD,
            loc.file ? loc.file : "<stdin>", loc.line, loc.column);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, COLOR_RESET "\n");

    if (source_line.string && source_line.len > 0) {
        fprintf(stderr, " %5d | %.*s\n", loc.line, source_line.len, source_line.string);

        fprintf(stderr, "       | ");
        for (int i = 1; i < loc.column && i <= source_line.len; i++) {
            fputc(source_line.string[i - 1] == '\t' ? '\t' : ' ', stderr);
        }

        fprintf(stderr, COLOR_BOLD COLOR_RED "^" COLOR_RESET "\n");
    }
}

__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void error(const char *fmt, ...) {
    fprintf(stderr, COLOR_BOLD COLOR_RED "fatal error: " COLOR_RESET COLOR_BOLD);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, COLOR_RESET "\n");
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

