#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h"
#include "utils/debug.h" 

void chckargc(int argc, Error throw) {
    if (argc < 2) throw("No arguments provided\n\texpected: compiler <input file>");
}

void compile(struct CoreData *c_data, struct ErrorHandler handler) {
    f_fill(c_data, handler.ferr);

    #ifdef DEBUG
        printf("This is the size of test file: %ld\n", c_data->length);
        f_out(c_data);
    #endif

    #ifdef BENCHMARK
		handler.ferr = dummy_exit;
        for (int i = 0; i < 1000000; i++) {
            lexer(c_data, handler);
        }
    #else
        lexer(c_data, handler);
    #endif

    ts_free(c_data->t_stream);
	f_free(c_data);
}

void setup(struct CoreData *c_data, struct ErrorHandler *handler, char *argv) {
    ts_init(c_data->t_stream);

    c_data->filename    = argv;
    c_data->file        = NULL;
    c_data->length      = 0;
    c_data->data        = NULL;

    handler->err            = err;
    handler->verr           = verbose_err;
    handler->ferr           = fatal_err;

    handler->fatal          = exit;

    handler->warning        = warning_log;
    handler->note           = note_log;
}

int main(int argc, char **argv) {
    struct CoreData c_data;
    struct ErrorHandler handler;

    chckargc(argc, fatal_err);
    setup(&c_data, &handler, argv[1]);
	compile(&c_data, handler);
}
