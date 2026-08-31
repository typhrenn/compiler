#ifndef UTILS_H
#define UTILS_H

typedef struct {
    const char *string;
    int len;
} String;

static inline String strcnstr(const char *string, int len) {
    return (String){string, len};
}

typedef struct IncludeFrame {
    const char *filename;
    const char *pos;
    const char *line_start;
    int         line;
} IncludeFrame;

#endif