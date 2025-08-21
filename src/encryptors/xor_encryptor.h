#ifndef XOR_ENCRYPTOR_H
#define XOR_ENCRYPTOR_H

#include <stddef.h>

void generate_key(char *buffer, size_t size);

int encrypt_file(const char *src_file_path, const char *dest_file_path, const char *key);
int decrypt_file(const char *src_file_path, const char *dest_file_path, const char *key);

#endif // XOR_ENCRYPTOR_H