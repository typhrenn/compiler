#include "utils/file.h"

void f_size(struct FileData *fileStructure, Error throw) {
    if (fileStructure->file == NULL) {
        throw("File is null, unable to get size\n");
    }
    fseek(fileStructure->file, 0, SEEK_END);
    fileStructure->length = ftell(fileStructure->file);
    fseek(fileStructure->file, 0, SEEK_SET);
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
}

void f_free(struct FileData *fileStruct) {
    fclose(fileStruct->file);
}

void f_init(struct FileData *data, const char *filename, Error ferr) {
    data->file = NULL;
    data->length = 0;
    data->filename = filename;

    f_fill(data, ferr);
}