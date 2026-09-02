#include "utils/dynamic/buffer_list.h"
#include "utils/file.h"

void buflist_init(BufferList *list) {
    list->items = NULL;
    list->capacity = 0;
    list->count = 0;
}

void bl_fill(CBuffer *buffer, struct FileData *data, Error throw) {
    buffer = malloc(sizeof(char) *  (data->length + 1));
    if (buffer == NULL) {
        throw("unable to allocate memory for data");
    }
    fread(buffer, 1, data->length, data->file);

    buffer[data->length] = '\0';
}

void bl_push(BufferList *list, struct FileData *data, char *filename, Error ferr) {
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;

        char **new_list = realloc(list->items, new_capacity * sizeof(char *));
        if (new_list == NULL) {
            ferr("run out of memory while performing reallocation of string list");
        }

        list->items = new_list;
        list->capacity = new_capacity;
    }

    bl_fill(list->items[list->count++], data, ferr);
}