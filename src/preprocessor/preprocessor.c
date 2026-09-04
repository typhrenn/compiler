#include "utils/file.h"
#include "utils/dynamic/string_list.h"

#include "preprocessor/preprocessor.h"

void setup_preprocessor(Preprocessor *pp, TokenStream *stream, ErrorHandler *handler) {
    pp->handler = handler;
    pp->out = stream;
    pp->fatal_err = false;
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

void preprocess(FileData *data, TokenStream *stream, ErrorHandler *handler) {
    Preprocessor pp;
    Token buffer;

    setup_preprocessor(&pp, stream, handler);

    prepare_file(&pp, data->filename, data, handler->ferr);
}