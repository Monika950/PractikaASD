#include <stdio.h>
#include "encrypting_questions.h"

void encrypt(char *input, char *output)
{
    FILE *in = fopen(input, "r");
    FILE *out = fopen(output, "w");
    FILE *key_file = fopen("key.txt", "r");

    if (in == NULL || out == NULL)
    {
        printf("Error opening files\n");
        return;
    }
    char key_char;
    int key;
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        key_char = fgetc(key_file);
        if (key_char == '\0')
        {
            fseek(key_file, 0, SEEK_SET);
            continue;
        }
        key = key_char - '0';
        c = c + key;
        fputc(c, out);
    }

    fclose(in);
    fclose(out);
}

void decrypt(char *input, char *output)
{
    FILE *in = fopen(input, "rb");
    FILE *out = fopen(output, "w");
    FILE *key_file = fopen("key.txt", "r");

    if (in == NULL || out == NULL)
    {
        printf("Error opening files\n");
        return;
    }
    char key_char;
    int key;
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        key_char = fgetc(key_file);
        if (key_char == '\0')
        {
            fseek(key_file, 0, SEEK_SET);
            continue;
        }
        key = key_char - '0';
        c = c - key;
        fputc(c, out);
    }

    fclose(in);
    fclose(out);
}
