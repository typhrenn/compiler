#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

#include "file.h"

typedef enum {
    FIRST,
    SECOND,
    IDENTIFIER,
    SYMBOL
} TokenType;

typedef struct {
    const char  *value;
    uint32_t    length;
    TokenType   type;
} Token;

bool check_format(char c);
void tokenize(struct FileData *fileStruct);

#endif