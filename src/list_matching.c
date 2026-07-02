#include "header.h"

char (*list_match(ALL_WORD_LISTS word_list_enum, uint32_t *number_of_words))[6]
{
	uint32_t num_words = 0;

	uint16_t lines = 0;
	char filename[128] = {0};
	buffer_write(filename, 128, get_filename(word_list_enum));
	char *word_list_filename(ALL_WORD_LISTS word_list_type);

	switch (word_list_enum)
	{
	case en_all:
		num_words = NUM_ALL_WORDS;
		break;
	case en_nyt:
		num_words = NUM_WORDS;
		break;
	case en_common:
		num_words = NUM_COMMON_WORDS;
		break;

	case fr_all:
		num_words = NUM_FR_ALL_WORDS;
		break;

	case la_all:
		num_words = NUM_LA_ALL_WORDS;
		break;
	
	case la_common:
		num_words = NUM_LA_COM_WORDS;
		break;

	case custom:
		/* standard_word_list = false; */
		lines = get_num_lines(filename);
		num_words = (int)lines;
		break;
		
	default:
		/* a word list entry is missing in this switch statement */
		err(UNKNOWN_WORD_LIST);
		break;
	}

	*(number_of_words) = num_words;

	/* allocate memory for the pointer */
	return read_words(filename, &num_words);
}
