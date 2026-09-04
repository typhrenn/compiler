#include "utils/file.h"
#include "utils/dynamic/string_list.h"

#include "preprocessor/preprocessor.h"
#include "parameters/parameters.h"

#define CURRENT_DIR .

const char *create_path(const char *include, Token *token) {
    size_t include_len = strlen(include);
    size_t len = include_len + token->length + 2;

    char *res = malloc(sizeof(char) * len);

    int counter = 0;
    
    for (int i = 0; i < include_len; i++) res[counter++] = include[i];
    res[counter++] = '/';
    for (int i = 0; i < token->length; i++) res[counter++] = token->value[i];
    res[counter++] = '\0';

    return res;
}

void next_pp_directive(IncludeFrame *frame) {

}

bool check_include(Token *token, TargetList *includes, const char *out) {
    for (int i = 0; i < includes->count; i++) {

    }
}



void prepare_file(Preprocessor *pp, const char *filename, FileData *data, Error ferr) {
    // !todo a proper logic for finding include loops needs to be included later
    if (pp->depth == MAX_INCLUDE_DEPTH) ferr("compiler has reached max include depth, possible include loop encountered");

    sl_push(&pp->included, filename, ferr);
    bl_push(&pp->buffers, data, filename, ferr);

    char *buf = pp->buffers.items[pp->buffers.count - 1];

    pp->stack[pp->depth] = (IncludeFrame){
        .filename   = filename,
        .line       = 1,
        .line_start = buf,
        .pos        = buf
    };
    pp->depth++;
}

void setup_preprocessor(Preprocessor *pp, TokenStream *stream, ErrorHandler *handler) {
    pp->handler = handler;
    pp->out = stream;
    pp->fatal_err = false;
}

void preprocess(FileData *data, TokenStream *stream, ErrorHandler *handler) {
    Preprocessor pp;
    Token buffer;

    setup_preprocessor(&pp, stream, handler);

    prepare_file(&pp, data->filename, data, handler->ferr);
}