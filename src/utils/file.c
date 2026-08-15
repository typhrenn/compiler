#include "utils/file.h"

void f_size(struct FileData *fileStructure, Error throw) {
    if (fileStructure->file == NULL) {
        throw("File is null, unable to get size\n");
    }
    fseek(fileStructure->file, 0, SEEK_END);
    fileStructure->length = ftell(fileStructure->file);
    fseek(fileStructure->file, 0, SEEK_SET);
}

void f_data(struct FileData *fileStructure, Error throw) {
    fileStructure->data = malloc(sizeof(char) * fileStructure->length + 1);
    if (fileStructure->data == NULL) {
        throw("unable to allocate memory for data");
    }
    fread(fileStructure->data, 1, fileStructure->length, fileStructure->file);

    fileStructure->data[fileStructure->length] = '\0';
}

void f_open(struct FileData *fileStruct, Error throw) {
    if (fileStruct->filename == NULL) {
        throw("No filename provided\n");
    }
    fileStruct->file = fopen(fileStruct->filename, "rb");
    if (fileStruct->file == NULL) {
        throw("Unable to open the file\n");
    }
}

void f_fill(struct FileData *fileStruct, Error throw) {
    f_open(fileStruct, throw);
    f_size(fileStruct, throw);
    f_data(fileStruct, throw);
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