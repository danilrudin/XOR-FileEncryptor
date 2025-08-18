#include "xorencryptor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int isSafeChar(char ch);

void generateKey(char *buffer, size_t size)
{
    srand((unsigned int) time(NULL));
    
    size_t i = 0;
    while (i < size - 1)
    {
        char candidate = (char)((rand() % (126 - 33 + 1)) + 33);
        if (isSafeChar(candidate))
        {
            buffer[i++] = candidate;
        }
    }

    buffer[size - 1] = '\0';
}

int encryptFile(const char *srcFilePath, const char *destFilePath, const char *key)
{
    FILE *fs = fopen(srcFilePath, "rb");
    if (!fs)
    {
        return EXIT_FAILURE;
    }

    FILE *ft = fopen(destFilePath, "wb");
    if (!ft)
    {
        fclose(fs);
        return EXIT_FAILURE;
    }
    
    size_t keyIndex = 0, keyLength = strlen(key);

    int ch;
    while ((ch = fgetc(fs)) != EOF)
    {
        unsigned char encrypted = (unsigned char)ch ^ key[keyIndex];
        if (fputc(encrypted, ft) == EOF)
        {
            break;
        }
        keyIndex = (keyIndex + 1) % keyLength;
    }

    int error = ferror(fs) || ferror(ft);
    fclose(fs);
    fclose(ft);
    
    return error ? EXIT_FAILURE : EXIT_SUCCESS;
}

int decryptFile(const char *srcFilePath, const char *destFilePath, const char *key)
{
    return encryptFile(srcFilePath, destFilePath, key);
}

static int isSafeChar(char ch)
{
    return (ch >= 33 && ch <= 126) && ch != '\\' && ch != '"' && ch != '\'';
}