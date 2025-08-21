#ifndef XORENCRYPTOR_H
#define XORENCRYPTOR_H

#include <stddef.h>

void generate_key(char *buffer, size_t size);

int encrypt_file(const char *src_file_path, const char *dest_file_path, const char *key);
int decrypt_file(const char *src_file_path, const char *dest_file_path, const char *key);

#endif // XORENCRYPTOR_H