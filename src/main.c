#include "header.h"

char filtered_arr[NUM_WORDS][6];

int n_possible_answers;

int main(int argc, char *argv[])
{
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
		    printf("Integer value: %d\n", word_letter_index);
		    word_letter_index--;
		    if (word_letter_index > 5 || word_letter_index < 0)
		    {
			err(5);
		    }

		    char letter_indexed = argv[letter_arg_index][0];

		    n_possible_answers = 0;
		    for (int j = 0; j < NUM_WORDS; j++)
		    {
			if (letter_indexed == words[j][word_letter_index])
			{
			    printf("True for %d\n", j);
			    strcpy(filtered_arr[n_possible_answers], words[j]);
			    n_possible_answers++;
			}
		    }
		    printf("Possible words:\n");
		    printf("%d\n", n_possible_answers);

		    for (int j = 0; j < n_possible_answers; j++)
		    {
			char *word_temp = filtered_arr[j];
			printf("%s\n", word_temp);

			//printf("%s", words;
		    }
		}

		i += FILTER_ARG_EXPECTED;
	    }
	}
    }
    else
    {
	//err(1);
    }

    //parse_command(argc, argv);

    print_as_table(5, n_possible_answers, false);

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
	    err(7); // not getting past that

	    int n_last_row = total_elements % width;
    	    int n_items_full_row = total_elements - n_last_row; // the amount of items in all full row(s)
    	    int size_column = n_items_full_row / width;
    	    printf("%d\n", n_last_row);
    	    printf("%d\n", n_items_full_row);
    	    printf("%d\n", size_column);
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
