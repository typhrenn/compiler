#include "file.h"

struct FileData {
    char *filename;
    FILE *file;
    
    long length;
    char *data;
};

void f_size(struct FileData *fileStructure) {
    fseek(fileStructure->file, 0, SEEK_END);
    fileStructure->length = ftell(fileStructure->file);
    fseek(fileStructure->file, 0, SEEK_SET);
}

void f_data(struct FileData *fileStructure, ThrowError throw) {
    fileStructure->data = malloc(sizeof(char) * fileStructure->length + 1);
    if (fileStructure->data == NULL) {
        throw("unable to allocate memory for data");
    }
    fread(fileStructure->data, 1, fileStructure->length, fileStructure->file);

    fileStructure->data[fileStructure->length] = '\0';
}

void f_verify(struct FileData *fileStruct, ThrowError throw) {
    if (fileStruct->filename == NULL) {
        throw("filename is NULL");
    } 
    if (fileStruct->file == NULL) {
        throw("failed to open file");
    }
}

void f_fill(struct FileData *fileStruct, ThrowError throw) {
    fileStruct->file = fopen(fileStruct->filename, "rb");
    f_verify(fileStruct, throw);
    f_size(fileStruct);
    f_data(fileStruct, log_error);
}

void f_out(struct FileData *fileStruct) {
    for (int i = 0; i < fileStruct->length; i++) {
        printf("%c", fileStruct->data[i]);
    }
    printf("\n");
}

void f_free(struct FileData *fileStruct) {
    free(fileStruct->data);
    fclose(fileStruct->file);
}