#include "include/header.h"

void validate_word(char *command_word_string)
{
	bool word_matches = false;
	bool word_list_matches[NUM_WORD_LISTS + 1];

	for (int i = 0; i < NUM_WORD_LISTS; i++)
	{
		word_list_matches[i] = false;
	}

	if (command_word_string != NULL)
	{
		for (int i = en_nyt; i != custom_list; i++)
		{
			uint32_t num_words = 0;
			char (*ptr)[INDEX_LETTERS_WORD] = list_match((ALL_WORD_LISTS)i, &num_words, true);
	
			int mid = middle(0, (int)num_words - 1);
			int ret = strcmp(command_word_string, ptr[mid]);

			if (ret == 0)
			{
				word_list_matches[i] = true;
				word_matches = true;
			}
			else
			{
			}
			free(ptr);
		}
	}
	else
	{
		/* word is NULL therefore it can't be used */
		err(INVALID_WORD);
	}

	printf(BOLD_S"\nThe word: "UDRL_S"%s\n"STYLE_END, command_word_string);

	if (word_matches)
	{
		printf("was found in the following lists:\n\n");

		/* print matching word lists */
		for (uint16_t i = 0; i < NUM_WORD_LISTS; i++)
		{
			if (word_list_matches[i])
			{
				printf(ANSI_GREEN"%s\n"STYLE_END, word_list_name((ALL_WORD_LISTS)i, NULL));

				if (i == fr_all)
				{
					uint16_t next = i + 1;
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
}

/* TODO take in int64_t and add error checking for possibly invalid values */
int middle(int lb, int ub)
{
	int dif = ub - lb;
	if (dif == 0)
	{
		return 0;
	}
	else if (dif < 0)
	{
		fprintf(stderr, "Invalid bounds, lower bound \"%d\" lb is greater than upper bound \"%d\"\n", lb, ub);
		exit(1);
	}
	return (dif / 2);
}
