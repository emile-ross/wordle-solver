#include "header.h"

void drawing(char wordle_answer[INDEX_LETTERS_WORD])
{
	char wordle_answer_temp[INDEX_LETTERS_WORD];
	for (int i = 0; i < NUM_LETTERS_WORD; i++)
	{
		wordle_answer_temp[i] = (char)to_uppercase(wordle_answer[i]);
	}
	wordle_answer = wordle_answer_temp;

	printf("%s\n", wordle_answer);
}

