#ifndef LEXER_H
#define LEXER_H

long filesize(const char *filename);
char *charstream(const char *filename);
char **lexstream(char *charstream);
Token *tokenize(char **charstream);

#endif
