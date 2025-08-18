#include "encryptors/xorencryptor.h"
#include "cli/args.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    CliArgs opts;
    if (parseArgs(argc, argv, &opts))
    {
        return EXIT_FAILURE;
    }

    if (opts.encryptMode == 1)
    {
        if (opts.generateKey)
        {
            generateKey(opts.key, KEY_LENGTH);
        }

        printf("Encrypting file...\n");
        if (encryptFile(opts.inputPath, opts.outputPath, opts.key) == EXIT_SUCCESS)
        {
            printf("The file was successfully encrypted. Your key:\n%s\n", opts.key);
        }
        else
        {
            perror("Encryption failed");
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("Decrypting file...\n");
        if (decryptFile(opts.inputPath, opts.outputPath, opts.key) == EXIT_SUCCESS)
        {
            printf("The file was successfully decrypted.\n");
        }
        else
        {
            perror("Decryption failed");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
