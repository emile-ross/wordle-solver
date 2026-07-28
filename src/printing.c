#include "header.h"

void print_as_table(uint8_t width, uint64_t total_elements, bool awsum_mode, char all_answers_print[NUM_ALL_WORDS][INDEX_LETTERS_WORD])
{
	/* hide elements */
	uint64_t hidden_elements = 0;
	bool hidden_msg = false;
	if (cap_total_elements)
	{
		if (element_cap < total_elements)
		{
			hidden_elements = total_elements - element_cap;
			total_elements = element_cap;

			if (hidden_elements > 0)
			{
				/* the hidden elements message will be displayed */
				hidden_msg = true;
			}
		}
	}

	/* element printing */
	if (total_elements > 0)
	{
	    	if (awsum_mode)
	    	{
			uint64_t empty_cells = total_elements % width;
	    		uint64_t total_cells = total_elements + (empty_cells == 0 ? 0 : width - empty_cells);	/* ternary operator to remove garbage data */
	    		uint64_t column_height = (total_cells / width);
	
	    		for (uint64_t base_count = 0; base_count < column_height; base_count++)
	    		{
	    		    	for (int j = 0; j < width; j++)
	    		    	{
			    		uint64_t base_offset = j * column_height;
			    		uint64_t index = base_count + base_offset;
	
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
			for (uint64_t i = 0; i < total_elements; i++)
			{
			    	if (i % width == 0)
				{
					/* add newline when the width is reached */
					if (i != 0)
					{
						printf("\n");
					}
				}
			    	printf("%s ", all_answers_print[i]);
			}

			/* decrease the indenting by one */
			uint64_t temp_indenting = indenting;
			if (indenting >= 2)
			{
				temp_indenting--;
			}

			/* add newline when the whole list is done printing */
			for (uint8_t i = 0; i < temp_indenting; i++)
			{
				printf("\n");
			}
	    	}


		/* print the number of possible words 
		 * this is obtained by the last function going through the entire word list
		 * in order to check if the word is matching */
		printf(BOLD_S"%d possible words"STYLE_END, n_possible_answers);

		if (hidden_msg)
		{
			for (uint8_t i = 0; i < indenting; i++)
			{
				printf("\n");
			}
			printf(ANSI_GREY BOLD_S"%d"STYLE_END ANSI_GREY " elements were hidden due to the %lu element limit\n"STYLE_END, hidden_elements, element_cap);
		}
		else
		{
			/* only indent one line if there is no hidden message */
			printf("\n");
		}

	}
}

void verbose_printing(char *flag, char letter, int indexed_letter_value, int affected_words, bool letter_is_present)
{
	/* add colour to options */
	verbose_print(BOLD_S"%s", flag);
	verbose_print(" flag caused ");
	verbose_print(UDRL_S BOLD_S"%d", affected_words);
	verbose_print(" word");

	/* craft sentence with appropriate words
	 * make sure it is grammatically correct (plural and negative statements) */

	if (affected_words != 1)
    	{
		verbose_print("s");
    	}

    	if (letter_is_present)
    	    	verbose_print(" with ");
    	else
    	    	verbose_print(" without ");

    	verbose_print(UDRL_S BOLD_S"%c"STYLE_END" ", letter);

	/* add colour to options */
    	if (indexed_letter_value != -1)
    	{
		/* in order to make it more user friendly because the user inputs a value 1-5 not 0-4 */
    	    	indexed_letter_value++; 
    	    	verbose_print("at index "UDRL_S BOLD_S"%d", indexed_letter_value);
    	}

	verbose_print(" to be moved to the filtered array");

	/* decrease the indenting by one */
	int temp_indenting = indenting;
	if (indenting >= 2)
	{
		temp_indenting--;
	}

	for (int i = 0; i < temp_indenting; i++)
	{
		printf("\n");
	}
}
