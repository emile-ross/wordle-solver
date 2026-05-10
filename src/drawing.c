#include "header.h"

void drawing(char wordle_answer[INDEX_LETTERS_WORD])
{
	char wordle_answer_temp[INDEX_LETTERS_WORD];
	for (int i = 0; i < NUM_LETTERS_WORD; i++)
	{
		wordle_answer_temp[i] = (char)to_uppercase(wordle_answer[i]);
	}
	wordle_answer = wordle_answer_temp;

	bool x_pattern false;

	char all_answers[5][ALLWORDS];
	if (!x_pattern)
	{
		for (int i = 0; i < 5; i++)
		{
			char filtered_temp_arr[NUM_ALL_WORDS];
			for (int j = 0; i < NUM_ALL_WORDS; i++)
			{
				if ()
				{
				}
			}
		}
	}
	
	printf("%s\n", wordle_answer);
}

