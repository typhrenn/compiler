#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h"
#include "utils/debug.h" 

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

int main(int argc, char **argv) {
    if (argc < 2) {
        fatal_err("No arguments provided\n");
    }

    struct FileData fileStruct = {
        .filename = argv[1],
        .file = NULL,
        .length = 0,
        .data = NULL
    };

	struct ErrorHandler handler = {
		.err = err,
		.verr = verbose_err,
		.ferr = fatal_err,
		
		.fatal = exit,

		.warning = warning_log,
		.note = note_log
	};

	compile(&fileStruct, handler);
}