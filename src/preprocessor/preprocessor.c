#include "utils/file.h"
#include "utils/string/string_list.h"

typedef const char * Macro;

typedef struct {
    const char *key;
    size_t key_len;

    char **parameters;
    size_t p_count;

    Token *value;
    size_t v_count;
} MacroDef;

typedef struct {
    MacroDef *macro;

    size_t    count;
    size_t    capacity;
} MacroTable;

void preprocess(struct CoreData data) {

}