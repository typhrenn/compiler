#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    TOKEN_TYPE1,
    TOKEN_TYPE2,
    TOKEN_TYPE3,
    UNINDENTIFIED
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

#endif
