#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "error/error_handle.h"
#include "lexer/token.h"

struct CoreData {
    const char *filename;
    FILE *file;
    
    long length;
    char *data;

    TokenStream *t_stream;
};

void f_size(struct CoreData *fileStructure, Error throw);
void f_data(struct CoreData *fileStructure, Error throw);
void f_open(struct CoreData *fileStructure, Error throw);
void f_fill(struct CoreData *fileStruct, Error throw);
void f_out(struct CoreData *fileStruct);
void f_free(struct CoreData *fileStructure);

#endif