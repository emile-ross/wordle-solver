#include "header.h"

#include <ctype.h>

int parsing(struct prs_args parsing_args, bool filter_include_bl, bool letter_indexed_bl, const char *arguments[])
{
	/* this is the way this interprets characters
	 * execute(./binary) flag(-s) letter_position(5) letter(A)
	 * this means all words(in the list) ending in A */

	int letter_arg_index = *(parsing_args.flag_r) + 1;
	int number_arg_index = *(parsing_args.flag_r) + 2;
	
	/* check if number of arguments given to parse is enough
	 * will return error if not, this prevents segfault */
	if (letter_arg_index >= parsing_args.num_args) 
	{
		err(CMD_MISSING_ARGS);
	}
	
	if (letter_indexed_bl && number_arg_index >= parsing_args.num_args)
	{
		err(CMD_MISSING_ARGS);
	}

	char (*ptr)[INDEX_LETTERS_WORD] = NULL;
	uint32_t n_pos_arr = 0;

	if (*(parsing_args.first_exec))
	{
		/* initialise the filename with zero 
		 * the filename will be the filename of the word list */
		char filename[128] = {0};

		bool standard_word_list = true;

		if (0 != buffer_write(NULL, filename, 128, get_filename(parsing_args.w_list)))
		{
			err(BUFFER_WRITE_FAIL);
		}

		switch (parsing_args.w_list)
		{
		case en_all:
			n_pos_arr = NUM_ALL_WORDS;
			break;
		case en_nyt:
			n_pos_arr = NUM_WORDS;
			break;
		case en_common:
			n_pos_arr = NUM_COMMON_WORDS;
			break;

		case fr_all:
			n_pos_arr = NUM_FR_ALL_WORDS;
			break;

		case la_all:
			n_pos_arr = NUM_LA_ALL_WORDS;
			break;
	
		case la_common:
			n_pos_arr = NUM_LA_COM_WORDS;
			break;

		case custom_list:
			/* standard_word_list = false; */
			n_pos_arr = get_num_lines(filename);
			break;
			
		default:
			err(UNKNOWN_WORD_LIST);
			break;
		}

		ptr = list_match(parsing_args.w_list, &n_pos_arr, standard_word_list);
	
		/* since this is the first execution, it will parse through the entire array */
		n_possible_answers = 0;	
		/* reset word count buffer this needs to be reset only once */
	}
	else
	{
		if (n_possible_answers == 0)
		{
			err(NO_POSSIBLE_ANSWERS);
		}
		/* rename variables */
		ptr = (char (*)[INDEX_LETTERS_WORD])filtered_arr;
		n_pos_arr = (uint16_t)n_possible_answers;
	}

	/* word_letter_index is the index of the letter the user is looking for
	 *
	 * example 1: you want to find all words with A as the first letter
	 * 'A' is at index 1
	 * "AFTER" would work
	 *
	 * example 2: if you wanted the find all words with 'T' as the third letter
	 * 'T' would be at index 3 
	 * "AFTER" would work */
	
	char *endptr;
	int word_letter_index;
	if (letter_indexed_bl)
	{
		/* convert the string containing the index to the letter
		 * this will convert it to a long and then it casts it to an int (word_letter_index) */
		long user_index = strtol(arguments[number_arg_index], &endptr, 10);
		if (strcmp(endptr, arguments[number_arg_index]) == 0)
		{
			/* the strings are matching, therefore no valid characters were found */

			/* TODO add error message for this specific case */
			free(ptr);
			err(INVALID_INDEX);
		}
		if (*endptr != '\0')
		{
			/* there was at least one invalid character */

			/* TODO add error message for this specific case */
			free(ptr);
			err(INVALID_INDEX);
		}

		word_letter_index = (int)valid_user_index(user_index, (void*)ptr);

		word_letter_index = (uint8_t)valid_user_index((long)word_letter_index, (void*)ptr); /* validate the index the user provided */
		word_letter_index--;	/* decrease the index by one because the user isn't typing an index
								   therefore, we need to convert it from a count to an index */
		if (word_letter_index < 0)
		{
			/* this is just an invalid index */
			free(ptr);
			err(INVALID_INDEX);
		}
	}


	if (arguments[letter_arg_index][0] == '\0')
	{
		if (*(parsing_args.first_exec))
		{
			free(ptr);
		}
		err(INVALID_LETTER);
	}

	char letter_indexed = (char)toupper((unsigned char)arguments[letter_arg_index][0]);
	if (!(isalpha(letter_indexed)))
	{
		if (*(parsing_args.first_exec))
		{
			free(ptr);
		}
		err(INVALID_LETTER);
		exit(1);
	}
	
	char filtered_arr_temp[n_pos_arr][INDEX_LETTERS_WORD];
	uint32_t temp_count = 0; /* reset temporary count buffer */
	
	if (verbose)
	{
		verbose_print(ANSI_LCYAN"Parsing through "STYLE_END);
	
		if (*(parsing_args.first_exec))
		{
			verbose_print(UDRL_S BOLD_S"%s"STYLE_END " ", word_list_name(parsing_args.w_list, (void*)ptr));
			verbose_print("("UDRL_S BOLD_S"first");
			verbose_print(" filter)\n");
		}
		else
		{
			verbose_print(UDRL_S BOLD_S"the filtered array");
			verbose_print(" ("UDRL_S BOLD_S"not first");
			verbose_print(" filter)\n");
		}
	}
	
	char flag_string[24] = {0};
	size_t flag_length = sizeof(flag_string);

	/* parsing logic is below for all options */

	if (letter_indexed_bl)
	{
		if (filter_include_bl)
		{
			/* buffer_write() is safer than using strcpy()
			 * this copies the last string specified to the flag_string buffer */
			if (verbose)
			{
				if (0 != buffer_write(NULL, flag_string, flag_length, "--strict"))
				{
					if (*(parsing_args.first_exec))
					{
						free(ptr);
					}
					err(BUFFER_WRITE_FAIL);
				}
			}

			bool first_character = false;
			bool prev_character_found = false;
		
			if (word_letter_index == 0)
				first_character = true;
		
			for (uint32_t j = 0; j < n_pos_arr; j++)
			{
				/* compare the specified letter against the words in a loop */
				if (letter_indexed == ptr[j][word_letter_index])
				{
					memcpy(filtered_arr_temp[temp_count], ptr[j], INDEX_LETTERS_WORD);
					temp_count++;
		
					if (!prev_character_found && first_character)
					{
						prev_character_found = true;
					}
				}
				else
				{
					if (prev_character_found)
					{
						break;
					}
				}
			}
		}
		else
		{
			if (verbose)
			{

				if (buffer_write(NULL, flag_string, flag_length, "--excludes") != 0)
				{
					if (*(parsing_args.first_exec))
					{
						free(ptr);
					}
					err(BUFFER_WRITE_FAIL);
				}
			}

			for (uint32_t j = 0; j < n_pos_arr; j++)
			{
				/* compare the specified letter against the words in a loop */
				if (letter_indexed != ptr[j][word_letter_index])
				{
					memcpy(filtered_arr_temp[temp_count], ptr[j], INDEX_LETTERS_WORD);
					temp_count++;
				}
			}
		}
	}
	else
	{
		if (filter_include_bl)
		{
			if (verbose)
			{
				if (buffer_write(NULL, flag_string, flag_length, "--includes") != 0)
				{
					err(BUFFER_WRITE_FAIL);
				}
			}

			for (uint32_t j = 0; j < n_pos_arr; j++)
			{
				/* compare the specified letter against the words in a loop */
				for (int k = 0; k < NUM_LETTERS_WORD; k++)
				{
					if (letter_indexed == ptr[j][k])
					{
						memcpy(filtered_arr_temp[temp_count], ptr[j], INDEX_LETTERS_WORD);
						temp_count++;
						break;
					}
				}
			}
		}
		else
		{
			if (verbose)
			{
				if (buffer_write(NULL, flag_string, flag_length, "--absent") != 0)
				{
					err(BUFFER_WRITE_FAIL);
				}
			}

			for (uint32_t j = 0; j < n_pos_arr; j++)
			{
				bool letter_match = false;
				/* compare the specified letter against the words in a loop */
				for (int k = 0; k < NUM_LETTERS_WORD; k++)
				{
					if (letter_indexed == ptr[j][k])
					{
						letter_match = true;
						break;
					}
				}
				if (!letter_match)
				{
					memcpy(filtered_arr_temp[temp_count], ptr[j], INDEX_LETTERS_WORD);
					temp_count++;
				}
			}
		}
	}

	if (*(parsing_args.first_exec))
	{
		free(ptr);
	}
	
	/* set the global "n_possible_answers" to "temp_count" local variable 
	 * this is done in order to prevent breaking the other processes using the global 
	 * it also avoids modifying the global all the time */
	n_possible_answers = temp_count;
	
	/* Write to filtered array */
	for (uint32_t k = 0; k < n_possible_answers; k++)
	{
		/* call buffer_write as replacement for strcpy() */
		buffer_write(NULL, filtered_arr[k], INDEX_LETTERS_WORD, filtered_arr_temp[k]);
	}

	/* display verbose message if verbose mode is enabled */
	if (verbose) {
		verbose_printing(flag_string, letter_indexed, word_letter_index, n_possible_answers, true);
	}

	/* offset the flag_r iterator by the number of arguments we used here 
	 * ("-s A 1" would count as 3) */
	if (letter_indexed_bl)
	{
		/* the number of arguments expected when no index is specified (2)
		 * example: "-a Z" (any word without Z) */
		*(parsing_args.flag_r) += P_FILTERS_ARG_EXP;
	}
	else
	{
		/* the number of arguments expected when a letter index is specified (3) 
		 * example: "-s A 1" (any word with A at the first position) */
	    	*(parsing_args.flag_r) += G_FILTERS_ARG_EXP;
	}
	
	*(parsing_args.first_exec) = false;
	
	return 0;
}
