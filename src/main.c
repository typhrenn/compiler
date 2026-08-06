#include "file.h"
#include "error_handle.h"
#include "lexer.h"

int main() {
    struct FileData fileStruct = {
        .filename = "test.txt",
        .file = NULL,
        .length = 0,
        .data = NULL
    };
    f_fill(&fileStruct, log_error);

    printf("This is the size of test file: %ld\n", fileStruct.length);

    f_out(&fileStruct);

    tokenize(&fileStruct, log_error);

    f_free(&fileStruct);
}