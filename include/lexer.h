#ifndef LEXER_H
#define LEXER_H

#include "file.h"

typedef char* Token;

void tokenize(Token *tokens, struct FileData *fileStruct);

#endif