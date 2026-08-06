#include "lexer.h"
#include <string.h>
#include <ctype.h>

bool check_format(char c) {
    return isalnum(c) || c == '_';
} 

void tokenize(struct FileData *fileStruct) {
    const char *pos = fileStruct->data;
    int counter = 1;

    while (*pos != '\0') {
        if (isspace(*pos)) {
            pos++;
            continue;
        }

        Token token;
        token.value = pos;

        if (isalpha(*pos)) {
            while (check_format(*pos)) {
                pos++;
            }

            token.length = pos - token.value;
            token.type = IDENTIFIER;
        } else {
            pos++; 
            token.length = 1;
            token.type = SYMBOL;
        }

        printf("Token %d: %.*s\n", counter, (int)token.length, token.value);
        counter++;
    }
}