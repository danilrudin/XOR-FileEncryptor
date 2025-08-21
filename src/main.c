#include "encryptors/xor_encryptor.h"
#include "cli/args.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    cli_args_t opts;
    if (parse_args(argc, argv, &opts))
    {
        return EXIT_FAILURE;
    }

    if (opts.encrypt_mode == 1)
    {
        if (opts.generate_key)
        {
            generate_key(opts.key, KEY_LENGTH);
        }

        printf("Encrypting file...\n");
        if (encrypt_file(opts.input_path, opts.output_path, opts.key) == EXIT_SUCCESS)
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
        if (decrypt_file(opts.input_path, opts.output_path, opts.key) == EXIT_SUCCESS)
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
