#ifndef XORENCRYPTOR_H
#define XORENCRYPTOR_H

#include <stddef.h>

void generateKey(char *buffer, size_t size);

int encryptFile(const char *srcFilePath, const char *destFilePath, const char *key);
int decryptFile(const char *srcFilePath, const char *destFilePath, const char *key);

#endif // XORENCRYPTOR_H