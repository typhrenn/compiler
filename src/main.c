#include <stdio.h>
#include <token.h>
#include <lexer.h>

int main()
{
    const char *file = "testfile";
    char *text = charstream(file);

    char **lex = lexstream(text);

    return 0;
}
