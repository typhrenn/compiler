#include <stdio.h>
#include <stdlib.h>
#include <token.h>
#include <string.h>

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
    printf("Debugging output(file size): %ld bytes\n", size);

    char *charstream = malloc((size + 1) * sizeof(char));
    if (!charstream)
    {
        perror("Failed to allocate memory for charstream\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    printf("Debugging output(file name): %s\n", filename);

    unsigned char buffer[1];
    int currentByte = 0;

    while (fread(buffer, 1, 1, file) == 1)
    {
        if (currentByte >= size)
        {
            break;
        }
        charstream[currentByte] = buffer[0];

        ++currentByte;
    }

    charstream[currentByte] = '\0';

    fclose(file);
    printf("Debugging output(file content as charstream): %s\n", charstream);
    return charstream;
}

// Return tokens from char pointer
char **lexstream(char *charstream)
{
    printf("Debugging output(charstream parameter): %s\n", charstream);
    
    int word_count = 0;
    int in_word = 0;

    // Count words
    for (int i = 0; charstream[i] != '\0'; i++)
    {
        if (charstream[i] == ' ' || charstream[i] == '\t' || charstream[i] == '\n')
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

    printf("Debugging output(word count): %d\n", word_count);

    char **lexstream = malloc((word_count + 1) * sizeof(char *));
    if (!lexstream)
    {
        perror("Failed to allocate memory for lexstream\n");
        exit(EXIT_FAILURE);
    }

    printf("Debugging output(memory allocation - words): %d\n", word_count);

    int word_index = 0;
    int start = -1;

    // Extract words
    for (int i = 0; ; i++)
    {
        if (charstream[i] == ' ' || charstream[i] == '\t' || charstream[i] == '\n' || charstream[i] == '\0')
        {
            if (start != -1)
            {
                int word_len = i - start;

                lexstream[word_index] = malloc((word_len + 1) * sizeof(char));
                if (!lexstream[word_index])
                {
                    perror("Failed to allocate memory for word\n");
                    exit(EXIT_FAILURE);
                }

                for (int j = 0; j < word_len; j++)
                {
                    lexstream[word_index][j] = charstream[start + j];
                }

                lexstream[word_index][word_len] = '\0';

                printf("Debugging output(current word %d): %s\n", word_index, lexstream[word_index]);

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
            if (start == -1)
            {
                start = i;
            }
        }
    }

    lexstream[word_count] = NULL;  // Null-terminate the array
    printf("Debugging output(outputed words): \n");
    for (int i = 0; lexstream[i] != NULL; i++)
    {
        printf("Debugging output(lexstream[%d]): %s\n", i, lexstream[i]);
    }

    return lexstream;
}

