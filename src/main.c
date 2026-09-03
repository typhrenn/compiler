#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h" 
#include "parameters/parameters.h"
#include "preprocessor/preprocessor.h"

void setup_handler(ErrorHandler *handler) {
    handler->err     = err;
    handler->verr    = verbose_err;
    handler->ferr    = fatal_err;
    handler->fatal   = exit;
    handler->warning = warning_log;
    handler->note    = note_log;
}

void compile(const char *filename, TargetList *includes, ErrorHandler handler) {
    FileData c_data;
    TokenStream stream;

    // initialization of token stream and file data
    ts_init(&stream);
    f_init(c_data);

    preprocess(c_data, &stream);

    ts_free(&stream);
    f_free(&c_data);
}

int main(int argc, char **argv) {
    ErrorHandler handler;
    CompileInfo info;

    chckargs(&info, argc, argv, fatal_err);
	print_ci(&info);
    setup_handler(&handler);

    for (int i = 0; i < info.source.count; i++) {
        compile(info.source.target[i], &info.include, handler);
    }

    free_ci(&info);
}