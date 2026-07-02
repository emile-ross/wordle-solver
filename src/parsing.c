#include "header.h"

#include <ctype.h>

int parsing(int *flag_r, ALL_WORD_LISTS w_list, bool *f_exec, bool filter_include_bl, bool letter_indexed_bl, const char *arguments[], int num_args)
{
	/* this is the way this interprets characters
	 * execute(./binary) flag(-s) letter_position(5) letter(A)
	 * this means all words(in the list) ending in A */

	int letter_arg_index = *flag_r + 1;
	int number_arg_index = *flag_r + 2;
	
	/* check if number of arguments given to parse is enough
	 * will return error if not, this prevents segfault */
	if (letter_arg_index >= num_args) 
	{
		err(CMD_MISSING_ARGS);
	}
	
	if (letter_indexed_bl && number_arg_index >= num_args)
	{
		err(CMD_MISSING_ARGS);
	}

	char (*ptr)[INDEX_LETTERS_WORD];
	uint32_t n_pos_arr = 0;

	if (*f_exec)
	{
		/* initialise the filename with zero 
		 * the filename will be the filename of the word list */
		char filename[128] = {0};

		bool standard_word_list = true;
		buffer_write(filename, 128, get_filename(w_list));

		switch (w_list)
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

		case custom:
			/* standard_word_list = false; */
			n_pos_arr = get_num_lines(filename);
			break;
			
		default:
			err(UNKNOWN_WORD_LIST);
			break;
		}

		ptr = list_match(w_list, &n_pos_arr, standard_word_list);

	
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
		word_letter_index = (int)valid_user_index(user_index);

		word_letter_index = (uint8_t)valid_user_index((long)word_letter_index); /* validate the index the user provided */
		word_letter_index--;	/* decrease the index by one because the user isn't typing an index
								   therefore, we need to convert it from a count to an index */
	}
	else
	{
		word_letter_index = -1;
	}
	
	char letter_indexed = (char)toupper((unsigned char)arguments[letter_arg_index][0]);
	
	char filtered_arr_temp[n_pos_arr][INDEX_LETTERS_WORD];
	int temp_count = 0; /* reset temporary count buffer */
	
	if (verbose)
	{
		printf(ANSI_LCYAN"Parsing through "STYLE_END);
	
		if (*f_exec)
		{
			char **word_list_name;
			char *unknown_word_list = "[Unknown word list]";
	
			switch (w_list)
			{
			case en_nyt:
				word_list_name = &word_list_text[w_list];
				break;
			case en_common:
				word_list_name = &word_list_text[w_list];
				break;
			case en_all:
				word_list_name = &word_list_text[w_list];
				break;
			case la_all:
				word_list_name = &word_list_text[w_list];
				break;
			case fr_all:
				word_list_name = &word_list_text[w_list];
				break;
			case custom:
				word_list_name = &default_word_list_name;
				break;
	
			default:
				word_list_name = &unknown_word_list;
				break;
			}
			printf(ANSI_LCYAN UDRL_S BOLD_S"%s"STYLE_END " ", *word_list_name);
			printf(ANSI_LCYAN"("UDRL_S BOLD_S"first"STYLE_END ANSI_LCYAN" filter)\n"STYLE_END);
		}
		else
		{
			printf(ANSI_LCYAN UDRL_S BOLD_S"the filtered array"STYLE_END" ");
			printf(ANSI_LCYAN"("UDRL_S BOLD_S"not first"STYLE_END ANSI_LCYAN" filter)\n"STYLE_END);
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
				buffer_write(flag_string, flag_length, "--strict");
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
						prev_character_found = true;
				}
				else
					if (prev_character_found)
						break;
			}
		}
		else
		{

			if (verbose)
			{
				buffer_write(flag_string, flag_length, "--excludes");
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
				buffer_write(flag_string, flag_length, "--includes");
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
				buffer_write(flag_string, flag_length, "--absent");
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

	if (*f_exec && w_list == custom)
	{
		free(ptr);
	}
	
	/* set the global "n_possible_answers" to "temp_count" local variable 
	 * this is done in order to prevent breaking the other processes using the global 
	 * it also avoids modifying the global all the time */
	n_possible_answers = temp_count;
	
	/* Write to filtered array */
	for (int k = 0; k < n_possible_answers; k++)
	{
		/* call buffer_write as replacement for strcpy() */
		buffer_write(filtered_arr[k], (size_t)INDEX_LETTERS_WORD, filtered_arr_temp[k]);
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
		*(flag_r) += P_FILTERS_ARG_EXP;
	}
	else
	{
		/* the number of arguments expected when a letter index is specified (3) 
		 * example: "-s A 1" (any word with A at the first position) */
	    	*(flag_r) += G_FILTERS_ARG_EXP;
	}
	
	*(f_exec) = false;
	
	return 0;
}
