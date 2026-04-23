#define HEADER_DOT_H
#define _POSIX_C_SOURCE 200809L

#include "enums.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// number of words for each array
#define NUM_WORDS 2331
#define NUM_COMMON_WORDS 5700
#define NUM_ALL_WORDS 12923

#define NUM_LETTERS_WORD 5
// INDEX_LETTERS_WORD is NUM_LETTERS + 1
#define INDEX_LETTERS_WORD 6

#define ARGS_BEFORE_FLAG_BASE 1
#define P_FILTERS_ARG_EXP 3
#define G_FILTERS_ARG_EXP 2
#define WORD_LIST_ARG_EXP 2

// Define colours
#define ANSI_RED 	"\x1b[31m"
#define ANSI_GREEN 	"\x1b[32m" 
#define ANSI_CYAN    	"\x1b[36m"
#define ANSI_LCYAN    	"\x1b[96m"
#define ANSI_YELLOW 	"\x1b[33m"
#define ANSI_LYELLOW 	"\x1b[93m"
#define ANSI_BLUE    	"\x1b[34m"
#define ANSI_WHITE    	"\x1b[97m"

#define BOLD_S  	"\x1B[1m" 

// reset styling
#define STYLE_END	"\x1B[0m" 


#define n_num_list (3)
extern char nyt_words[NUM_WORDS][INDEX_LETTERS_WORD];
extern char common_words[NUM_COMMON_WORDS][INDEX_LETTERS_WORD];
extern char all_words[NUM_ALL_WORDS][INDEX_LETTERS_WORD];

// filtered array used to store filtered words and it is also used for printing results
extern char filtered_arr[NUM_ALL_WORDS][INDEX_LETTERS_WORD];


extern char *word_list_text[n_num_list];

void err(int error_code);

void print_as_table(int width, int total_elements, bool awsum_mode);

int parsing(int *flag_r, enum ALL_WORD_LISTS w_list, bool *f_exec, bool filter_include_bl, bool letter_indexed_bl, char *arguments[]);
void command_parsing(int argc, int flag_reading_index, char *arguments[]);

// Global variables
extern int ARGS_BEFORE_CUR_FLAG;
extern enum ALL_WORD_LISTS word_list;
extern int n_possible_answers;


// General simple functions
void user_index_validation(int index);


// config file
extern bool awsum_table_mode;
extern int table_width;
extern bool verbose;
extern bool ignore_warn;

void verbose_printing(char *flag, char letter, int indexed_letter_value, int affected_words, bool letter_is_present);

