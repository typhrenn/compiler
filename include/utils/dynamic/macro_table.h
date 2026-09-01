#ifndef __MACRO_TABLE_H__
#define __MACRO_TABLE_H__

#include <stdlib.h>

#include "lexer/token.h"

typedef const char * Macro;

typedef struct {
    const char *key;
    size_t key_len;

    char **parameters;
    size_t p_count;

    Token *value;
    size_t v_count;
} MacroDef;

typedef struct {
    MacroDef *macro;

    size_t    count;
    size_t    capacity;
} MacroTable;

void macro_construct(MacroDef *macro, Token key, Token *value);

#endif