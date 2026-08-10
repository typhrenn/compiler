#include "lexer.h"
#include "debug.h"

TokenType lookup_keyword(const char *text, size_t length) {
    for (size_t i = 0; i < KEYWORD_COUNT; i++) {
        if (keywords[i].length == length) {
            if (memcmp(keywords[i].name, text, length) == 0) {
                return keywords[i].type;
            }
        }
    }
    
    return TOKEN_IDENTIFIER; 
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

		// Identifiers and tokens
        if (token_start(*pos)) {
			while (token_body(*pos)) {
				pos++;
			}
			token.length = (int)(pos - token.value);

			token.type = lookup_keyword(token.value, token.length);
		} else if (isdigit((unsigned char)*pos)) {
				while (isdigit((unsigned char)*pos)) {
					pos++;
				}
				token.length = (int)(pos - token.value);
				token.type = TOKEN_NUMBER;
			} else {
			char c = *pos++;
			switch (c) {
				case '(': token.type = TOKEN_LPAREN; break;
				case ')': token.type = TOKEN_RPAREN; break;
				case '{': token.type = TOKEN_LBRACE; break;
				case '}': token.type = TOKEN_RBRACE; break;
				case '[': token.type = TOKEN_LBRACK; break;
				case ']': token.type = TOKEN_RBRACK; break;
				case ';': token.type = TOKEN_SEMICOLON; break;
				case '.': token.type = TOKEN_DOT; break;
				case ',': token.type = TOKEN_COMMA; break;

				default: {
					const char *line_end = line_start;
					while (*line_end != '\n' && *line_end != '\0') {
						line_end++;
					}
                    int line_len = (int)(line_end - line_start);

                    throw(
                        (Location){fileStruct->filename, lineCount, column},
                        strcnstr(line_start, line_len),
                        1,
                        "Unexpected character in source code: '%c'", c
                    );
                    fatalErr = true;
                    continue;
				}

			}
		}

        #ifdef DEBUG
        printf("Token %d (Line %d, Col %d): %.*s\n", 
               counter, lineCount, column, (int)token.length, token.value
		);
        counter++;
        #endif
    }

    if (fatalErr) {
        fatal(EXIT_FAILURE);
    }
}