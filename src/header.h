#define HEADER_DOT_H
#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_WORDS 2327
#define FILTER_ARG_EXPECTED 3
#define ARGS_BEFORE_FLAG 1

extern char words[NUM_WORDS][6];

void test(int num_arg);
void parse_command(int num_arg, char *argument[]);
void debug(int num_arg, char *argument[]);
void err(int error_code);
