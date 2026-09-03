#ifndef __BUFFER_LIST_H__
#define __BUFFER_LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "error/error_handle.h"

typedef char * CBuffer;

typedef struct {
    CBuffer *items;
    size_t count;
    size_t capacity;
} BufferList;

void bl_init(BufferList *list);
void bl_fill(CBuffer *buffer, FileData *data, Error throw);
void bl_push(BufferList *list, FileData *data, char *filename, Error ferr);

#endif