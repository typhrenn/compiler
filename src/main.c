#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h"
#include "utils/debug.h" 
#include "parameters/parameters.h"
#include "preprocessor/preprocessor.h"

void setup_handler(struct ErrorHandler *handler) {
    handler->err     = err;
    handler->verr    = verbose_err;
    handler->ferr    = fatal_err;
    handler->fatal   = exit;
    handler->warning = warning_log;
    handler->note    = note_log;
}

void compile(const char *filename, TargetList *includes, struct ErrorHandler handler) {
    struct FileData c_data;
    TokenStream stream;
    Preprocessor pp;

    ts_init(&stream);
    f_init(c_data);

    
    lexerize(&c_data, handler);

    ts_free(&stream);
    f_free(&c_data);
}

int main(int argc, char **argv) {
    struct ErrorHandler handler;
    CompileInfo info;

    chckargs(&info, argc, argv, fatal_err);
	print_ci(&info);
    setup_handler(&handler);

    for (int i = 0; i < info.source.count; i++) {
        compile(info.source.target[i], &info.include, handler);
    }

    free_ci(&info);
    return 0;
}