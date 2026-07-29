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

void check_config(void)
{
}

void check_buf(int return_value, int64_t size_of_buffer, void *buf_to_free[])
{
	/* check if the string was truncated after the use of snprintf */
	if (return_value < 0 || return_value >= size_of_buffer)
	{
		err_buffer_size = size_of_buffer;
		err_buffer_write = return_value;

		if (buf_to_free != NULL)
		{
			for (uint8_t i = 0; buf_to_free[i] != NULL; i++)
			{
				free(buf_to_free[i]);
			}
		}

		if (return_value == 0)
		{
			err(ZERO_SIZED_BUF);
		}

		err(FORMATTING_ERROR);
		exit(1);
	}
}

