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
	int return_value = snprintf(string, size_of_string, format);
	check_buf(return_value, (int)size_of_string);

	/* check if the string was truncated after the use of snprintf */
	if ((size_t)return_value >= size_of_string)
	{
		err(BUFFER_WRITE_FAIL);
	}
}

char *word_list_filename(ALL_WORD_LISTS word_list_type)
{
	switch(word_list_type)
	{
	case en_all:
		return "en_all_words.txt";
		break;
	case en_nyt:
		return "en_nyt_words.txt";
		break;
	case en_common:
		return "en_common_words.txt";
		break;
	case fr_all:
		return "fr_all_words.txt";
		break;

	case la_all:
		return "la_all_words.txt";
		break;

	case la_common:
		return "la_com_words.txt";
		break;
	case custom:
		return default_word_list_name;
		break;
	default:
		err(FILENAME_FAIL);
		break;
	}
	err(FILENAME_FAIL);
	return NULL;
}
