#include "lexer.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

bool check_format(char c) {
    return isalnum((unsigned char)c) || c == '_' || c == '-';
}

void tokenize(struct FileData *fileStruct, VerboseError throw) {
    const char *pos = fileStruct->data;
    const char *line_start = fileStruct->data;
    int counter = 1;
    int lineCount = 1;

    while (*pos != '\0') {
        if (*pos == '\n') {
            pos++;
            lineCount++;
            line_start = pos;
            continue;
        } 

        if (isspace((unsigned char)*pos)) {
            pos++;
            continue;
        }

        Token token;
        token.value = pos;

        int column = (int)(token.value - line_start) + 1;

        if (isalpha((unsigned char)*pos)) {
            const char *start = pos;

            while (check_format(*pos)) {
                pos++;
            }

            if (pos > start) {
                if (!isalnum((unsigned char)*(pos - 1))) {
                    const char *line_end = line_start;
                    while (*line_end != '\n' && *line_end != '\0') {
                        line_end++;
                    }
                    int line_len = (int)(line_end - line_start);

                    throw(
                        (Location){fileStruct->filename, lineCount, column},
                        strcnstr(line_start, line_len),
                        "Identifier must end with a letter or number: '%.*s'", (int)(pos - token.value), token.value
                    );
                }
            }

            token.length = pos - token.value;
            token.type = IDENTIFIER;
        } else {
            pos++; 
            token.length = 1;
            token.type = SYMBOL;
        }

        printf("Token %d (Line %d, Col %d): %.*s\n", 
               counter, lineCount, column, (int)token.length, token.value);
        counter++;
    }
}