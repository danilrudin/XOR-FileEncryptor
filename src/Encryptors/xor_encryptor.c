#include "xor_encryptor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int is_char(char ch);

void generate_key(char *buffer, size_t size)
{
    srand((unsigned int) time(NULL));
    
    size_t i = 0;
    while (i < size - 1)
    {
        char candidate = (char)((rand() % (126 - 33 + 1)) + 33);
        if (is_char(candidate))
        {
            buffer[i++] = candidate;
        }
    }

    buffer[size - 1] = '\0';
}

int encrypt_file(const char *src_path, const char *dest_path, const char *key)
{
    FILE *fs = fopen(src_path, "rb");
    if (!fs)
    {
        return EXIT_FAILURE;
    }

    FILE *ft = fopen(dest_path, "wb");
    if (!ft)
    {
        fclose(fs);
        return EXIT_FAILURE;
    }
    
    size_t key_index = 0, key_length = strlen(key);

    int ch;
    while ((ch = fgetc(fs)) != EOF)
    {
        unsigned char encrypted = (unsigned char)ch ^ key[key_index];
        if (fputc(encrypted, ft) == EOF)
        {
            break;
        }
        key_index = (key_index + 1) % key_length;
    }

    int error = ferror(fs) || ferror(ft);
    fclose(fs);
    fclose(ft);
    
    return error ? EXIT_FAILURE : EXIT_SUCCESS;
}

int decrypt_file(const char *src_path, const char *dest_path, const char *key)
{
    return encrypt_file(src_path, dest_path, key);
}

static int is_char(char ch)
{
    return (ch >= 33 && ch <= 126) && ch != '\\' && ch != '"' && ch != '\'';
}