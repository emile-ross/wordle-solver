#include "../include/header.h"

#include <stdarg.h>

/* check_buf() is in checks.c */

int buffer_write(void *buf_to_free[], char *str, const size_t size_of_string, const char *restrict format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the message */
	size_t format_str_size = 1 + (size_t)vsnprintf(NULL, 0, format, copy);

	/* compare the buffer size to the string length (error checking) */
	if (format_str_size > size_of_string)
	{
		fprintf(stderr, "Insufficient memory allocated for the string\n");
		err(BUFFER_WRITE_FAIL);
		return 1;
	}
	va_end(copy);

	/* write the contents of format, args to the 'str' string */
	int ret = vsnprintf(str, format_str_size, format, args);
	va_end(args);

	check_buf(ret, (int)format_str_size, buf_to_free);
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
		if (installed_package)
		{
			total_size = (size_t)snprintf(NULL, 0, filepath_template, LIST_SHARE_PATH, filename);
		}
		else
		{
			total_size = (size_t)snprintf(NULL, 0, filepath_template, path_to_lists, filename);
		}
		/* account for null terminator */
		total_size++;
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
			if (installed_package)
			{
				snprintf(file_path_dst, dst_size, filepath_template, LIST_SHARE_PATH, filename);
			}
			else
			{
				snprintf(file_path_dst, dst_size, filepath_template, path_to_lists, filename);
			}
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
	if (verbose)
	{
		verbose_print("buffer_size = %zu\nname_len (valid characters in filename) = %u\n", buffer_size, name_len);
	}
	buffer[name_len] = '\0';	/* replace \n with \0 to terminate the string */

	return buffer;
}

void safe_write(char **str, size_t *buffer_size, const char *restrict fmt, ...)
{
	va_list args, copy;

	va_start(args, fmt);
	va_copy(copy, args);
	
	int ret = 1 + vsnprintf(*(str), *(buffer_size), fmt, copy);
	va_end(copy);	/* copy was used */

	if (ret > (signed)(*(buffer_size)))
	{
		if (verbose)
		{
			verbose_print("safe_write() prevented truncation (buffer size from %zu bytes to %zu bytes)\n", *(buffer_size), ret);
		}

		if (ret < 0)
		{
			err(ZERO_SIZED_BUF);
			return;
		}

		*(str) = realloc(*(str), (unsigned)ret);
		*(buffer_size) = (unsigned)ret;
		vsnprintf(*(str), (unsigned)ret, fmt, args);
	}

	va_end(args);
}

void *smalloc(size_t size)
{
	void *str = NULL;
	if (size <= 0)
	{
		fprintf(stderr, "error in smalloc() fn\n");
		err(ZERO_SIZED_BUF);
	}

	str = malloc(size);
	if (str == NULL)
		err(MALLOC_FAIL);

	return str;
}

