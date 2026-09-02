#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "error/error_handle.h"
#include "lexer/token.h"

struct FileData {
    const char *filename;
    FILE *file;
    
    long length;
};

void f_size(struct FileData *fileStructure, Error throw);
void f_open(struct FileData *fileStructure, Error throw);
void f_fill(struct FileData *fileStruct, Error throw);
void f_out(struct FileData *fileStruct);
void f_free(struct FileData *fileStructure);

#endif