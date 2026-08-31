#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h"
#include "utils/debug.h" 
#include "parameters/parameters.h"

void setup_handler(struct ErrorHandler *handler) {
    handler->err     = err;
    handler->verr    = verbose_err;
    handler->ferr    = fatal_err;
    handler->fatal   = exit;
    handler->warning = warning_log;
    handler->note    = note_log;
}

void compile(const char *filename, TargetList *includes, struct ErrorHandler handler) {
    struct CoreData c_data;
    TokenStream stream;
    c_data.t_stream = &stream;

#ifdef BENCHMARK
    struct ErrorHandler bench_handler = handler;
    bench_handler.ferr = dummy_exit;

    for (int i = 0; i < 1000000; i++) {
        ts_init(c_data.t_stream);
        c_data.filename = filename;
        c_data.file     = NULL;
        c_data.length   = 0;
        c_data.data     = NULL;

        f_fill(&c_data, bench_handler.ferr);
        lexerize(&c_data, bench_handler);

        ts_free(c_data.t_stream);
        f_free(&c_data);
    }
    return;
#endif

    ts_init(c_data.t_stream);
    c_data.filename = filename;
    c_data.file     = NULL;
    c_data.length   = 0;
    c_data.data     = NULL;

    f_fill(&c_data, handler.ferr);
    lexerize(&c_data, handler);

    ts_free(c_data.t_stream);
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