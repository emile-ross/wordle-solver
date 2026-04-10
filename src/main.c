#include "header.h"

char filtered_arr[NUM_WORDS][6];

int n_possible_answers;

int main(int argc, char *argv[])
{
    bool first_execution = true;

    if (argc >= 2)
    {
	if (argc % FILTER_ARG_EXPECTED == 1)
	{
	    // in order to ignore the first argument of the command (probably the execution command)
	    int i = ARGS_BEFORE_FLAG;

	    while(i < argc)
	    {
		if (strcmp(argv[i], "-s") == 0)
		{
		    // this is the way this interprets characters
		    // execute(./binary) flag(-s) letter_position(5) letter(A)
		    // this means all words(in the list) ending in A
		    int letter_arg_index = i;
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
		    if (word_letter_index > 5 || word_letter_index < 0)
		    {
			err(5);
		    }

		    char letter_indexed = argv[letter_arg_index][0];

		    n_possible_answers = 0;
		    if (first_execution)
		    {
			for (int j = 0; j < NUM_WORDS; j++)
		    	{
		    	    if (letter_indexed == words[j][word_letter_index])
		    	    {
		    	        strcpy(filtered_arr[n_possible_answers], words[j]);
		    	        n_possible_answers++;
		    	    }
		    	}
		    }
		    else
		    {
			for (int k = 0; k < NUM_WORDS; k++)
		    	{
		    	    if (letter_indexed == filtered_arr[k][word_letter_index])
		    	    {
		    	        strcpy(filtered_arr[n_possible_answers], filtered_arr[k]);
		    	        n_possible_answers++;
		    	    }
		    	}
		    }

		    first_execution = false;
		}
		i += FILTER_ARG_EXPECTED;
	    }
	}
    }
    else
    {
	err(1);
    }

    print_as_table(8, n_possible_answers, false);

    printf("%d possible words\n", n_possible_answers);

    return 0;
}

void parse_command(int num_arg, char *argument[])
{
    // set the amount of filtered words but inclusively
    int inc_filtered_num = NUM_WORDS;

    int filtered_words = 0;
    for (int i = 0; i < NUM_WORDS; i++)
    {
	if ('Z' == words[i][0])
	{
	    printf("True for %d\n", i);
	    filtered_words++;
	}
    }
    printf("True for %d words\n", filtered_words);
}

void debug(int num_arg, char *argument[])
{
    if (num_arg < 2)
    {
	printf("You haven't used any argments in your command\nMoving on...\n");
    }

    for (int i = 0; i < num_arg; i++)
    {
	// print all arguments by looping through all of them
	printf("%s\n", argument[i]);
    }
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
	    printf("CC \n");
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
	    int total_cells = total_elements + width - empty_cells;
	    int column_height = total_cells / width;

	    for (int base_count = 0; base_count < column_height; base_count++)
	    {
		for (int j = 0; j < width; j++)
		{
		    int base_offset = j * column_height;
		    int index = base_count + base_offset;
		    char *word_temp = filtered_arr[index];
		    printf("%s ", word_temp);
		}
		printf("\n");
	    }
	}
	else
	{
	    printf("\n\n"); // just for clarity (will be removed later)
	    for (int i = 0; i < total_elements; i++)
	    {
		if (i % width == 0)
		{
		    printf("\n");
		}
		char *word_temp = filtered_arr[i];
		printf("%s ", word_temp);
	    }
	    printf("\n");
	}
    }
}
