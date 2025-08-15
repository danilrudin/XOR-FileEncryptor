#include "arg_flags.h"
#include "arg_handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int handle_flag(int argc, char *argv[], int *i, int *target, int expected_value, int disallowed_value);
static int handle_string(int argc, char *argv[], int *i, char *target, size_t max_length);
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

static int handle_flag(int argc, char *argv[], int *i, int *target, int expected_value, int disallowed_value)
{
    (void)argc;
    
    const char *flag_name = argv[*i];

    if (*target != disallowed_value)
    {
        fprintf(stderr, "Error: duplicate or conflicting %s flag.\n", flag_name);
        return -1;
    }

    *target = expected_value;
    return 0;
}

static int handle_string(int argc, char *argv[], int *i, char *target, size_t max_length)
{
    const char *flag_name = argv[*i];

    if (target[0])
    {
        fprintf(stderr, "Error: duplicate %s flag.\n", flag_name);
        return -1;
    }

    const char *arg;
    if (parse_string(argc, argv, i, &arg) != 0 || is_known_flag(arg))
    {
        fprintf(stderr, "Error: %s requires a value.\n", flag_name);
        return -1;
    }

    if (strlen(arg) >= max_length)
    {
        fprintf(stderr, "Error: value for %s is too long (max %zu characters).\n", flag_name, max_length - 1);
        return -1;
    }

    strncpy(target, arg, max_length);
    target[max_length - 1] = '\0';

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

static const char *known_flags[] = {
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
    for (int i = 0; known_flags[i] != NULL; ++i)
    {
        if (strcmp(arg, known_flags[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}