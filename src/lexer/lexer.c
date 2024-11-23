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
char **lexstream(char *charstream)
{
    int word_count = 0;
    int in_word = 0;

    for (int i = 0; charstream[i] != '\0'; i++)
    {
        if (charstream[i] == ' ' || charstream[i] == '\t'|| charstream[i] == '\n')
        {
            if (in_word)
            {
                in_word = 0;
            }
        }

        else
        {
            if (!in_word)
            {
                word_count++;
                in_word = 1;
            }
        }
    }

    char **lexstream = malloc((word_count + 1) * sizeof(char *));

    int word_index = 0;
    int start = -1;

    for (int i = 0; ; i++)
    {
        if (charstream[i] == ' ' || charstream[i] == '\t'|| charstream[i] == '\n')
        {
            if (start != -1)
            {
                int word_len = i - start;

                lexstream[word_index] = malloc((word_len + 1) * sizeof(char));

                for (int j = 0; j < word_len; j++)
                {
                    lexstream[word_index][j] = charstream[start + j];
                }

                lexstream[word_index][word_len] = '\0';

                word_index++;
                start = -1;
            }

            if (charstream[i] == '\0')
            {
                break;
            }
        }

        else
        {
            if (start == 1)
            {
                start = i;
            }
        }
    }

    lexstream[word_count] = NULL;

    return lexstream;
}
