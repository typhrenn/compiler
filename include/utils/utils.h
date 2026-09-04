#ifndef UTILS_H
#define UTILS_H

typedef struct {
    const char *value;
    int length;
} String;

static inline String strcnstr(const char *value, int len) {
    return (String){value, len};
}

typedef struct IncludeFrame {
    const char *filename;
    const char *pos;
    const char *line_start;
    int         line;
} IncludeFrame;

#endif