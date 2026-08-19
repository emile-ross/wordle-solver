#include "include/header.h"

#define setwords(wordList) \
		num_words = wordList; \
		break;


char (*list_match(ALL_WORD_LISTS word_list_enum, uint32_t *number_of_words, bool standard_word_list))[6]
{
	char filename[max_filename_length] = {0};

	if (word_list_enum == custom_list)
	{
		if (custom_filename == NULL)
		{
			fprintf(stderr, "error: custom_filename is NULL (it hasn't been allocated yet)\n");
			exit(1);
		}

		if (buffer_write(NULL, filename, max_filename_length, custom_filename) != 0)
		{
			err(BUFFER_WRITE_FAIL);
		}
	}
	else 
	{
		if (buffer_write(NULL, filename, max_filename_length, get_filename(word_list_enum)) != 0)
		{
			err(BUFFER_WRITE_FAIL);
		}
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

	uint32_t num_words = 0;
	/* set the number of words in the list using the setwords macro */
	switch (word_list_enum)
	{
	case en_all:
		setwords(NUM_ALL_WORDS);
	case en_nyt:
		setwords(NUM_WORDS);
	case en_common:
		setwords(NUM_COMMON_WORDS);
	case fr_all:
		setwords(NUM_FR_ALL_WORDS);
	case la_all:
		setwords(NUM_LA_ALL_WORDS);
	case la_common:
		setwords(NUM_LA_COM_WORDS);
	case custom_list:
		/* standard_word_list = false; */
		setwords(get_num_lines(filename));

	case undefined_list:
		fprintf(stderr, "error in list_match()\n");
		err(UNDEFINED_LIST);
		exit(1);

	case no_word_list:
		fprintf(stderr, "error in list_match()\n");
		err(NO_WORD_LIST);
		exit(1);
		
	default:
		/* a word list entry is missing in this switch statement */
		err(UNKNOWN_WORD_LIST);
		break;
	}

	*(number_of_words) = num_words;

	/* allocate memory for the pointer */
	return read_words(filename, &num_words);
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
			size_t buffer_size = 128;
			char *buffer = malloc(buffer_size);
			custom_filename = buffer;
			return get_custom_file(buffer, buffer_size);
		}
		else
		{
			return custom_list_name;
		}
	case undefined_list:
		fprintf(stderr, "error in get_filename()\n");
		err(UNDEFINED_LIST);
		exit(1);

	case no_word_list:
		fprintf(stderr, "error in get_filename()\n");
		err(NO_WORD_LIST);
		exit(1);

	default:
		err(FILENAME_FAIL);
		break;
	}
	err(FILENAME_FAIL);
	return NULL;
}
