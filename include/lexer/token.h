#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <ctype.h>

#include "error/error_handle.h"
#include "tokentype.h"


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

typedef struct {
    const char  *value;
    int		    length;
    TokenType   type;
} Token;

typedef struct {
	Token* 	items;
	int		count;
	int 	capacity;
} TokenStream;

void tl_init(TokenStream *list) {
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

void tl_push(TokenStream *list, Token token, Fatal fatal) {
	if (list->count == list->capacity) {
		size_t new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;

		Token *new_items = realloc(list->items, new_capacity*sizeof(Token));
		if (new_items == NULL) {
			error("run out of memory while performing reallocation of token stream capacity");
			fatal(EXIT_FAILURE);
		}

		list->items = new_items;
		list->capacity = new_capacity;
	}

	list->items[list->count++] = token;
}

void tl_free(TokenStream *list) {
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

#endif