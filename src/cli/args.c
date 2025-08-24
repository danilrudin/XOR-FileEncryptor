#include "args.h"
#include "arg_flags.h"
#include "arg_handlers.h"
#include "../constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int validate_args(const cli_args_t *opts);
static void print_usage(const char *program_name);

// Table-driven mapping of CLI flags to their handler functions.
// This allows parsing logic to remain generic and extensible.
typedef struct
{
    const char *flag;
    arg_handler_t handler;
} arg_option_t;

static const arg_option_t arg_option_ts[] = {
    {FLAG_ENCRYPT, handle_encrypt},
    {FLAG_DECRYPT, handle_decrypt},
    {FLAG_GENERATE_KEY, handle_generate_key},
    {FLAG_KEY, handle_key},
    {FLAG_INPUT, handle_input},
    {FLAG_OUTPUT, handle_output},
    {NULL, NULL}
};

int parse_args(int argc, char *argv[], cli_args_t *opts)
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    memset(opts, 0, sizeof(cli_args_t));
    opts->encrypt_mode = -1;


    // Iterate over argv, attempting to match each argument to a known flag.
    // If a flag matches, its handler is invoked, which may consume additional arguments.
    // Unknown flags result in an error and early exit.
    for (int i = 1; i < argc; ++i)
    {
        int matched = 0;
        for (const arg_option_t *opt = arg_option_ts; opt->flag; ++opt)
        {
            if (strcmp(argv[i], opt->flag))
            {
                continue;
            }

            // Argument index 'i' is passed by pointer so the handler can
            // consume additional arguments (e.g., -k <key>) and advance 'i'.
            if (opt->handler(argc, argv, &i, opts))
            {
                return EXIT_FAILURE;
            }

            matched = 1;
        }

        if (!matched)
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            
            return EXIT_FAILURE;
        }
    }

    return validate_args(opts);
}

static int validate_args(const cli_args_t *opts)
{
    if (opts->encrypt_mode == -1 || !opts->input_path[0] || !opts->output_path[0])
    {
        fprintf(stderr, "Error: missing required arguments (-e/-d, -i, -o).\n");
        return EXIT_FAILURE;
    }

    if (strcmp(opts->input_path, opts->output_path) == 0)
    {
        fprintf(stderr, "Error: source path cannot be the same as destination path.\n");
        return EXIT_FAILURE;
    }

    if (opts->encrypt_mode)
    {
        if (opts->generate_key && opts->key[0])
        {
            fprintf(stderr, "Error: use either -k or -g, not both.\n");
            return EXIT_FAILURE;
        }
        else if (!opts->generate_key && !opts->key[0])
        {
            fprintf(stderr, "Error: encryption requires a key (-k) or key generation (-g).\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        if (opts->generate_key)
        {
            fprintf(stderr, "Error: -g cannot be used in decryption mode.\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static void print_usage(const char *program_name)
{
    fprintf(stderr, "Usage: %s [-e | -d] [-k <key> | -g] -i <input_file> -o <output_file>\n", program_name);
}