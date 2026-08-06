#include "lexer.h"
#include <string.h>
#include <ctype.h>

bool check_format(char c) {
    return isalnum(c) || c == '_' || c == '-';
}

void tokenize(struct FileData *fileStruct, ThrowError throw) {
    const char *pos = fileStruct->data;
    int counter = 1;
    int line = 1;

    while (*pos != '\0') {
        const char *linec = pos;

        if (*pos == '\n') {
            pos++;
            line++;
            continue;
        } else if (isspace(*pos)) {
            pos++;
            continue;
        }

        Token token;
        token.value = pos;

        if (isalpha(*pos)) {
            const char *start = pos;

            while (check_format(*pos)) {
                pos++;
            }

            if (pos > start) {
                if (!isalnum((unsigned char)*(pos - 1))) throw("Incorrect identifier format, an identifier must end with either a letter or a number: \n At line %d: \"%.*s\"", line, (int)(pos - token.value - 1), token.value);
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