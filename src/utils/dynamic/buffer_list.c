#include "utils/dynamic/buffer_list.h"
#include "utils/file.h"

void bl_init(BufferList *list) {
    list->items = NULL;
    list->capacity = 0;
    list->count = 0;
}

void bl_fill(CBuffer **buffer, FileData *data, Error throw) {
    *buffer = malloc(sizeof(char) * (data->length + 1));
    if (*buffer == NULL) throw("unable to allocate memory for data");

    fread(*buffer, 1, data->length, data->file);
    (*buffer)[data->length] = '\0';
}

void bl_push(BufferList *list, FileData *data, char *filename, Error ferr) {
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;

        CBuffer **new_items = realloc(list->items, new_capacity * sizeof(CBuffer *));
        if (new_items == NULL) ferr("run out of memory while performing reallocation of buffer list");

        list->items = new_items;
        list->capacity = new_capacity;
    }

    bl_fill(&list->items[list->count], data, ferr);
    list->count++;
}