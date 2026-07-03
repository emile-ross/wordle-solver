#include "header.h"

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
	int return_value = snprintf(string, size_of_string, "%s", format);
	check_buf(return_value, (int)size_of_string);

	/* check if the string was truncated after the use of snprintf */
	if ((size_t)return_value >= size_of_string)
	{
		err(BUFFER_WRITE_FAIL);
	}
}

char *get_filename(ALL_WORD_LISTS word_list_type)
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
		return "en_com_words.txt";
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
		return custom_list_name;
		break;
	default:
		err(FILENAME_FAIL);
		break;
	}
	err(FILENAME_FAIL);
	return NULL;
}

size_t prepend_fp(char *file_path_dst, size_t dst_size, char *filename)
{
	/* this function prepends (adds in front) the filename with the directory
	 * in order for the wordle solver to be able to resolve the file paths correctly */ 

	const char *filepath_template = "%s/%s";
	const char *dir = "src/word-lists";

	size_t total_size = 0;
	if (filename != NULL)
	{
		/* calculate the size of the possible output */
		total_size = 1 + (size_t)snprintf(NULL, 0, filepath_template, dir, filename);
	}
	else
	{
		err(FILEPATH_FAIL);
		return 1;
	}

	if (file_path_dst != NULL)
	{
		if (dst_size >= total_size)
		{
			/* write to path_to_file buffer */
			snprintf(file_path_dst, dst_size, filepath_template, dir, filename);
			return 0;
		}
		else
		{
			err(FILEPATH_FAIL);
			return 1;
		}
	}
	else
	{
		if (total_size > 1)
		{
			return total_size;
		}
		else
		{
			err(FILEPATH_FAIL);
			return 1;
		}
	}
	return 0;
}

char *get_custom_file(void)
{
	char buffer[120];
	if (fgets(buffer, sizeof(buffer), stdin) == NULL)
	{
		err(INPUT_FAIL);
	}
	return buffer;
}
