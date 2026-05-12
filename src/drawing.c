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
		for (int i = 0; i < NUM_LETTERS_WORD; i++)
		{
			char filtered_words[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			char filtered_words_temp[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			int num_answers = 0;
			for (int j = 0; j < NUM_ALL_WORDS; j++)
			{
				if (wordle_answer[i] == all_words[j][i])
				{
					strcpy(filtered_words[num_answers], all_words[j]);
					num_answers++;
				}
			}
			int temp_count = 0;
			for (int j = 0; j < num_answers; j++)
			{
				strcpy(filtered_words_temp[j], filtered_words[j]);
			}
			for (int j = 0; j < num_answers; j++)
			{
				for (int k = 0; k < NUM_LETTERS_WORD; k++)
				{
					if (k != i)
					{
						if (wordle_answer[j] != all_words[j][k])
						{
							strcpy(filtered_words[temp_count], filtered_words_temp[j]);
							temp_count++;
						}
					}
				}
			}
			num_answers = temp_count;
			int user_letter_index = i + 1;
			printf(BOLD_S"\nEntry %d \n"STYLE_END, user_letter_index);

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

