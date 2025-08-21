#include "arg_flags.h"
#include "arg_handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int handle_flag(int argc, char *argv[], int *i, int *target, int expectedValue, int disallowedValue);
static int handle_string(int argc, char *argv[], int *i, char *target, size_t maxLength);
static int parse_string(int argc, char *argv[], int *i, const char **target);
static int is_known_flag(const char *arg);


int handle_encrypt(int argc, char *argv[], int *i, cli_args_t *opts)
{
    return handle_flag(argc, argv, i, &opts->encrypt_mode, 1, -1);
}

int handle_decrypt(int argc, char *argv[], int *i, cli_args_t *opts)
{
    return handle_flag(argc, argv, i, &opts->encrypt_mode, 0, -1);
}

int handle_generate_key(int argc, char *argv[], int *i, cli_args_t *opts)
{
    return handle_flag(argc, argv, i, &opts->generate_key, 1, 0);
}

int handle_key(int argc, char *argv[], int *i, cli_args_t *opts)
{
    return handle_string(argc, argv, i, opts->key, KEY_LENGTH);
}

int handle_input(int argc, char *argv[], int *i, cli_args_t *opts)
{
    return handle_string(argc, argv, i, opts->input_path, PATH_LENGTH);
}

int handle_output(int argc, char *argv[], int *i, cli_args_t *opts)
{
    return handle_string(argc, argv, i, opts->output_path, PATH_LENGTH);
}

static int handle_flag(int argc, char *argv[], int *i, int *target, int expectedValue, int disallowedValue)
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

static int handle_string(int argc, char *argv[], int *i, char *target, size_t maxLength)
{
    const char *flagName = argv[*i];

    if (target[0])
    {
        fprintf(stderr, "Error: duplicate %s flag.\n", flagName);
        return -1;
    }

    const char *arg;
    if (parse_string(argc, argv, i, &arg) != 0 || is_known_flag(arg))
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

static int parse_string(int argc, char *argv[], int *i, const char **arg)
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

static int is_known_flag(const char *arg)
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