#ifndef UTILS_H
#define UTILS_H

typedef struct {
    char *string;
    int len;
} String;

static inline String strcnstr(char *string, int len) {
    return (String){string, len};
}

#endif