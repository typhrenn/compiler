#include "lexer.h"
#include "debug.h"

bool check_format(char c) {
    return isalnum((unsigned char)c) || c == '_' || c == '-';
}

void tokenize(struct FileData *fileStruct, VerboseError throw, Fatal fatal) {
    const char *pos = fileStruct->data;
    const char *line_start = fileStruct->data;
    int lineCount = 1;
    bool fatalErr = false;

    int counter __attribute__((unused)) = 1;

    while (*pos != '\0') {
        if (*pos == '\n') {
            pos++;
            lineCount++;
            line_start = pos;
            continue;
        } 

        // Check for white spaces
        if (isspace((unsigned char)*pos)) {
            pos++;
            continue;
        }

        Token token;
        token.value = pos;

        int column = (int)(token.value - line_start) + 1;

        // Check if the token starts with a letter, if so it's an identifier
        if (isalpha((unsigned char)*pos) || (unsigned char)*pos == '_') {
            const char *start = pos;

            while (check_format(*pos)) {
                pos++;
            }

            token.length = pos - token.value;

            if (!isspace((unsigned char)*pos)) {
                    const char *line_end = line_start;
                    while (*line_end != '\n' && *line_end != '\0') {
                        line_end++;
                    }
                    int line_len = (int)(line_end - line_start);
                    throw(
                        (Location){fileStruct->filename, lineCount, column},
                        strcnstr(line_start, line_len),
                        token.length,
                        "Identifier cannot have a symbol other than letter, numer, underscore or hyphen inside itself: '%.*s'", (int)token.length, token.value
                    );

                    while (*pos != '\0' && !isspace((unsigned char)*pos)) {
                        pos++;
                    }

                    fatalErr = true;
                    continue;
            }

            if (pos > start) {
                // Check if last char is an allowed character
                if (!isalnum((unsigned char)*(pos - 1))) {
                    const char *line_end = line_start;
                    while (*line_end != '\n' && *line_end != '\0') {
                        line_end++;
                    }
                    int line_len = (int)(line_end - line_start);

                    throw(
                        (Location){fileStruct->filename, lineCount, column},
                        strcnstr(line_start, line_len),
                        token.length,
                        "Identifier must end with a letter or number: '%.*s'", (int)token.length, token.value
                    );

                    fatalErr = true;
                    continue;
                }
            }

            token.type = IDENTIFIER;
        } else {
            pos++; 
            token.length = 1;
            token.type = SYMBOL;
        }

        #ifdef DEBUG
        printf("Token %d (Line %d, Col %d): %.*s\n", 
               counter, lineCount, column, (int)token.length, token.value);
        counter++;
        #endif
    }

    if (fatalErr) {
        fatal(EXIT_FAILURE);
    }
}