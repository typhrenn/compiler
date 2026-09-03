#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "error/error_handle.h"
#include "lexer/token.h"

typedef struct {
    const char *filename;
    FILE *file;
    
    size_t length;
} FileData;

void f_size(FileData *fileStructure, Error throw);
void f_open(FileData *fileStructure, Error throw);
void f_fill(FileData *fileStruct, Error throw);
void f_out(FileData *fileStruct);
void f_free(FileData *fileStructure);

#endif