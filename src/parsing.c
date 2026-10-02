#include "include/header.h"

uint32_t initial_words = 0;

#define filename_len 128

int parsing(struct prs_args parsing_args, enum parsing_type type)
{
	/* this is the way this interprets characters
	 * execute(./binary) flag(-s) letter_position(5) letter(A)
	 * this means all words(in the list) ending in A */

	int index = parsing_args.index;
	
	char letter_indexed = parsing_args.letter_indexed;
	printf("%c is indexed\n", letter_indexed);


	if (!(is_letter(letter_indexed)))
	{
		err(INVALID_LETTER);
		exit(1);
	}

	/* in cases where the parsing type is 
	 * "strict" or "exclude", an index must be specified */
	bool letter_is_indexed = false;
	if (type == strict || type == exclude)
	{
		letter_is_indexed = true;
	}

	/* 
	if (letter_is_indexed && number_arg_index >= parsing_args.num_args)
	{
		err(CMD_MISSING_ARGS);
	}
	*/

	char (*ptr)[INDEX_LETTERS_WORD] = NULL;
	uint32_t n_pos_arr = 0;

	if (*(parsing_args.first_exec))
	{
		/* initialise the filename with zero 
		 * the filename will be the filename of the word list */
		char filename[filename_len] = {0};

		if (buffer_write(NULL, filename, filename_len, get_filename(parsing_args.w_list)) != 0)
		{
			err(BUFFER_WRITE_FAIL);
			exit(1);
		}
		
		bool standard_word_list = true;


		set_length(parsing_args.w_list, &n_pos_arr, filename);

		ptr = list_match(parsing_args.w_list, &n_pos_arr, standard_word_list);
	
		/* since this is the first execution, it will parse through the entire array */
		n_possible_answers = 0;	
		/* reset word count buffer this needs to be reset only once */
	}
	else
	{
		/* rename variables */
		ptr = (char (*)[INDEX_LETTERS_WORD])filtered_arr;
		n_pos_arr = (uint16_t)n_possible_answers;
	}

	/* index is the index of the letter the user is looking for
	 *
	 * example 1: you want to find all words with A as the first letter
	 * 'A' is at index 1
	 * "AFTER" would work
	 *
	 * example 2: if you wanted the find all words with 'T' as the third letter
	 * 'T' would be at index 3 
	 * "AFTER" would work */
	
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
	
	/* parsing logic is below for all options */
	switch (type)
	{
	case strict:
		bool first_character = false;
		bool prev_character_found = false;
	
		if (index == 0)
			first_character = true;
	
		for (uint32_t j = 0; j < n_pos_arr; j++)
		{
			/* compare the specified letter against the words in a loop */
			if (letter_indexed == ptr[j][index])
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
		break;
	case exclude:
		for (uint32_t j = 0; j < n_pos_arr; j++)
		{
			/* compare the specified letter against the words in a loop */
			if (letter_indexed != ptr[j][index])
			{
				memcpy(filtered_arr_temp[temp_count], ptr[j], INDEX_LETTERS_WORD);
				temp_count++;
			}
		}
		break;
	case include:
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
		break;
	case absent:
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
		break;
	}

	if (*(parsing_args.first_exec))
	{
		free(ptr);
	}
	
	/* set the global "n_possible_answers" to "temp_count" local variable 
	 * this is done in order to prevent breaking the other processes using the global 
	 * it also avoids modifying the global all the time */
	n_possible_answers = temp_count;

	if (n_possible_answers == 0)
	{
		/* free ptr before exiting */
		if (*(parsing_args.first_exec))
		{
			if (ptr != NULL)
			{
				free(ptr);
			}
		}
		err(NO_POSSIBLE_ANSWERS);
	}

	/* Write to filtered array */
	for (uint32_t k = 0; k < n_possible_answers; k++)
	{
		/* call buffer_write as replacement for strcpy() */
		buffer_write(NULL, filtered_arr[k], INDEX_LETTERS_WORD, filtered_arr_temp[k]);
	}

	/* display verbose message if verbose mode is enabled */
	if (verbose)
	{
		verbose_printing(mode_to_text(type), letter_indexed, index, n_possible_answers, true);
	}

	/* offset the flag_r iterator by the number of arguments we used here 
	 * ("-s A 1" would count as 3) */
	if (letter_is_indexed)
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
