#include "header.h"

#include <ctype.h>

void validate_word(char *command_word_string)
{
	for (size_t i = 1; i < sizeof(command_word_string); i++) 
	{
		command_word_string[i] = (char)toupper((unsigned char)command_word_string[i]);
	}

	int num_matches = 0;
	bool word_list_matches[NUM_WORD_LISTS];

	for (int i = 0; i < NUM_WORD_LISTS; i++)
	{
		word_list_matches[i] = false;
	}

	if (command_word_string != NULL)
	{
		for (int i = 0; i < NUM_WORD_LISTS; i++)
		{
			uint32_t num_words = 0;
			char (*ptr)[INDEX_LETTERS_WORD] = list_match((ALL_WORD_LISTS)i, &num_words, true);
	
			for (uint32_t j = 0; j < num_words; j++)
			{
				if (strcmp(command_word_string, ptr[j]) == 0)
				{
					word_list_matches[i] = true;
					num_matches++;
					break;
				}
			}
		}
	}

	printf(BOLD_S"\nThe word: "UDRL_S"%s\n"STYLE_END, command_word_string);

	if (num_matches > 0)
	{
		printf("was found in the following lists:\n\n");

		/* print matching word lists */
		for (int i = 0; i < NUM_WORD_LISTS; i++)
		{
			if (word_list_matches[i])
			{
				printf(ANSI_GREEN"%s\n"STYLE_END, word_list_name(i));

				if (i == fr_all)
				{
					int next = i + 1;
					if (word_list_matches[next] || word_list_matches[next+1])
						printf("\n");
				}
			}
		}

	}
	else
	{
		printf("was not found in any word list\n");
	}
	exit(0);
}

