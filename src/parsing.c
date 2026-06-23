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

	const char (*ptr)[INDEX_LETTERS_WORD];
	
	int n_pos_arr;
	
	if (*f_exec)
	{

		n_pos_arr = list_match(w_list, &ptr);
		switch (w_list)
		{
		case en_all:
			ptr = all_words;
			n_pos_arr = NUM_ALL_WORDS;
			break;
		case en_nyt:
			ptr = nyt_words;
			n_pos_arr = NUM_WORDS;
			break;
		case en_common:
			ptr = common_words;
			n_pos_arr = NUM_COMMON_WORDS;
			break;

		case fr_all:
			ptr = fr_all_words;
			n_pos_arr = NUM_FR_ALL_WORDS;
			break;

		case la_all:
			ptr = la_all_words;
			n_pos_arr = NUM_LA_ALL_WORDS;
			break;
	
		case la_common:
			ptr = la_com_words;
			n_pos_arr = NUM_LA_COM_WORDS;
			break;
			
		default:
			err(UNKNOWN_WORD_LIST);
			break;
		}
	
		/* since this is the first execution, it will parse through the entire array */
		n_possible_answers = 0;	
		/* reset word count buffer this needs to be reset only once */
	}
	else
	{
		if (n_possible_answers == 0)
		{
			err(20);
		}
		/* rename variables */
		ptr = (const char (*)[INDEX_LETTERS_WORD])filtered_arr;
		n_pos_arr = n_possible_answers;
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
	
	/* parsing logic is below for all options */
	size_t str_size = 24;
	char *flag_string = malloc(24);	/* allocate enough memory for the flag_string (24 bytes) */
	
	if (letter_indexed_bl)
	{
		if (filter_include_bl)
		{
			snprintf(flag_string, str_size, "--strict");
			bool first_character = false;
			bool prev_character_found = false;
		
			if (word_letter_index == 0)
				first_character = true;
		
			for (int j = 0; j < n_pos_arr; j++)
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
			snprintf(flag_string, str_size, "--exclude");
			for (int j = 0; j < n_pos_arr; j++)
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
			snprintf(flag_string, str_size, "--includes");
			for (int j = 0; j < n_pos_arr; j++)
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
			snprintf(flag_string, str_size, "--absent");
			for (int j = 0; j < n_pos_arr; j++)
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
	
	/* set the global "n_possible_answers" to "temp_count" local variable 
	 * this is done in order to prevent breaking the other processes using the global 
	 * it also avoids modifying the global all the time */
	n_possible_answers = temp_count;
	
	/* Write to filtered array */
	for (int k = 0; k < n_possible_answers; k++)
	{
		strcpy(filtered_arr[k], filtered_arr_temp[k]);
	}

	/* display verbose message if verbose mode is enabled */
	if (verbose)
	        verbose_printing(flag_string, letter_indexed, word_letter_index, n_possible_answers, true);

	free(flag_string);	/* free after use */
	
	int arg_offset = 0;
	if (letter_indexed_bl)
	    	arg_offset = P_FILTERS_ARG_EXP;
	else
	    	arg_offset = G_FILTERS_ARG_EXP;
	
	*(flag_r) += arg_offset;
	*(f_exec) = false;
	
	return 0;
}
