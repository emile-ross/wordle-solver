#include "header.h"

char filtered_arr[NUM_WORDS][INDEX_LETTERS_WORD];

int n_possible_answers;

int main(int argc, char *argv[])
{
    bool first_execution = true;
    int ARGS_BEFORE_CUR_FLAG = ARGS_BEFORE_FLAG_BASE;

    if (argc >= 2)  // or else there's nothing
    {
	// in order to ignore the first argument of the command (probably the execution command)
	int flag_r = ARGS_BEFORE_CUR_FLAG; // doesn't require all flags to have 3 arguments

	while(flag_r < argc)
	{
	    if (strcmp(argv[flag_r], "--word-list") == 0 || strcmp(argv[flag_r], "-w") == 0)
	    {
		// TODO:
		// attempt to read the flag after the flag
		// assign the corresponding word list to the enum

		// this sets the word list as the common word list (5700 words)
		enum ALL_WORD_LISTS word_list = common;
	        flag_r += WORD_LIST_ARG_EXP;
	    }
	    else if (strcmp(argv[flag_r], "--strict") == 0 || strcmp(argv[flag_r], "-s") == 0)
	    {
	        // this is the way this interprets characters
	        // execute(./binary) flag(-s) letter_position(5) letter(A)
	        // this means all words(in the list) ending in A
	        int letter_arg_index = flag_r;
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
	            char filtered_arr_temp[NUM_WORDS][INDEX_LETTERS_WORD];
		    int temp_count = 0; // reset temporary count buffer
		    for (int k = 0; k < n_possible_answers; k++)
		    {
			// compare the specified letter against the words in a loop
			if (letter_indexed == filtered_arr[k][word_letter_index])
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
		    verbose_printing("--strict", letter_indexed, word_letter_index, n_possible_answers, true);
		}
		    
	        first_execution = false;
	        flag_r += P_FILTERS_ARG_EXP;
	    }
	    else if (strcmp(argv[flag_r], "--exclude") == 0 || strcmp(argv[flag_r], "-x") == 0 || strcmp(argv[flag_r], "-e") == 0)
	    {
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
	            char filtered_arr_temp[NUM_WORDS][INDEX_LETTERS_WORD];
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
	    else if (strcmp(argv[flag_r], "--includes") == 0 || strcmp(argv[flag_r], "-i") == 0)
	    {
	        int letter_arg_index = flag_r;
	        letter_arg_index++;

	        char letter_indexed = argv[letter_arg_index][0];

	        if (first_execution)
	        {
		    n_possible_answers = 0;	// reset word count buffer
						// this needs to be reset only once
		    for (int j = 0; j < NUM_WORDS; j++)
	            {
			// compare the specified letter against the words in a loop
			for (int k = 0; k < NUM_LETTERS_WORD; k++)
			{
			    if (letter_indexed == words[j][k])
			    {
				strcpy(filtered_arr[n_possible_answers], words[j]);
				n_possible_answers++;
			    }
			}
		    }
	        }
	        else
	        {
		    int buffer_size_word = NUM_LETTERS_WORD + 1;
	            char filtered_arr_temp[NUM_WORDS][buffer_size_word];
		    int temp_count = 0; // reset temporary count buffer
		    for (int k = 0; k < n_possible_answers; k++)
		    {
			// compare the specified letter against the words in a loop
			for (int l = 0; l < NUM_LETTERS_WORD; l++)
			{
			    if (letter_indexed == filtered_arr[k][l])
	                    {
				strcpy(filtered_arr_temp[temp_count], filtered_arr[k]);
				temp_count++;
	                    }
			}
		    }

	            n_possible_answers = temp_count;
	            for (int k = 0; k < n_possible_answers; k++)
		    {
			strcpy(filtered_arr[k], filtered_arr_temp[k]);
	            }
	        }

	        first_execution = false;
	        flag_r += G_FILTERS_ARG_EXP;
		if (verbose)
		{
		    verbose_printing("--includes", letter_indexed, -1, n_possible_answers, true);
		}
	    }
	    else
	    {
	        err(10);
	    }

	    // read (P_FILTERS_ARG_EXP) ahead of the previous read
	    //
	    // example:
	    // the input is the following:
	    // ./binary -s A 1 -s D 2
	    // the first read is "-s A 1"
	    // P_FILTERS_ARG_EXP is 3 since the previous read had 3 arguments
	    // the next line will skip 3 because it's reading the next 3 arguments (-s D 2)

	    // G_FILTERS_ARG_EXP is 2 since the flags with it only read 2 arguments (-i D)
	    // this means the word has a 'D'
	}
    }
    else
    {
	err(1);
    }

    print_as_table(table_width, n_possible_answers, awsum_table_mode);

    printf(BOLD_S"%d possible words\n"STYLE_END, n_possible_answers);

    return 0;
}

void err(int error_code)
{
    switch(error_code)
    {
	case 1:
	    printf("Missing arguments\n");
	    break;
	    
	case 5:
	    printf("Index value must be between 1 and 5 (inclusive)\n");
	    break;

	case 7:
	    printf("This feature hasn't been implemented\n");
	    break;

	case 10:
	    printf("Invalid flag\n");
	    printf("The only valid flags are:\n\n");
	    printf("-e (exclude)\n");
	    printf("-x (exclude)\n");
	    printf("--exclude (exclude)\n\n");
	    printf("-s (strict)\n");
	    printf("--strict (strict)\n");
	    printf("-i (includes)\n");
	    printf("--includes (includes)\n");
	    break;

	default:
	    printf("Missing error message\n");
	    break;
    }
    exit(error_code);
}

void print_as_table(int width, int total_elements, bool awsum_mode)
{
    if (total_elements > 0)
    {
	if (awsum_mode)
	{
	    int empty_cells = total_elements % width;
	    int total_cells = total_elements + (empty_cells == 0 ? 0 : width - empty_cells);	// ternary operator to remove garbage data
	    int column_height = total_cells / width;

	    for (int base_count = 0; base_count < column_height; base_count++)
	    {
		for (int j = 0; j < width; j++)
		{
		    int base_offset = j * column_height;
		    int index = base_count + base_offset;

		    // bounds checking (avoids printing garbage data
		    if (index < total_elements)
		    {
			printf("%s ", filtered_arr[index]);
		    }
		}
		printf("\n");
	    }
	}
	else
	{
	    for (int i = 0; i < total_elements; i++)
	    {
		
		if (i % width == 0)
		{
		    if (i != 0)
		    {
			printf("\n");
		    }
		}
		printf("%s ", filtered_arr[i]);
	    }
	    printf("\n");
	}
    }
}

void user_index_validation(int index)
{
    if (index < 0 || index > 5 )
    {
	// display error message for invalid value
	err(5);
    }
}

void verbose_printing(char *flag, char letter, int indexed_letter_value, int affected_words, bool letter_is_present)
{

    printf(BOLD_S ANSI_LCYAN"%s"STYLE_END ANSI_LCYAN" flag caused "BOLD_S "%d"STYLE_END ANSI_LCYAN" word", flag, affected_words);

    if (affected_words != 1)
    {
	printf("s");
    }

    if (letter_is_present)
    {
	printf(" with ");
    }
    else
    {
	printf(" without ");
    }

    printf(BOLD_S"%c "STYLE_END ANSI_LCYAN, letter);


    // might add colour options here
    if (indexed_letter_value != -1)
    {
	indexed_letter_value++; // in order to make it more user friendly 
				// because the user inputs a value 1-5 not 0-4
	printf("at index "BOLD_S"%d "STYLE_END ANSI_LCYAN, indexed_letter_value);
    }

    printf("to be moved to the filtered array\n"STYLE_END);
}
