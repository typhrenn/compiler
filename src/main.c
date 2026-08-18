#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h"
#include "utils/debug.h" 

void chckargc(int argc, Error throw) {
    if (argc < 2) throw("No arguments provided\n");
}

void compile(struct FileData *fileStruct, struct ErrorHandler handler) {
    f_fill(fileStruct, handler.ferr);

    #ifdef DEBUG
        printf("This is the size of test file: %ld\n", fileStruct->length);
        f_out(fileStruct);
    #endif

    #ifdef BENCHMARK
		handler.ferr = dummy_exit;
        for (int i = 0; i < 1000000; i++) {
            lexer(fileStruct, handler);
        }
    #else
        lexer(fileStruct, handler);
    #endif

	f_free(fileStruct);
}

void setup(struct FileData *fileStruct, struct ErrorHandler *handler, char *argv) {
    fileStruct->filename    = argv;
    fileStruct->file        = NULL;
    fileStruct->length      = 0;
    fileStruct->data        = NULL;

    handler->err            = err;
    handler->verr           = verbose_err;
    handler->ferr           = fatal_err;

    handler->fatal          = exit;

    handler->warning        = warning_log;
    handler->note           = note_log;
}

int main(int argc, char **argv) {
    struct FileData fileStruct;
    struct ErrorHandler handler;

    chckargc(argc, fatal_err);
    setup(&fileStruct, &handler, argv[1]);
	compile(&fileStruct, handler);
}