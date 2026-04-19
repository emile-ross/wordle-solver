#include "header.h"

int strict_parsing(int *flag_r, enum ALL_WORD_LISTS w_list, bool *f_exec, char *arguments[])
{
    // this is the way this interprets characters
    // execute(./binary) flag(-s) letter_position(5) letter(A)
    // this means all words(in the list) ending in A

    char (*ptr)[6];

    if (*f_exec)
    {
	switch (w_list)
    	{
    	    case nyt:
    	        ptr = words;
    	        break;

    	    case common:
    	        ptr = common_words;
    	        break;

    	    case all:
    	        ptr = all_words;
    	        break;

    	    default:
    	        err(15);
    	        break;
    	}
    }

    int letter_arg_index = *flag_r;
    letter_arg_index++;
    int number_arg_index = letter_arg_index;
    number_arg_index++;

    // word_letter_index is the index of the letter the user is looking for
    //
    // example 1: you want to find all words with A as the first letter
    // 'A' is at index 1
    // "AFTER" would work
    //
    // example 2: if you wanted the find all words with 'T' as the third letter
    // 'T' would be at index 3 
    // "AFTER" would work

    char *endptr;
    int word_letter_index = strtol(arguments[number_arg_index], &endptr, 10);
    word_letter_index--;

    user_index_validation(word_letter_index);

    char letter_indexed = arguments[letter_arg_index][0];

    if (*f_exec)
    {
	if (verbose)
	{
	    printf(ANSI_LCYAN"Parsing through the entire word list (first filter)\n"STYLE_END);
	}
	
        n_possible_answers = 0;	// reset word count buffer
    				// this needs to be reset only once
        for (int j = 0; j < NUM_ALL_WORDS; j++)
	{
	    // compare the specified letter against the words in a loop
	    if (letter_indexed == ptr[j][word_letter_index])
	    {
		memcpy(filtered_arr[n_possible_answers], ptr[j], INDEX_LETTERS_WORD);
		n_possible_answers++;
	    }
	}
    }
    else
    {
        char filtered_arr_temp[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
        int temp_count = 0; // reset temporary count buffer

        for (int k = 0; k < n_possible_answers; k++)
        {
	    // compare the specified letter against the words in a loop
	    if (letter_indexed == filtered_arr[k][word_letter_index])
	    {
		memcpy(filtered_arr_temp[temp_count], filtered_arr[k], INDEX_LETTERS_WORD);
		temp_count++;
            }
        }

        n_possible_answers = temp_count;

	for (int k = 0; k < n_possible_answers; k++)
	{
	    strcpy(filtered_arr[k], filtered_arr_temp[k]);
        }
    }

    if (verbose)
    {
        verbose_printing("--strict", letter_indexed, word_letter_index, n_possible_answers, true);
    }
        
    *(f_exec) = false;
    *(flag_r) += P_FILTERS_ARG_EXP;

    return 0;
}

void exclude_filter()
{
    NUM_ALL_WORDS
    // this is the way this interprets characters
    // execute(./binary) flag(-x) letter_position(5) letter(A)
    // this means all words(in the list) NOT ending in A
    int letter_arg_index = flag_r;
    letter_arg_index++;
    int number_arg_index = letter_arg_index;
    number_arg_index++;
    
    // word_letter_index is the index of the letter the user specified
    //
    // example 1: you want to find all words WITHOUT A as the first letter
    // 'A' is at index 1
    // This is not useful when it's the only flag since it will print about 2200 words...
    // It is useful when combined with other flags because it helps narrow down further the possible words
    
    char *endptr;
    int word_letter_index = strtol(argv[number_arg_index], &endptr, 10);
    word_letter_index--;
    user_index_validation(word_letter_index);
    
    char letter_indexed = argv[letter_arg_index][0];
    
    if (first_execution)
    {
        n_possible_answers = 0;	// reset word count buffer
    				// this needs to be reset only once
        for (int j = 0; j < NUM_WORDS; j++)
        {
    	// compare the specified letter against the words in a loop
    	if (letter_indexed == words[j][word_letter_index])
    	{
    	    strcpy(filtered_arr[n_possible_answers], words[j]);
    	    n_possible_answers++;
    	}
        }
    }
    else
    {
        char filtered_arr_temp[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
        int temp_count = 0; // reset temporary count buffer
        for (int k = 0; k < n_possible_answers; k++)
        {
    	// compare the specified letter against the words in a loop
    	if (letter_indexed != filtered_arr[k][word_letter_index])
            {
    	    strcpy(filtered_arr_temp[temp_count], filtered_arr[k]);
    	    temp_count++;
            }
        }
        n_possible_answers = temp_count;
        for (int k = 0; k < n_possible_answers; k++)
        {
            strcpy(filtered_arr[k], filtered_arr_temp[k]);
        }
    }
    
    if (verbose)
    {
        verbose_printing("--exclude", letter_indexed, word_letter_index, n_possible_answers, false);
    }
    
    first_execution = false;
    flag_r += P_FILTERS_ARG_EXP;
}
