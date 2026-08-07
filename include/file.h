#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "error_handle.h"

struct FileData {
    char *filename;
    FILE *file;
    
    long length;
    char *data;
};

void f_size(struct FileData *fileStructure);
void f_data(struct FileData *fileStructure, Error throw);
void f_verify(struct FileData *fileStruct, Error throw);
void f_fill(struct FileData *fileStruct, Error throw);
void f_out(struct FileData *fileStruct);
void f_free(struct FileData *fileStructure);

#endif