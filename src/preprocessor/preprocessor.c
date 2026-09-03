#include "utils/file.h"
#include "utils/dynamic/string_list.h"

#include "preprocessor/preprocessor.h"

void new_file(Preprocessor *pp, Error ferr, const char *filename, FileData *data) {
    // later a proper way to check for include loop should be implemented
    if (pp->depth == MAX_INCLUDE_DEPTH) ferr("compiler has reached max include depth, possible include loop encountered");

    bl_push(&pp->buffers, data, filename, ferr);

    pp->stack[pp->depth] = (IncludeFrame){
        .filename = filename,
        .line = 0,
        .line_start = 0,

        .pos = pp->buffers.items[pp->buffers.count]
    };
}

void preprocess(FileData data, TokenStream *stream) {
    Preprocessor pp;
    
    
}