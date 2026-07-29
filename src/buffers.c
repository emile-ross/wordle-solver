#include "include/header.h"

#include <stdarg.h>

/* check_buf() is in checks.c */

int buffer_write(void *buf_to_free[], char *string, size_t size_of_string, const char *restrict format, ...)
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
		return 1;
	}

	int ret = vsnprintf(format_str, (size_t)format_str_size, format, args);
	va_end(args);


	if (buf_to_free != NULL)
	{
		void* arr[max_valid_args];
		uint16_t i = 0;
		for (i = 0; buf_to_free[i] != NULL; i++)
		{
			arr[i] = buf_to_free[i];
		}
		i++; arr[i] = format_str;
		i++; arr[i] = NULL;
		check_buf(ret, format_str_size, arr);
	}
	else
	{
		check_buf(ret, format_str_size, NULL);
	}

	int return_value = snprintf(string, size_of_string, "%s", format_str);
	free(format_str);
	check_buf(return_value, (int)size_of_string, buf_to_free);

	/* check if the string was truncated after the use of snprintf */
	if ((size_t)return_value >= size_of_string)
	{
		if (buf_to_free != NULL)
		{
			for (uint16_t i = 0; buf_to_free[i] != NULL; i++)
			{
				free(buf_to_free[i]);
			}
		}
		return 1;
	}
	return 0;
}

size_t prepend_fp(char *file_path_dst, size_t dst_size, char *filename)
{
	/* this function prepends (adds in front) the filename with the directory
	 * in order for the wordle solver to be able to resolve the file paths correctly */ 

	const char *filepath_template = "%s/%s";

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
