#include "header.h"

void print_as_table(int width, int total_elements, bool awsum_mode, char all_answers_print[NUM_ALL_WORDS][INDEX_LETTERS_WORD])
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
						printf("%s ", all_answers_print[index]);
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
				printf("%s ", all_answers_print[i]);
		    }
		    printf("\n");
		}
    }
}

void verbose_printing(char *flag, char letter, int indexed_letter_value, int affected_words, bool letter_is_present)
{
	/* add colour to options */
    printf(BOLD_S ANSI_LCYAN"%s"STYLE_END ANSI_LCYAN" flag caused "UDRL_S BOLD_S "%d"STYLE_END ANSI_LCYAN" word", flag, affected_words);

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

    printf(UDRL_S BOLD_S"%c"STYLE_END" "ANSI_LCYAN, letter);

	/* add colour to options */
    if (indexed_letter_value != -1)
    {
		indexed_letter_value++; /* in order to make it more user friendly 
								   because the user inputs a value 1-5 not 0-4 */
		printf("at index "UDRL_S BOLD_S"%d"STYLE_END" "ANSI_LCYAN, indexed_letter_value);
    }

    printf("to be moved to the filtered array\n"STYLE_END);
}
