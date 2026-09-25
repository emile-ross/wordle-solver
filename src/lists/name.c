#include "../include/header.h"

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
		exit(EXIT_FAILURE);
	case no_word_list:
		fprintf(stderr, "error in list_match()\n");
		err(NO_WORD_LIST);
		exit(EXIT_FAILURE);
	default:
		free(buf);
		err(UNKNOWN_WORD_LIST);
		exit(EXIT_FAILURE);
	}
}

