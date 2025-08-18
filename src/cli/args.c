#include "args.h"
#include "argFlags.h"
#include "argHandlers.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int validateArgs(const CliArgs *opts);
static void printUsage(const char *programName);

typedef struct
{
    const char *flag;
    ArgHandler handler;
} ArgOption;

static const ArgOption argOptions[] = {
    {FLAG_ENCRYPT, handleEncrypt},
    {FLAG_DECRYPT, handleDecrypt},
    {FLAG_GENERATE_KEY, handleGenerateKey},
    {FLAG_KEY, handleKey},
    {FLAG_INPUT, handleInput},
    {FLAG_OUTPUT, handleOutput},
    {NULL, NULL}
};

int parseArgs(int argc, char *argv[], CliArgs *opts)
{
    if (argc < 2)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    memset(opts, 0, sizeof(CliArgs));
    opts->encryptMode = -1;

    for (int i = 1; i < argc; ++i)
    {
        int matched = 0;
        for (const ArgOption *opt = argOptions; opt->flag; ++opt)
        {
            if (strcmp(argv[i], opt->flag))
            {
                continue;
            }

            if (opt->handler(argc, argv, &i, opts))
            {
                return EXIT_FAILURE;
            }

            matched = 1;
        }

        if (!matched)
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            printUsage(argv[0]);
            
            return EXIT_FAILURE;
        }
    }

    return validateArgs(opts);
}

static int validateArgs(const CliArgs *opts)
{
    if (opts->encryptMode == -1 || !opts->inputPath[0] || !opts->outputPath[0])
    {
        fprintf(stderr, "Error: missing required arguments (-e/-d, -i, -o).\n");
        return EXIT_FAILURE;
    }

    if (strcmp(opts->inputPath, opts->outputPath) == 0)
    {
        fprintf(stderr, "Error: source path cannot be the same as destination path.\n");
        return EXIT_FAILURE;
    }

    if (opts->encryptMode)
    {
        if (opts->generateKey && opts->key[0])
        {
            fprintf(stderr, "Error: use either -k or -g, not both.\n");
            return EXIT_FAILURE;
        }
        else if (!opts->generateKey && !opts->key[0])
        {
            fprintf(stderr, "Error: encryption requires a key (-k) or key generation (-g).\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (opts->generateKey)
        {
            fprintf(stderr, "Error: -g cannot be used in decryption mode.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static void printUsage(const char *programName)
{
    fprintf(stderr, "Usage: %s [-e | -d] [-k <key> | -g] -i <input_file> -o <output_file>\n", programName);
}