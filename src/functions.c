#include "header.h"

const char *word_list_flag = "-w";
const char *word_list_long_flag = "--word-list";

char *word_list_text[NUM_WORD_LISTS] =
{
	"all french words",
	"all words",
	"common words",
	"New-York-Times words",
};

void user_index_validation(int index)
{
	if (index < 0 || index > NUM_LETTERS_WORD )
	{
	    	/* display error message for invalid value (invalid index into the word) */
	    	err(CMD_INDEX_BOUNDS);
	}
}

