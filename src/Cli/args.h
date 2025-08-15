#ifndef ARGS_H
#define ARGS_H

#include "../constants.h"

typedef struct
{
    int encrypt_mode;
    int generate_key;
    char key[KEY_LENGTH];
    char input_path[PATH_LENGTH];
    char output_path[PATH_LENGTH];
} cli_args_t;

int parse_args(int argc, char *argv[], cli_args_t *out_options);

#endif // ARGS_H