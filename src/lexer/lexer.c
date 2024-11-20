#include <stdio.h>
#include <stdlib.h>
#include <token.h>

// Get file size
long filesize(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size;
}

// Get char pointer out of file
char *charstream(const char *filename)
{
    long size = filesize(filename);
    char *charstream = malloc(size * sizeof(char));

    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_SET);

    unsigned char buffer[1];
    int currentByte = 0;

    while (fread(buffer, 1, 1, file) == 1)
    {
        ++currentByte;

        if (currentByte > size)
        {
            break;
        }
        charstream[currentByte] = buffer[1];
    }

    fclose(file);
    return charstream;
}

// Return tokens from char pointer
Token tokenstream(char *charstream)
{

}
