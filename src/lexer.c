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
            // Basaed upon C23 / ISO/IEC 9899:2024 standard
			char c = *pos++;
			switch (c) {
				case '(': token.type = TOKEN_LPAREN; break; // function call
				case ')': token.type = TOKEN_RPAREN; break; 
				case '{': token.type = TOKEN_LBRACE; break; // compound statements & aggregate initializers
				case '}': token.type = TOKEN_RBRACE; break;
				case '[': token.type = TOKEN_LBRACK; break; // array subscripting
				case ']': token.type = TOKEN_RBRACK; break;
				case ';': token.type = TOKEN_SEMICOLON; break; // statement terminator
				case '.': token.type = TOKEN_DOT; break; // structure and union member access
				case ',': token.type = TOKEN_COMMA; break;
                case '~': token.type = TOKEN_TILDE; break; // bitwise NOT
                
                case '-': {
                    if (*pos == '>') {
                        pos++;
                        token.type = TOKEN_ARROW; // structure and union member access through pointer
                    } else if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_MINUS_EQUAL; // Assignment by difference
                    } else if (*pos == '-') {
                        pos++;
                        token.type = TOKEN_DECREMENT; // decrement
                    } else {
                        token.type = TOKEN_MINUS; // Subtraction or unary minus
                    }

                    break;
                }

                case '+': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_PLUS_EQUAL; // Assignment by sum
                    } else if (*pos == '+') {
                        pos++;
                        token.type = TOKEN_INCREMENT; // increment
                    } else {
                        token.type = TOKEN_PLUS; // Addition or unary plus
                    }

                    break;
                }

                case '!': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_EXCL_EQUAL; // relational operator not equal to
                    } else {
                        token.type = TOKEN_EXCL; // logical NOT
                    }

                    break;
                }

                case '*': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_ASTERISK_EQUAL; // Assignment by product
                    } else {
                        token.type = TOKEN_ASTERISK; // dereference and multiplication
                    }

                    break;
                }

                case '&': {
                    if (*pos == '&') {
                        pos++;
                        token.type = TOKEN_AMPERS_AMPERS; // Logical AND
                    } else if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_AMPERS_EQUAL; // Assignment by bitwise AND
                    } else {
                        token.type = TOKEN_AMPERS; // Bitwise AND and adress-of
                    }

                    break;
                }

                case '/': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_SLASH_EQUAL; // Assignment by quotient
                    } else if (*pos == '/') {
                        while (*pos != '\n' && *pos != '\0') {
                            pos++;
                        }
                    } else {
                        token.type = TOKEN_SLASH; // division
                    }

                    break;
                }

                case '%': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_PERC_EQUAL; // Assignment by reminder
                    } else {
                        token.type = TOKEN_PERC; // reminder
                    }

                    break;
                }

                case '<': {
                    if (*pos == '<') {
                        pos++;
                        if (*pos == '=') {
                            pos++;
                            token.type = TOKEN_LESS_LESS_EQUAL; // Assignment by bitwise left shift
                        } else {
                            token.type = TOKEN_LESS_LESS; // Bitwise left shift
                        }
                    } else if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_LESS_EQUAL; // relational operator less or equal to
                    } else {
                        token.type = TOKEN_LESS; // relational operator less
                    }

                    break;
                }

                case '>': {
                    if (*pos == '>') {
                        pos++;
                        if (*pos == '=') {
                            pos++;
                            token.type = TOKEN_MORE_MORE_EQUAL; // Assignment by bitwise right shift
                        } else {
                            token.type = TOKEN_MORE_MORE; // Bitwise right shift
                        }
                    } else if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_MORE_EQUAL; // relational operator more or equal to
                    } else {
                        token.type = TOKEN_MORE; // relational operator more
                    }

                    break;
                }

                case '=': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_EQUAL_EQUAL; // relational operator equal to
                    } else {
                        token.type = TOKEN_EQUAL; // Assignment operator
                    }

                    break;
                }

                case '^': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_CARET_EQUAL; // Assignment by bitwise XOR
                    } else {
                        token.type = TOKEN_CARET; // Logical XOR
                    }

                    break;
                }
    
                case '|': {
                    if (*pos == '=') {
                        pos++;
                        token.type = TOKEN_PIPE_EQUAL; // Assignment by bitwise OR
                    } else if (*pos == '|') {
                        pos++;
                        token.type = TOKEN_PIPE_PIPE; // Logical OR
                    } else {
                        token.type = TOKEN_PIPE; // Bitwise OR
                    }

                    break;
                }

                case '"': {
                    const char *line_end = line_start;
					while (*line_end != '\n' && *line_end != '\0') {
						line_end++;
					}
                    int line_len = (int)(line_end - line_start);
                    pos++; 

                    const char *start __attribute__((unused)) = pos;

                    while (*pos != '"' && *pos != '\0') {
                        if (*pos == '\\' && *(pos + 1) != '\0') {
                            pos++;
                        }
                        pos++;
                    }

                    if (*pos == '"') {
                        token.type = TOKEN_STRING_LITERAL;
                        pos++;
                    } else {
                        throw(
                            (Location){fileStruct->filename, lineCount, column},
                            strcnstr(line_start, line_len),
                            1,
                            "string literal not terminated properly"
                        );
                    }

                    break;
                }

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
                    break;
				}

			}
		}

        token.length = (int)(pos - token.value);

        #ifdef DEBUG
        printf("Token %d (Line %d, Col %d):\t%.*s\n", 
               counter, lineCount, column, (int)token.length, token.value
		);
        counter++;
        #endif
    }

    if (fatalErr) {
        fatal(EXIT_FAILURE);
    }
}