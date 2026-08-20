#include "include/header.h"

#include <stdarg.h>

const char *word_list_flag = "-w";
const char *word_list_long_flag = "--word-list";

uint8_t NUM_WORD_LISTS = la_all;

char *custom_filename = NULL;
bool installed_package = true;

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

	case undefined_list:
		fprintf(stderr, "error in list_match()\n");
		err(UNDEFINED_LIST);
		exit(1);
	case no_word_list:
		fprintf(stderr, "error in list_match()\n");
		err(NO_WORD_LIST);
		exit(1);
	default:
		free(buf);
		err(UNKNOWN_WORD_LIST);
		exit(1);
	}
}

