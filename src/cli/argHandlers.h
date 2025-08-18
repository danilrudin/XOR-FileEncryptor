#ifndef ARGHANDLERS_H
#define ARGHANDLERS_H

#include "args.h"

typedef int (*ArgHandler)(int argc, char *argv[], int *i, CliArgs *opts);

int handleEncrypt(int argc, char *argv[], int *i, CliArgs *opts);
int handleDecrypt(int argc, char *argv[], int *i, CliArgs *opts);
int handleGenerateKey(int argc, char *argv[], int *i, CliArgs *opts);
int handleKey(int argc, char *argv[], int *i, CliArgs *opts);
int handleInput(int argc, char *argv[], int *i, CliArgs *opts);
int handleOutput(int argc, char *argv[], int *i, CliArgs *opts);

#endif // ARGHANDLERS_H