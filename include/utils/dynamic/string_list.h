#ifndef __STRING_LIST_H__
#define __STRING_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error/error_handle.h"
#include "lexer/token.h"
#include "utils/utils.h"

typedef struct {
	String *list;

	size_t count;
	size_t capacity;
} StringList;

void sl_init(StringList *stream);
void sl_push(StringList *stream, char *string, Error ferr);
void sl_free(StringList *stream);

#endif