#include "header.h"

int list_match(ALL_WORD_LISTS word_list_enum, char (*(*word_list_pointer))[INDEX_LETTERS_WORD])
{
	int number_of_words = 0;
	switch (word_list_enum)
	{
	case nyt:
		*word_list_pointer = nyt_words;
		number_of_words = NUM_WORDS;
		break;
	case common:
		*word_list_pointer = common_words;
		number_of_words = NUM_COMMON_WORDS;
		break;
	case fr_all:
		*word_list_pointer = fr_all_words;
		number_of_words = NUM_FR_ALL_WORDS;
		break;

	case la_all:
		*word_list_pointer = la_all_words;
		number_of_words = NUM_LA_ALL_WORDS;
		break;

	case la_common:
		*word_list_pointer = la_com_words;
		number_of_words = NUM_LA_COM_WORDS;
		break;

	case all:
		*word_list_pointer = all_words;
		number_of_words = NUM_ALL_WORDS;
		break;

	default:
		/* word list entry is missing in this switch statement */
		err(UNKNOWN_WORD_LIST);
		break;
	}

	return number_of_words;
}
