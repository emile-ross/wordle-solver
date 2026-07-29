#include "include/header.h"

uint8_t valid_user_index(long index, void *ptr_to_free)
{
	/* return a valid uint8_t variable */
	if (index > NUM_LETTERS_WORD || index > 65535 )
	{
		/* display error message for invalid value (invalid index into the word) */
		free(ptr_to_free);
	    	err(CMD_INDEX_BOUNDS);
		exit(1);
	}
	else if (index <= 0)
	{
		free(ptr_to_free);
		err(INVALID_INDEX);
		exit(1);
	}
	else
	{
		return (uint8_t)index;
	}
}

