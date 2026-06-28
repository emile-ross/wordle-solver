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
	char *word_list_names[NUM_WORD_LISTS];

	word_list_names[en_nyt]		= "english New-York Times word list";
	word_list_names[en_common]		= "english the \"common words\" list";
	word_list_names[en_all]		= "english \"all words\" list";

	word_list_names[fr_all]		= "french \"all words\" list";
	word_list_names[la_common]	= "latin \"common words\" list";
	word_list_names[la_all]		= "latin \"all words\" list";

	for (int i = 0; i < NUM_WORD_LISTS; i++)
	{
		word_list_matches[i] = false;
	}

	if (command_word_string != NULL)
	{
		for (int i = 0; i < NUM_WORD_LISTS; i++)
		{
			const char (*ptr)[INDEX_LETTERS_WORD];
			int num_words = 0;
			/* TODO: make a single function to do this instead of multiple duplicate switches in parsing.c and here */

			num_words = list_match((ALL_WORD_LISTS)i, &ptr);
	
			for (int j = 0; j < num_words; j++)
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
				printf(ANSI_GREEN"%s\n"STYLE_END, word_list_names[i]);

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

