#include "lexer/lexer.h"
#include "utils/debug.h"
#include "lexer/token.h"

TokenType lookup_keyword(const char *text, size_t length) {
    switch (text[0]) {
        case '#': {
            if (length == 3 && memcmp(text, "#if", 3) == 0) return PP_IF;
            if (length == 5 && memcmp(text, "#elif", 5) == 0) return PP_ELIF;
            if (length == 5 && memcmp(text, "#else", 5) == 0) return PP_ELSE;
            if (length == 6 && memcmp(text, "#endif", 6) == 0) return PP_ENDIF;
            if (length == 6 && memcmp(text, "#ifdef", 6) == 0) return PP_IFDEF;
            if (length == 7 && memcmp(text, "#ifndef", 7) == 0) return PP_IFNDEF;
            if (length == 8 && memcmp(text, "#elifdef", 8) == 0) return PP_ELIFDEF;
            if (length == 9 && memcmp(text, "#elifndef", 9) == 0) return PP_ELIFNDEF;
            if (length == 8 && memcmp(text, "#include", 8) == 0) return PP_INCLUDE;
            if (length == 7 && memcmp(text, "#define", 7) == 0) return PP_DEFINE;
            break;
        }
        case 'b': {
            if (length == 4 && memcmp(text, "bool", 4) == 0) return TOKEN_BOOL;
            if (length == 5 && memcmp(text, "break", 5) == 0) return TOKEN_BREAK;
			break;
        }
        case 'c': {
            if (length == 4 && memcmp(text, "char", 4) == 0) return TOKEN_CHAR;
            if (length == 5 && memcmp(text, "const", 5) == 0) return TOKEN_CONST;
            if (length == 8 && memcmp(text, "continue", 8) == 0) return TOKEN_CONTINUE;
			break;
        }
        case 'e': {
            if (length == 4 && memcmp(text, "else", 4) == 0) return TOKEN_ELSE;
			break;
        }
        case 'f': {
            if (length == 5 && memcmp(text, "false", 5) == 0) return TOKEN_FALSE;
            if (length == 7) {
                if (memcmp(text, "float32", 7) == 0) return TOKEN_FLOAT32;
                if (memcmp(text, "float64", 7) == 0) return TOKEN_FLOAT64;
            }
            if (length == 3 && memcmp(text, "for", 3) == 0) return TOKEN_FOR;
            if (length == 4 && memcmp(text, "func", 4) == 0) return TOKEN_FUNC;
			break;
        }
        case 'i': {
            if (length == 2 && text[1] == 'f') return TOKEN_IF;
            if (length == 4 && memcmp(text, "int8", 4) == 0) return TOKEN_INT8;
            if (length == 5) {
                if (memcmp(text, "int16", 5) == 0) return TOKEN_INT16;
                if (memcmp(text, "int32", 5) == 0) return TOKEN_INT32;
                if (memcmp(text, "int64", 5) == 0) return TOKEN_INT64;
            }
			break;
        }
        case 'r': {
            if (length == 6 && memcmp(text, "return", 6) == 0) return TOKEN_RETURN;
			break;
        }
        case 's': {
            if (length == 6 && memcmp(text, "struct", 6) == 0) return TOKEN_STRUCT;
			break;
        }
        case 't': {
            if (length == 4 && memcmp(text, "true", 4) == 0) return TOKEN_TRUE;
            if (length == 7 && memcmp(text, "typedef", 7) == 0) return TOKEN_TYPEDEF;
			break;
        }
        case 'u': {
            if (length == 5 && memcmp(text, "uint8", 5) == 0) return TOKEN_UINT8;
            if (length == 6) {
                if (memcmp(text, "uint16", 6) == 0) return TOKEN_UINT16;
                if (memcmp(text, "uint32", 6) == 0) return TOKEN_UINT32;
                if (memcmp(text, "uint64", 6) == 0) return TOKEN_UINT64;
            }
			break;
        }
        case 'v': {
            if (length == 4 && memcmp(text, "void", 4) == 0) return TOKEN_VOID;
			break;
        }
        case 'w': {
            if (length == 5 && memcmp(text, "while", 5) == 0) return TOKEN_WHILE;
			break;
        }
    }
    
    return TOKEN_IDENTIFIER; 
}

void lexerize(struct FileData *fileStruct, struct ErrorHandler handler) {
    IncludeFrame frame = {
        .filename   = fileStruct->filename,
        .pos        = fileStruct->data,
        .line_start = fileStruct->data,
        .line       = 1
    };

    bool fatalErr = false;

    int counter __attribute__((unused)) = 1;

    while (*frame.pos != '\0') {
		// newline token for preprocessor
		if (*frame.pos == '\n') {
			frame.pos++;
			frame.line++;
			frame.line_start = frame.pos;
			ts_push(fileStruct->t_stream, (Token){frame.pos, 1, TOKEN_NEWLINE}, handler.ferr);
			continue;
		}

        // Check for white spaces
        if (isspace((unsigned char)*frame.pos)) {
            frame.pos++;
            continue;
        }

        Token token;
        token.value = frame.pos;
		int column = (int)(token.value - frame.line_start) + 1;

		// Identifiers and tokens
        if (token_start(*frame.pos)) {
			do {
				frame.pos++;
			} while (token_body(*frame.pos));
			token.length = (int)(frame.pos - token.value);

			token.type = lookup_keyword(token.value, token.length);
		} else if (isdigit((unsigned char)*frame.pos)) {
				while (isdigit((unsigned char)*frame.pos)) {
					frame.pos++;
				}
				token.length = (int)(frame.pos - token.value);
				token.type = TOKEN_NUMBER;
			} else {
            // Based upon C23 / ISO/IEC 9899:2024 standard
			char c = *frame.pos++;
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
                    if (*frame.pos == '>') {
                        frame.pos++;
                        token.type = TOKEN_ARROW; // structure and union member access through pointer
                    } else if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_MINUS_EQUAL; // Assignment by difference
                    } else if (*frame.pos == '-') {
                        frame.pos++;
                        token.type = TOKEN_DECREMENT; // decrement
                    } else {
                        token.type = TOKEN_MINUS; // Subtraction or unary minus
                    }

                    break;
                }

                case '+': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_PLUS_EQUAL; // Assignment by sum
                    } else if (*frame.pos == '+') {
                        frame.pos++;
                        token.type = TOKEN_INCREMENT; // increment
                    } else {
                        token.type = TOKEN_PLUS; // Addition or unary plus
                    }

                    break;
                }

                case '!': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_EXCL_EQUAL; // relational operator not equal to
                    } else {
                        token.type = TOKEN_EXCL; // logical NOT
                    }

                    break;
                }

                case '*': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_ASTERISK_EQUAL; // Assignment by product
                    } else {
                        token.type = TOKEN_ASTERISK; // dereference and multiplication
                    }

                    break;
                }

                case '&': {
                    if (*frame.pos == '&') {
                        frame.pos++;
                        token.type = TOKEN_AMPERS_AMPERS; // Logical AND
                    } else if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_AMPERS_EQUAL; // Assignment by bitwise AND
                    } else {
                        token.type = TOKEN_AMPERS; // Bitwise AND and adress-of
                    }

                    break;
                }

                case '/': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_SLASH_EQUAL; // Assignment by quotient
                    } else if (*frame.pos == '/') {
                        while (*frame.pos != '\n' && *frame.pos != '\0') {
                            frame.pos++;
                        }
						continue;
                    } else {
                        token.type = TOKEN_SLASH; // division
                    }

                    break;
                }

                case '%': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_PERC_EQUAL; // Assignment by reminder
                    } else {
                        token.type = TOKEN_PERC; // reminder
                    }

                    break;
                }

                case '<': {
                    if (*frame.pos == '<') {
                        frame.pos++;
                        if (*frame.pos == '=') {
                            frame.pos++;
                            token.type = TOKEN_LESS_LESS_EQUAL; // Assignment by bitwise left shift
                        } else {
                            token.type = TOKEN_LESS_LESS; // Bitwise left shift
                        }
                    } else if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_LESS_EQUAL; // relational operator less or equal to
                    } else {
                        token.type = TOKEN_LESS; // relational operator less
                    }

                    break;
                }

                case '>': {
                    if (*frame.pos == '>') {
                        frame.pos++;
                        if (*frame.pos == '=') {
                            frame.pos++;
                            token.type = TOKEN_MORE_MORE_EQUAL; // Assignment by bitwise right shift
                        } else {
                            token.type = TOKEN_MORE_MORE; // Bitwise right shift
                        }
                    } else if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_MORE_EQUAL; // relational operator more or equal to
                    } else {
                        token.type = TOKEN_MORE; // relational operator more
                    }

                    break;
                }

                case '=': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_EQUAL_EQUAL; // relational operator equal to
                    } else {
                        token.type = TOKEN_EQUAL; // Assignment operator
                    }

                    break;
                }

                case '^': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_CARET_EQUAL; // Assignment by bitwise XOR
                    } else {
                        token.type = TOKEN_CARET; // Logical XOR
                    }

                    break;
                }
    
                case '|': {
                    if (*frame.pos == '=') {
                        frame.pos++;
                        token.type = TOKEN_PIPE_EQUAL; // Assignment by bitwise OR
                    } else if (*frame.pos == '|') {
                        frame.pos++;
                        token.type = TOKEN_PIPE_PIPE; // Logical OR
                    } else {
                        token.type = TOKEN_PIPE; // Bitwise OR
                    }

                    break;
                }

                case '"': {
                    const char *line_end = frame.line_start;
					while (*line_end != '\n' && *line_end != '\0') {
						line_end++;
					}
                    frame.pos++; 

                    const char *start __attribute__((unused)) = frame.pos;

                    while (*frame.pos != '"' && *frame.pos != '\0') {
                        if (*frame.pos == '\\' && *(frame.pos + 1) != '\0') {
                            frame.pos++;
                        }
                        frame.pos++;
                    }

                    if (*frame.pos == '"') {
                        token.type = TOKEN_STRING_LITERAL;
                        frame.pos++;
                    } else {
                        handler.verr(
                            &frame,
                            column,
                            1,
                            "string literal not properly terminated"
                        );
                    }

                    break;
                }

				default: {
					const char *line_end = frame.line_start;
					while (*line_end != '\n' && *line_end != '\0') {
						line_end++;
					}

                    handler.verr(
						&frame,
						column,
						1,
                        "Unexpected character: '%c'", c
                    );
                    fatalErr = true;
                    break;
				}

			}
		}

        token.length = (int)(frame.pos - token.value);

        #ifdef DEBUG
        printf("Token %d (Line %d, Col %d):\t%.*s\n", 
               counter, frame.line, column, (int)token.length, token.value
		);
        counter++;
        #endif

        ts_push(fileStruct->t_stream, (Token){token.value, token.length, token.type}, handler.ferr);
    }

    ts_push(fileStruct->t_stream, (Token){frame.pos, 0, TOKEN_EOF}, handler.ferr);

    if (fatalErr) {
        handler.fatal(EXIT_FAILURE);
    }
}