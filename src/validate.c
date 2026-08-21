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
			int o = 0;
			uint32_t num_words = 0;
			char (*ptr)[INDEX_LETTERS_WORD] = list_match((ALL_WORD_LISTS)i, &num_words, true);
	
			int lb = 0;
			int ub = (int)num_words - 1;

			int mid = middle(0, (int)num_words - 1);
			int ret = strcmp(command_word_string, ptr[mid]);

			if (ret == 0)
			{
				word_list_matches[i] = true;
				word_matches = true;
			}
			else
			{
				int range = ub - lb;
				while (range > -1 && o < 1024)
				{
					if ((mid >= (int)num_words) || (mid < 0))
					{
						fprintf(stderr, "Invalid index to word (out of bounds)\n");
						fprintf(stderr, "lower bound: %d\nupper bounds: %d\nindex: %d\n", lb, ub, mid);
						exit(1);
					}

					ret = strcmp(command_word_string, ptr[mid]);
					o++;

					if (ret < 0)
					{
						ub = mid - 1;
					}
					else if (ret > 0)
					{
						lb = mid + 1;
					}
					else 
					{
						break;
					}

					mid = middle(lb, ub);
					range = ub - lb;
				}

				if (ret == 0)
				{
					word_list_matches[i] = true;
					word_matches = true;
				}

				if (o >= 1024)
				{
					fprintf(stderr, "Failed checking after %d operations\n", o);
				}
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
int middle(int64_t lb, int64_t ub)
{
	if (ub > INT32MAX)
	{
		fprintf(stderr, "%ld is outside the integer range (from %d to %d)\n", ub, (0-INT32MAX-1), INT32MAX);
	}

	int64_t dif = ub - lb;
	if (dif == 0)
	{
		return (int)lb;
	}
	else if (dif < 0)
	{
		fprintf(stderr, "Invalid bounds, lower bound \"%ld\" lb is greater than upper bound \"%ld\"\n", lb, ub);
		exit(1);
	}
	return (int)(lb + (dif / 2));
}
