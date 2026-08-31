#include "error/error_handle.h"
#include "utils/utils.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_MAGENTA  "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_BOLD    "\x1b[1m"

void verbose_err(struct IncludeFrame *frame, int column, uint32_t length, const char *fmt, ...) {
    const char *line_end = frame->line_start;
    while (*line_end != '\n' && *line_end != '\0') {
        line_end++;
    }
    int line_len = (int)(line_end - frame->line_start);

    fprintf(stderr, COLOR_BOLD "%s:%d:%d: " COLOR_RED "error: " COLOR_RESET COLOR_BOLD,
            frame->filename ? frame->filename : "<stdin>", frame->line, column);

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, COLOR_RESET "\n");

    if (line_len > 0) {
        fprintf(stderr, " %5d | %.*s\n", frame->line, line_len, frame->line_start);

        fprintf(stderr, "       | ");
        for (int i = 1; i < column + (int)length && i <= line_len; i++) {
            fputc(frame->line_start[i - 1] == '\t' ? '\t' : ' ', stderr);
        }

        fprintf(stderr, COLOR_BOLD COLOR_RED "^" COLOR_RESET "\n");
    }
}
__attribute__((noreturn)) __attribute__((format(printf, 1, 2))) void fatal_err(const char *fmt, ...) {
    fprintf(stderr, COLOR_BOLD COLOR_RED "fatal error: " COLOR_RESET COLOR_BOLD);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, COLOR_RESET "\n");
    exit(EXIT_FAILURE);
}

__attribute__((format(printf, 1, 2))) void err(const char *fmt, ...) {
    fprintf(stderr, COLOR_BOLD COLOR_RED "error: " COLOR_RESET COLOR_BOLD);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr, COLOR_RESET "\n");
}

__attribute__((format(printf, 1, 2))) void warning_log(const char *fmt, ...) {
    va_list args;
    fprintf(stderr, COLOR_BOLD COLOR_MAGENTA "warning: " COLOR_RESET);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

__attribute__((format(printf, 1, 2))) void note_log(const char *fmt, ...) {
    va_list args;
    fprintf(stderr, COLOR_BOLD COLOR_CYAN "note: " COLOR_RESET);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void dummy_exit(int __status) {}