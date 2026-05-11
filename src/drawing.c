#include "header.h"

void drawing(char wordle_answer[INDEX_LETTERS_WORD])
{
	char wordle_answer_temp[INDEX_LETTERS_WORD];
	for (int i = 0; i < NUM_LETTERS_WORD; i++)
	{
		wordle_answer_temp[i] = (char)to_uppercase(wordle_answer[i]);
	}
	wordle_answer = wordle_answer_temp;

	bool x_pattern = false;

	char all_answers[INDEX_LETTERS_WORD][NUM_ALL_WORDS][NUM_LETTERS_WORD];

	if (!x_pattern)
	{
		for (int i = 0; i < 5; i++)
		{
			char filtered_words[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			int num_answers = 0;
			for (int j = 0; j < NUM_ALL_WORDS; j++)
			{
				if (wordle_answer[i] == all_words[j][i])
				{
					strcpy(filtered_words[num_answers], all_words[j]);
					num_answers++;
				}
			}
			printf(BOLD_S"\nEntry %d \n"STYLE_END, i);

			if (num_answers < 1)
			{
				printf("No matches were found\n");
			}

			for (int j = 0; j < num_answers; j++)
			{
				strcpy(all_answers[i][j], filtered_words[j]);
			}
			print_as_table(table_width, num_answers, awsum_table_mode, filtered_words);
		}
	}
	
	printf("%s\n", wordle_answer);
}

