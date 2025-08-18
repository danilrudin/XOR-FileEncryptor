#include "argFlags.h"
#include "argHandlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int handleFlag(int argc, char *argv[], int *i, int *target, int expectedValue, int disallowedValue);
static int handleString(int argc, char *argv[], int *i, char *target, size_t maxLength);
static int parseString(int argc, char *argv[], int *i, const char **target);
static int isKnownFlag(const char *arg);


int handleEncrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    return handleFlag(argc, argv, i, &opts->encryptMode, 1, -1);
}

int handleDecrypt(int argc, char *argv[], int *i, CliArgs *opts)
{
    return handleFlag(argc, argv, i, &opts->encryptMode, 0, -1);
}

int handleGenerateKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    return handleFlag(argc, argv, i, &opts->generateKey, 1, 0);
}

int handleKey(int argc, char *argv[], int *i, CliArgs *opts)
{
    return handleString(argc, argv, i, opts->key, KEY_LENGTH);
}

int handleInput(int argc, char *argv[], int *i, CliArgs *opts)
{
    return handleString(argc, argv, i, opts->inputPath, PATH_LENGTH);
}

int handleOutput(int argc, char *argv[], int *i, CliArgs *opts)
{
    return handleString(argc, argv, i, opts->outputPath, PATH_LENGTH);
}

static int handleFlag(int argc, char *argv[], int *i, int *target, int expectedValue, int disallowedValue)
{
    (void)argc;
    
    const char *flagName = argv[*i];

    if (*target != disallowedValue)
    {
        fprintf(stderr, "Error: duplicate or conflicting %s flag.\n", flagName);
        return -1;
    }

    *target = expectedValue;
    return 0;
}

static int handleString(int argc, char *argv[], int *i, char *target, size_t maxLength)
{
    const char *flagName = argv[*i];

    if (target[0])
    {
        fprintf(stderr, "Error: duplicate %s flag.\n", flagName);
        return -1;
    }

    const char *arg;
    if (parseString(argc, argv, i, &arg) != 0 || isKnownFlag(arg))
    {
        fprintf(stderr, "Error: %s requires a value.\n", flagName);
        return -1;
    }

    if (strlen(arg) >= maxLength)
    {
        fprintf(stderr, "Error: value for %s is too long (max %zu characters).\n", flagName, maxLength - 1);
        return -1;
    }

    strncpy(target, arg, maxLength);
    target[maxLength - 1] = '\0';

    return 0;
}

static int parseString(int argc, char *argv[], int *i, const char **arg)
{
    if (++(*i) >= argc || argv[*i][0] == '\0')
    {
        return -1;
    }

    *arg = argv[*i];
    return 0;
}

static const char *knownFlags[] = {
    FLAG_ENCRYPT,
    FLAG_DECRYPT,
    FLAG_GENERATE_KEY,
    FLAG_KEY,
    FLAG_INPUT,
    FLAG_OUTPUT,
    NULL
};

static int isKnownFlag(const char *arg)
{
    for (int i = 0; knownFlags[i] != NULL; ++i)
    {
        if (strcmp(arg, knownFlags[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}