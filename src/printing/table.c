#include "../include/header.h"

void print_as_table(uint16_t width, uint64_t total_elements, bool awsum_mode, char all_answers_print[NUM_ALL_WORDS][INDEX_LETTERS_WORD])
{
	/* hide elements */
	uint64_t hidden_elements = 0;
	bool hidden_msg = false;
	if (cap_total_elements && element_cap < total_elements)
	{
		hidden_elements = total_elements - element_cap;
		total_elements = element_cap;

		if (hidden_elements > 0)
		{
			/* the hidden elements message will be displayed */
			hidden_msg = true;
		}
	}

	/* element printing */
	if (awsum_mode)
	{
		uint64_t empty_cells = total_elements % width;
		uint64_t total_cells = total_elements + (empty_cells == 0 ? 0 : width - empty_cells);	/* ternary operator to remove garbage data */
		uint64_t column_height = (total_cells / width);
		
		for (uint64_t base_count = 0; base_count < column_height; base_count++)
		{
			for (uint16_t j = 0; j < width; j++)
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

	float remaining_percent = 0.00F;

	size_t size = 24;
	char *percent = smalloc(size);

	if (n_possible_answers != 0)
	{
		remaining_percent = (float)(((double)n_possible_answers / (double)initial_words) * 100);

		if (remaining_percent < 0.25F)
		{
			safe_write(&percent, &size, "%.4f", remaining_percent);
		}
		else if (remaining_percent < 2.5F)
		{
			safe_write(&percent, &size, "%.3f", remaining_percent);
		}
		else if (remaining_percent < 25.0F)
		{
			safe_write(&percent, &size, "%.2f", remaining_percent);
		}
		else
		{
			safe_write(&percent, &size, "%.1f", remaining_percent);
		}

	}

	printf(BOLD_S"%d possible words (%s%% of initial words)\n"STYLE_END, n_possible_answers, percent);
	if (percent != NULL)
		free(percent);


	/* initial_words is initialised in src/parsing.c in the parsing() fn */
	printf("( "BOLD_S"%d / %d"STYLE_END" possible words)\n", n_possible_answers, initial_words);

	if (hidden_msg)
	{
		for (uint8_t i = 0; i < indenting; i++)
		{
			printf("\n");
		}
		printf(ANSI_GREY BOLD_S"%lu"STYLE_END ANSI_GREY " elements were hidden due to the %lu element limit\n"STYLE_END, hidden_elements, element_cap);
	}
	else
	{
		/* only indent one line if there is no hidden message */
		printf("\n");
	}
}
