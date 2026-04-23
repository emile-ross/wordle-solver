#include "header.h"

char filtered_arr[NUM_ALL_WORDS][INDEX_LETTERS_WORD];


int n_possible_answers;
enum ALL_WORD_LISTS word_list;
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
	        if (!first_execution)	// print error message if -w comes after words have been filtered
		{
		    if (!ignore_warn)
		    {
			err(16);
		    }
		}

		if (argc >= 3)
		{
		    int wlist_indx_t = flag_r + 1;  // read 1 argument ahead of the "flag_r" integer

		    if (strcmp(argv[wlist_indx_t], "common") == 0 || strcmp(argv[wlist_indx_t], "common-words") == 0)
		    {
			word_list = common;
			if (verbose)
			{
			    printf(ANSI_LCYAN"using "BOLD_S"common"STYLE_END ANSI_LCYAN" word list\n"STYLE_END);
			}
		    }
		    else if (strcmp(argv[wlist_indx_t], "all") == 0 || strcmp(argv[wlist_indx_t], "all-words") == 0)
		    {
			word_list = all;
			if (verbose)
			{
			    printf(ANSI_LCYAN"using "BOLD_S"all"STYLE_END ANSI_LCYAN" word list\n"STYLE_END);
			}
		    }
		    else if (strcmp(argv[wlist_indx_t], "nyt") == 0 || strcmp(argv[wlist_indx_t], "NYT") == 0 || strcmp(argv[wlist_indx_t], "times") == 0)
		    {
			word_list = nyt;
			if (verbose)
			{
			    printf(ANSI_LCYAN"using the "BOLD_S"New-York-Times"STYLE_END ANSI_LCYAN" word list\n"STYLE_END);
			}
		    }
		    else
		    {
			err(15);
		    }
		    
		    if (verbose)
		    {
			printf(ANSI_LCYAN"using the "BOLD_S"%s"STYLE_END ANSI_LCYAN" word list\n"STYLE_END, word_list_text[word_list]);
		    }
		    
		}
		else // missing arguments
		{
		    err(1); 
		}


		// this sets the word list as the common word list (5700 words)
	        flag_r += WORD_LIST_ARG_EXP;
	    }
	    else if (strcmp(argv[flag_r], "--strict") == 0 || strcmp(argv[flag_r], "-s") == 0)
	    {
		parsing(&flag_r, word_list, &first_execution, true, true, argv);
	    }
	    else if (strcmp(argv[flag_r], "--exclude") == 0 || strcmp(argv[flag_r], "-x") == 0 || strcmp(argv[flag_r], "-e") == 0)
	    {
		parsing(&flag_r, word_list, &first_execution, false, true, argv);
	    }
	    else if (strcmp(argv[flag_r], "--includes") == 0 || strcmp(argv[flag_r], "-i") == 0)
	    {
		parsing(&flag_r, word_list, &first_execution, true, false, argv);
	    }
	    else if (strcmp(argv[flag_r], "--absent") == 0 || strcmp(argv[flag_r], "-a") == 0 || strcmp(argv[flag_r], "-d") == 0)
	    {
		parsing(&flag_r, word_list, &first_execution, false, false, argv);
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

	case 15:
	    printf("Unknown word list\n");
	    break;

	case 16:
	    printf("The \"-w\" or \"--word-list\" flags must be the first flag\n");
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
