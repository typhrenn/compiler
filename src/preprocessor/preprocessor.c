#include "utils/file.h"
#include "utils/dynamic/string_list.h"

#include "preprocessor/preprocessor.h"

void setup_preprocessor(Preprocessor *pp, ErrorHandler handler, TokenStream *stream) {
    pp->handler = handler;
    pp->out = stream;
    pp->fatal_err = false;
}

void prepare_file(Preprocessor *pp, Error ferr, const char *filename, FileData *data) {

    // later a proper way to check for include loop should be implemented
    if (pp->depth == MAX_INCLUDE_DEPTH) ferr("compiler has reached max include depth, possible include loop encountered");

    // setup
    sl_push(&pp->included, filename, ferr);
    bl_push(&pp->buffers, data, filename, ferr);
    pp->stack[pp->depth] = (IncludeFrame){
        .filename = filename,
        .line = 0,
        .line_start = 0,

        .pos = pp->buffers.items[pp->buffers.count]
    };
}

void preprocess(FileData data, TokenStream *stream, ErrorHandler handler) {
    Preprocessor pp;
    setup_preprocessor(&pp, handler, stream);

    Token buffer;
}