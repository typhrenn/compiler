#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef void (*ThrowError)(const char *msg);

void exit_fatal(const char *msg) {
    fprintf(stderr, "crashed with message %s\n", msg);
    exit(EXIT_FAILURE);
}

struct FileData {
    char *filename;
    FILE *file;
    
    long length;
    void *data;
};

void f_size(FILE *file, long *size) {
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);
}

void f_data(FILE *file) {

}

void verify_file_opened(struct FileData *fileStruct, ThrowError throw) {
    if (fileStruct->filename == NULL) {
        throw("filename is NULL");
    } 
    if (fileStruct->file == NULL) {
        throw("failed to open file (does it exist?)");
    }
}

void f_fill(struct FileData *fileStruct, ThrowError throw) {
    fileStruct->file = fopen(fileStruct->filename, "rb");
    verify_file_opened(fileStruct, throw);
    f_size(fileStruct->file, &fileStruct->length);
}
int main() {
    struct FileData fileStruct = {
        .filename = "test",
        .file = NULL,
        .length = 0,
        .data = NULL
    };
    f_fill(&fileStruct, exit_fatal);

    printf("This is the size of test file: %ld\n", fileStruct.length);
}