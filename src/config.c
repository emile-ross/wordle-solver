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
