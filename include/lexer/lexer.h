#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/file.h"
#include "token.h"

typedef struct {
    const char *name;
    size_t      length;
    TokenType   type;
} Keyword;

static const Keyword keywords[] = {
	{"void",	 4, TOKEN_VOID},
	{"const",	 5, TOKEN_CONST},
	{"bool",	 4, TOKEN_BOOL},

	{"int8",	 4,	TOKEN_INT8},
	{"int16",	 5,	TOKEN_INT16},
	{"int32",	 5,	TOKEN_INT32},
	{"int64",	 5,	TOKEN_INT64},
	{"uint8",	 5,	TOKEN_UINT8},
	{"uint16",	 6,	TOKEN_UINT16},
	{"uint32",	 6,	TOKEN_UINT32},
	{"uint64",	 6,	TOKEN_UINT64},

	{"float32",	 7,	TOKEN_FLOAT32},
	{"float64",	 7,	TOKEN_FLOAT64},

	{"char",	 4, TOKEN_CHAR},
	{"uchar",	 5, TOKEN_UCHAR},

    {"func",     4, TOKEN_FUNC},
    {"typedef",  7, TOKEN_TYPEDEF},
    {"struct",   6, TOKEN_STRUCT},
    {"return",   6, TOKEN_RETURN},
    {"if",       2, TOKEN_IF},
    {"else",     4, TOKEN_ELSE},
	{"for",		 3, TOKEN_FOR},
    {"while",    5, TOKEN_WHILE},
    {"break",    5, TOKEN_BREAK},
    {"continue", 8, TOKEN_CONTINUE},
    {"true",     4, TOKEN_TRUE},
    {"false",    5, TOKEN_FALSE},
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

TokenType lookup_keyword(const char *text, size_t length);

void lexer(struct FileData *fileStruct, struct ErrorHandler handler);

#endif