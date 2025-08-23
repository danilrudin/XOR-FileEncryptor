#include "xor_encryptor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_key(char *buffer, size_t size)
{
	static const char allowed_chars[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"!@#$%^&*()-_=+[]{};:,.<>/?|`~";

	const size_t allowed_count = sizeof(allowed_chars) - 1;

	srand((unsigned int) time(NULL));

	for (size_t i = 0; i < size - 1; ++i)
	{
		int index = rand() % allowed_count;
		buffer[i] = allowed_chars[index];
	}

	buffer[size - 1] = '\0';
}

int encrypt_file(const char *src_file_path, const char *dest_file_path, const char *key)
{
    FILE *fs = fopen(src_file_path, "rb");
    if (!fs)
    {
        return EXIT_FAILURE;
    }

    FILE *ft = fopen(dest_file_path, "wb");
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

int decrypt_file(const char *src_file_path, const char *dest_file_path, const char *key)
{
    return encrypt_file(src_file_path, dest_file_path, key);
}