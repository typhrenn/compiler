#include "lexer/token.h"

void ts_init(TokenStream *list) {
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

void ts_push(TokenStream *list, Token token, Error ferr) {
	if (list->count == list->capacity) {
		size_t new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;

		Token *new_items = realloc(list->items, new_capacity*sizeof(Token));
		if (new_items == NULL) {
			ferr("run out of memory while performing reallocation of token stream capacity");
		}

		list->items = new_items;
		list->capacity = new_capacity;
	}

	list->items[list->count++] = token;
}

void ts_free(TokenStream *list) {
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}