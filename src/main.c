#include "header.h"

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

		    for (int j = 0; j < NUM_WORDS; j++)
		    {
			int n_possible_answers = 0;
			if (letter_indexed == words[j][word_letter_index])
			{
			    printf("True for %d\n", j);
			    n_possible_answers++;
			}
		    }
		    printf("Possible words:\n");

		    for (int j = 0; j < n_possible_answers; j++)
		    {
			char *possible_answer = words[word_letter_index];
			//printf("%s", words;
		    }
		    // printf("Hi\n");

		    //printf("Hi %d\n", argc);
		    //printf("Hi %d\n", i);
		    //printf("Hi %d\n", letter_arg_index);
		}

		i += FILTER_ARG_EXPECTED;
	    }
	}
    }
    else
    {
	err(1);
    }
    //parse_command(argc, argv);
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

void test(int num_arg)
{
    printf("You entered %d command line argument", num_arg);
    if (num_arg >= 2)
    {
	printf("s");
    }

    printf("\n");
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
	default:
	    printf("Missing error message\n");
	    break;
    }
    exit(error_code);
}
