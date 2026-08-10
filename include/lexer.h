#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

typedef enum {
    // basic types and const
    TOKEN_VOID,
    TOKEN_CONST,
    TOKEN_BOOL,

    // int type
    TOKEN_INT8,
    TOKEN_INT16,
    TOKEN_INT32,
    TOKEN_INT64,
    TOKEN_UINT8,
    TOKEN_UINT16,
    TOKEN_UINT32,
    TOKEN_UINT64,

    // float type
    TOKEN_FLOAT32,
    TOKEN_FLOAT64,

    // char type
    TOKEN_CHAR,
    TOKEN_UCHAR,

    // Declaratins
    TOKEN_FUNC,
    TOKEN_TYPEDEF,
    TOKEN_STRUCT,

    // Control flow
    TOKEN_RETURN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_BREAK,
    TOKEN_CONTINUE,

    // Boolean literals
    TOKEN_TRUE,
    TOKEN_FALSE,
	TOKEN_NUMBER,
	TOKEN_IDENTIFIER,

	// SYMBOLS
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_LBRACE,
	TOKEN_RBRACE,
	TOKEN_LBRACK,
	TOKEN_RBRACK,
	TOKEN_SEMICOLON,
	TOKEN_DOT,
	TOKEN_COMMA
} TokenType;

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

typedef struct {
    const char  *value;
    int		    length;
    TokenType   type;
} Token;

TokenType lookup_keyword(const char *text, size_t length);

// MULTI-TOKEN SYNTAX
static inline bool token_start(char c) {
    return isalpha((unsigned char)c) || c == '_';
}

// Valid continuing character for an Identifier
static inline bool token_body(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

// Unary prefix operators (can start an expression)
static inline bool token_unary_prefix(char c) {
    return c == '!' || c == '~' || c == '-' || c == '+' || c == '*' || c == '&';
}

void tokenize(struct FileData *fileStruct, VerboseError throw, Fatal fatal);

#endif