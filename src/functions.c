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

uint8_t valid_user_index(long index)
{
	if (index > 65535 || index < 0 || index > NUM_LETTERS_WORD)
	{
		/* display error message for invalid value (invalid index into the word) */
	    	err(CMD_INDEX_BOUNDS);
	}
	return (uint8_t)index;
}

void check_buf(int return_value, int size_of_buffer)
{
	/* check if the string was truncated after the use of snprintf */
	if (return_value < 0 || return_value >= size_of_buffer)
	{
		err(FORMATTING_ERROR);
		exit(1);
	}
}

void buffer_write(char *string, size_t size_of_string, const char *restrict format, ...)
{
	size_t return_value = (size_t)snprintf(string, size_of_string, format);
	check_buf((int)return_value, (int)size_of_string);

	/* check if the string was truncated after the use of snprintf */
	if (return_value >= size_of_string)
	{
		err(BUFFER_WRITE_FAIL);
	}
}
