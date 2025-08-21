#ifndef ARGHANDLERS_H
#define ARGHANDLERS_H

#include "args.h"

typedef int (*arg_handler_t)(int argc, char *argv[], int *i, cli_args_t *opts);

int handle_encrypt(int argc, char *argv[], int *i, cli_args_t *opts);
int handle_decrypt(int argc, char *argv[], int *i, cli_args_t *opts);
int handle_generate_key(int argc, char *argv[], int *i, cli_args_t *opts);
int handle_key(int argc, char *argv[], int *i, cli_args_t *opts);
int handle_input(int argc, char *argv[], int *i, cli_args_t *opts);
int handle_output(int argc, char *argv[], int *i, cli_args_t *opts);

#endif // ARGHANDLERS_H