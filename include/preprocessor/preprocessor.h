#ifndef __PREPROCESSOR_H__
#define __PREPROCESSOR_H__

#include "utils/utils.h"
#include "utils/dynamic/buffer_list.h"
#include "utils/dynamic/macro_table.h"
#include "utils/dynamic/string_list.h"

#include "error/error_handle.h"

#define MAX_INCLUDE_DEPTH 10

typedef struct {
    IncludeFrame    stack[MAX_INCLUDE_DEPTH];
    int             depth;

    MacroTable      macros;
    StringList      included;
    BufferList      buffers;

    TokenStream     *out;

    ErrorHandler    handler;
    bool            fatal_err;
} Preprocessor;

void preprocess(FileData data, TokenStream *stream);

#endif