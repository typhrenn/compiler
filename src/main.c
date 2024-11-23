#include <stdio.h>
#include <token.h>
#include <lexer.h>

int main()
{
    const char *file = "testfile";
    char *text = charstream(file);

    char **lex = lexstream(text);
    Token *tokens = tokenize(lex);
    for (int i = 0; tokens[i].value != NULL; i++)
    {
        printf("Value: %s\n", tokens[i].value);
        printf("Type: %d\n", tokens[i].type);
    }

    return 0;
}
