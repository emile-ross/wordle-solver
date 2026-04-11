#define HEADER_DOT_H
#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_WORDS 2331
#define NUM_LETTERS_WORD 5

#define ARGS_BEFORE_FLAG_BASE 1
#define P_FILTERS_ARG_EXP 3
#define G_FILTERS_ARG_EXP 2

extern char words[NUM_WORDS][6];
extern char filtered_arr[NUM_WORDS][6];

void test(int num_arg);
void parse_command(int num_arg, char *argument[]);
void err(int error_code);

void print_as_table(int width, int total_elements, bool awsum_mode);

// Global variables
extern int ARGS_BEFORE_CUR_FLAG;
extern int flag_r;


// General simple functions
void user_index_validation(int index);


// config file
extern bool awsum_table_mode;
extern int table_width;

