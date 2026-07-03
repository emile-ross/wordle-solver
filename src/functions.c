#include "header.h"

const char *word_list_flag = "-w";
const char *word_list_long_flag = "--word-list";

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

char *word_list_name(ALL_WORD_LISTS word_list_type)
{
	switch (word_list_type)
	{
	case en_nyt:
		return "New-York-Times words";
	case en_all:
		return "all words";
	case en_common:
		return "common words";
	case fr_all:
		return "all french words";
	case la_all:
		return "all latin words";
	case la_common:
		return "common latin words";
	case custom:
		return "custom word list";
	default:
		err(UNKNOWN_WORD_LIST);
		return NULL;
	}
}
