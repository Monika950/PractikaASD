#include <stdio.h>

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
        // if (c >= 'a' && c <= 'z')
        // {
        //     c = c + key;
        //     if (c > 'z')
        //     {
        //         c = c - 'z' + 'a' - key;
        //     }
        //     if (c < 'a')
        //     {
        //         c = c + ('z' - 'a' + 1);
        //     }
        //     fputc(c, out);
        // }
        // else if (c >= 'A' && c <= 'Z')
        // {
        //     c = c + key;
        //     if (c > 'Z')
        //     {
        //         c = c - 'Z' + 'A' - key;
        //     }
        //     fputc(c, out);
        // }
        // else
        // {
        //     fputc(c, out);
        // }
    }

    fclose(in);
    fclose(out);
}

void decrypt(char *input, char *output)
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
        c = c - key;
        fputc(c, out);
        // if (c >= 'a' && c <= 'z')
        // {
        //     c = c - key;
        //     if (c < 'a')
        //     {
        //         c = c + 'z' - 'a' + key;
        //     }
        //     if (c > 'z')
        //     {
        //         c = c - ('z' - 'a' + 1);
        //     }
        //     fputc(c, out);
        // }
        // else if (c >= 'A' && c <= 'Z')
        // {
        //     c = c - key;
        //     if (c < 'A')
        //     {
        //         c = c + 'Z' - 'A' + key;
        //     }
        //     fputc(c, out);
        // }
        // else
        // {
        //     fputc(c, out);
        // }
    }

    fclose(in);
    fclose(out);
}

// int main()
// {
//     encrypt("to_encrypt.txt", "encrypted.txt");
//     decrypt("encrypted.txt", "decrypted.txt");
//     return 0;
// }