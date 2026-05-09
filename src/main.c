#include "header.h"

char filtered_arr[NUM_ALL_WORDS][INDEX_LETTERS_WORD];

int n_possible_answers;
enum ALL_WORD_LISTS word_list;

int main(int argc, char *argv[])
{
	bool find_match_mode = true; /* true by default
	 * true: finds all possible words matching all criterias
	 * false: tries to make a pattern with the letter colour */

    if (argc >= 2)  /* or else there's nothing */
    {
		int flag_r = ARGS_BEFORE_FLAG_BASE;
		command_parsing(argc, flag_r, argv, &find_match_mode);
    }
    else
    {
		err(1);
    }

	if (find_match_mode)
	{
		print_as_table(table_width, n_possible_answers, awsum_table_mode);
	}

	/* print the number of possible words 
	 * this is obtained by the last function going through the entire word list
	 * in order to check if the word is matching */
    printf(BOLD_S"%d possible words\n"STYLE_END, n_possible_answers);

    return 0;
}

void err(int error_code)
{
    switch (error_code)
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
		    printf("The only valid flags are:\n\n");
		    printf(BOLD_S" -e"STYLE_END" (exclude)\n");
		    printf(BOLD_S" -x"STYLE_END" (exclude)\n");
		    printf(BOLD_S"   --exclude"STYLE_END" (the letter \'X\' isn't at position Y)\n");
		    printf(BOLD_S" -s"STYLE_END" (strict)\n");
		    printf(BOLD_S"   --strict"STYLE_END" (the letter \'X\' is at position Y)\n\n");
		    printf(BOLD_S" -a"STYLE_END" (letter is absent)\n");
		    printf(BOLD_S"   --absent"STYLE_END" (the letter \'X\' isn't in the word)\n");
		    printf(BOLD_S" -i"STYLE_END" (includes)\n");
		    printf(BOLD_S"   --includes"STYLE_END" (the letter \'X\' is in the word)\n\n");
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
		    int total_cells = total_elements + (empty_cells == 0 ? 0 : width - empty_cells);	/* ternary operator to remove garbage data */
		    int column_height = total_cells / width;

		    for (int base_count = 0; base_count < column_height; base_count++)
		    {
				for (int j = 0; j < width; j++)
				{
				    int base_offset = j * column_height;
				    int index = base_count + base_offset;

				    /* bounds checking (avoids printing garbage data */
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
		/* display error message for invalid value (invalid index into the word) */
		err(5);
    }
}

void verbose_printing(char *flag, char letter, int indexed_letter_value, int affected_words, bool letter_is_present)
{

    printf(BOLD_S ANSI_LCYAN"%s"STYLE_END ANSI_LCYAN" flag caused "BOLD_S "%d"STYLE_END ANSI_LCYAN" word", flag, affected_words);

	/* craft sentence with appropriate words
	 * make sure it is grammatically correct (plural and negative statements) */

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


    /* ~~might add colour options here~~*/
    /* colour options were added */

    if (indexed_letter_value != -1)
    {
		indexed_letter_value++; /* in order to make it more user friendly 
								   because the user inputs a value 1-5 not 0-4 */
		printf("at index "BOLD_S"%d "STYLE_END ANSI_LCYAN, indexed_letter_value);
    }

    printf("to be moved to the filtered array\n"STYLE_END);
}

char to_uppercase(char letter)
{
	switch (letter)
	{
		case 'a':
			return 'A';
		case 'b':
			return 'B';
		case 'c':
			return 'C';
		case 'd':
			return 'D';
		case 'e':
			return 'E';
		case 'f':
			return 'F';
		case 'g':
			return 'G';
		case 'h':
			return 'H';
		case 'i':
			return 'I';
		case 'j':
			return 'J';
		case 'k':
			return 'K';
		case 'l':
			return 'L';
		case 'm':
			return 'M';
		case 'n':
			return 'N';
		case 'o':
			return 'O';
		case 'p':
			return 'P';
		case 'q':
			return 'Q';
		case 'r':
			return 'R';
		case 's':
			return 'S';
		case 't':
			return 'T';
		case 'u':
			return 'U';
		case 'v':
			return 'V';
		case 'w':
			return 'W';
		case 'x':
			return 'X';
		case 'y':
			return 'Y';
		case 'z':
			return 'Z';

		default:
			return letter;
	}
}

