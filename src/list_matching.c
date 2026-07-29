#include "include/header.h"

char (*list_match(ALL_WORD_LISTS word_list_enum, uint32_t *number_of_words, bool standard_word_list))[6]
{

	char filename[max_filename_length] = {0};
	if (buffer_write(NULL, filename, max_filename_length, get_filename(word_list_enum)) != 0)
	{
		err(BUFFER_WRITE_FAIL);
	}

	if (word_list_enum == custom_list)
	{
		standard_word_list = false;
	}

	if (standard_word_list)
	{
		size_t full_path_size = prepend_fp(NULL, 0, filename);
		if (full_path_size > sizeof(filename))
		{
			err(FILEPATH_FAIL);
		}

		char *temp_path_buffer = malloc(full_path_size);
		if (temp_path_buffer == NULL)
		{
			free(temp_path_buffer);
			err(MALLOC_FAIL);
		}
		prepend_fp(temp_path_buffer, full_path_size, filename);

		/* write to the filename string from the temp_full_path buffer */
		void *arr[2] = { temp_path_buffer, NULL };
		if (buffer_write(arr, filename, full_path_size, temp_path_buffer) != 0)
		{
			err(BUFFER_WRITE_FAIL);
		}

		free(temp_path_buffer);
	}

	char *word_list_filename(ALL_WORD_LISTS word_list_type);

	uint32_t num_words = 0;
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

	case custom_list:
		/* standard_word_list = false; */
		num_words = get_num_lines(filename);
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
