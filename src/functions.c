#include "include/header.h"

#include <stdarg.h>

const char *word_list_flag = "-w";
const char *word_list_long_flag = "--word-list";

uint8_t NUM_WORD_LISTS = la_all;

/* BTW: functions related to buffers were moved to src/buffers.c */

char *word_list_name(ALL_WORD_LISTS word_list_type, void *buf)
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
	case custom_list:
		return "custom word list";
	default:
		free(buf);
		err(UNKNOWN_WORD_LIST);
		exit(1);
	}
}

void verbose_print(const char *restrict format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the verbose message */
	size_t msg_size = 1 + (size_t)vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	/* allocate memory for the verbose message */
	char *verbose_msg = malloc(msg_size);

	void *arr[2] = 
	{
		verbose_msg,
		NULL
	};

	if (verbose_msg == NULL)
	{
		err(MALLOC_FAIL);
		exit(1);
	}
	size_t ret = (size_t)vsnprintf(verbose_msg, msg_size, format, args);

	check_buf((int)ret, (int)msg_size, arr);


	va_end(args);

	if (ret > msg_size)
	{
		free(verbose_msg);
		err(VERBOSE_FAIL);
		exit(1);
	}

	printf(ANSI_LCYAN"%s"STYLE_END, verbose_msg);
	free(verbose_msg);
}
