#include "header.h"

#include <stdarg.h>

void check_buf(int return_value, int size_of_buffer, void *buf_to_free[])
{
	/* check if the string was truncated after the use of snprintf */
	if (return_value < 0 || return_value >= size_of_buffer)
	{
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

void buffer_write(void *buf_to_free[], char *string, size_t size_of_string, const char *restrict format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the message */
	int format_str_size = 1 + vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	/* allocate memory for the warning message */
	char *format_str = malloc((size_t)format_str_size);
	if (format_str == NULL)
	{
		err(MALLOC_FAIL);
	}

	int ret = vsnprintf(format_str, (size_t)format_str_size, format, args);
	va_end(args);

	void* arr[2] = { format_str, NULL };
	check_buf(ret, format_str_size, arr);


	int return_value = snprintf(string, size_of_string, "%s", format_str);
	check_buf(return_value, (int)size_of_string, buf_to_free);

	/* check if the string was truncated after the use of snprintf */
	if ((size_t)return_value >= size_of_string)
	{
		if (buf_to_free != NULL)
		{
			for (uint8_t i = 0; buf_to_free[i] != NULL; i++)
			{
				free(buf_to_free[i]);
			}
		}
		err(BUFFER_WRITE_FAIL);
		exit(1);
	}
}

/* this is the default custom name for the word list
 * this is the name we use by default in the config.c file
 *
 * if this matches with the name in the config.c file, this 
 * means that the user never changed it */
const char *default_config_list_name = "default_custom_list.txt";	

char *get_filename(ALL_WORD_LISTS word_list_type)
{
	switch (word_list_type)
	{
	case en_all:
		return "en_all_words.txt";
	case en_nyt:
		return "en_nyt_words.txt";
	case en_common:
		return "en_com_words.txt";
	case fr_all:
		return "fr_all_words.txt";
	case la_all:
		return "la_all_words.txt";
	case la_common:
		return "la_com_words.txt";
	case custom_list:
		if (strcmp(default_config_list_name, custom_list_name) == 0)
		{
			char buffer[128];
			return get_custom_file(buffer, sizeof(buffer));
		}
		else
		{
			return custom_list_name;
		}
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

char *get_custom_file(char *buffer, size_t buffer_size)
{
	printf(ANSI_GREY"Edit the "BOLD_S"custom_list_name"STYLE_END ANSI_GREY" word list name in the "BOLD_S"src/config.c \n"STYLE_END ANSI_GREY
			"configuration file in order to avoid typing the file path each time\n"STYLE_END);

	printf("Type the path to your word list: ");
	if (fgets(buffer, (int)buffer_size, stdin) == NULL)
	{
		err(INPUT_FAIL);
	}

	uint8_t name_len = (uint8_t)strcspn(buffer, "\n");
	buffer[name_len] = '\0';	/* replace \n with \0 to terminate the string */

	return buffer;
}
