#include "header.h"

const char *word_list_flag = "-w";
const char *word_list_long_flag = "--word-list";

char *word_list_text[NUM_WORD_LISTS] =
{
	"all french words",
	"all words",
	"common words",
	"New-York-Times words",
	"all latin words",
	"common latin words",
};

uint8_t valid_user_index(long index)
{
	/* return a valid uint8_t variable */
	if (index > NUM_LETTERS_WORD || index > 65535 )
	{
		/* display error message for invalid value (invalid index into the word) */
	    	err(CMD_INDEX_BOUNDS);
	}
	else if (index < 0)
	{
		err(NEGATIVE_INDEX);
	}
	return (uint8_t)index;
}

/* BTW: functions related to buffers were moved to src/buffers.c */
