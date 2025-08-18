#ifndef ARGS_H
#define ARGS_H

#include "../constants.h"

typedef struct
{
    int encryptMode;
    int generateKey;
    char key[KEY_LENGTH];
    char inputPath[PATH_MAX];
    char outputPath[PATH_MAX];
} CliArgs;

int parseArgs(int argc, char *argv[], CliArgs *outOptions);

#endif // ARGS_H