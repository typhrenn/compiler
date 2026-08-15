#include "utils/file.h"
#include "error/error_handle.h"
#include "lexer/lexer.h"
#include "utils/debug.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        error("No arguments provided\n");
    }
    struct FileData fileStruct = {
        .filename = argv[1],
        .file = NULL,
        .length = 0,
        .data = NULL
    };
    f_fill(&fileStruct, error);

    #ifdef DEBUG
    printf("This is the size of test file: %ld\n", fileStruct.length);
    f_out(&fileStruct);
    #endif

    #ifdef BENCHMARK
    for (int i = 0; i < 1000000; i++) {
        lexer(&fileStruct, verror, dummy_exit);
    }
    #else
    lexer(&fileStruct, verror, exit);
    #endif

    f_free(&fileStruct);
}