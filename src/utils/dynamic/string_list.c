#include "utils/dynamic/string_list.h"

void sl_init(StringList *stream) {
    stream->list = NULL;
    stream->count = 0;
    stream->capacity = 0;
}

void sl_push(StringList *stream, char *string, Error ferr) {
    if (stream->count == stream->capacity) {
        size_t new_capacity = stream->capacity == 0 ? 16 : stream->capacity * 2;

        char **new_list = realloc(stream->list, new_capacity * sizeof(char *));
        if (new_list == NULL) {
            ferr("run out of memory while performing reallocation of string list");
        }

        stream->list = new_list;
        stream->capacity = new_capacity;
    }

    stream->list[stream->count++] = string;
}

void sl_free(StringList *stream) {
    if (stream == NULL) return;

    free(stream->list);
    stream->list = NULL;
    stream->count = 0;
    stream->capacity = 0;
}