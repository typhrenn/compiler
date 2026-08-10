#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

typedef enum {
    IDENTIFIER,
    SYMBOL
} TokenType;

typedef struct {
    const char  *value;
    uint32_t    length;
    TokenType   type;
} Token;

bool check_format(char c);
void tokenize(struct FileData *fileStruct, VerboseError throw, Fatal fatal);

#endif