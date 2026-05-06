#include "header.h"

/* display options */

bool awsum_table_mode = false; /* false by default */
/* if true, print items in columns and then go to the next column
 * if false, print items from left to right and then go to next row(down) */

int table_width = 6; /* 6 by default
						this is the width of the table (the number of words displayed on the x axis */


bool verbose = false; /* false by default
						 shows more logs and information about the program */


bool ignore_warn = false; /* false by default
							 ignores some warnings */


/* Parsing & command options */

enum ALL_WORD_LISTS default_word_list = nyt; /* nyt by default (nyt = New York Times word list)
 * this sets the default word list
 * it is used when no word list is specified in the command */

int command_arguments_context = 4; /* 4 by default */
/* this is the amount of arguments displayed around the error when a user types an invalid argument
 * the value corresponds to the number of arguments displayed before the error and after the error
 * it helps to provide context to the user whenever they make a mistake */
