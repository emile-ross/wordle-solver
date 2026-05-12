#include "header.h"

void drawing(char wordle_answer[INDEX_LETTERS_WORD], bool x_pattern)
{
	char wordle_answer_temp[INDEX_LETTERS_WORD];
	for (int i = 0; i < NUM_LETTERS_WORD; i++)
	{
		wordle_answer_temp[i] = (char)to_uppercase(wordle_answer[i]);
	}
	wordle_answer = wordle_answer_temp;

	char all_answers[INDEX_LETTERS_WORD][NUM_ALL_WORDS][NUM_LETTERS_WORD];

	if (!x_pattern)
	{
		for (int letter_index = 0; letter_index < NUM_LETTERS_WORD; letter_index++)
		{
			char filtered_words[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			char filtered_words_temp[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			int num_answers = 0;
			for (int j = 0; j < NUM_ALL_WORDS; j++)
			{
				if (wordle_answer[letter_index] == all_words[j][letter_index])
				{
					strcpy(filtered_words[num_answers], all_words[j]);
					num_answers++;
				}
			}
			int temp_count = 0;
			for (int i = 0; i < num_answers; i++)
			{
				strcpy(filtered_words_temp[i], filtered_words[i]);
			}
			for (int word_iteration = 0; word_iteration < num_answers; word_iteration++)
			{
				bool letter_matches = false;
				/* loop for every letter in the original word (answer) */
				for (int answer_letter_index = 0; answer_letter_index < NUM_LETTERS_WORD; answer_letter_index++)
				{
					/* if the letter in the orignal word matches the index of the temporary word to check,
					 * we have to go to the next letter */
					if (answer_letter_index != letter_index)
					{
						char original_letter = wordle_answer[answer_letter_index];
						for (int letter_iteration = 0; letter_iteration < NUM_LETTERS_WORD; letter_iteration++)
						{
							if (original_letter == all_words[word_iteration][letter_iteration])
							{
								letter_matches = true;
								/* break out of the answer_letter_index loop 
								 * since a letter is matching in the word */
								break; 
							}
						}
					}
				}
			
				if (!letter_matches)
				{
					strcpy(filtered_words[temp_count], filtered_words_temp[word_iteration]);
					temp_count++;
				}
			}
			num_answers = temp_count;
			int user_letter_index = letter_index + 1;
			printf(BOLD_S"\nEntry %d \n"STYLE_END, user_letter_index);

			if (num_answers < 1)
			{
				printf("No matches were found\n");
			}

			for (int j = 0; j < num_answers; j++)
			{
				strcpy(all_answers[letter_index][j], filtered_words[j]);
			}
			print_as_table(table_width, num_answers, awsum_table_mode, filtered_words);
		}
	}
	else
	{
		err(7);
	}
	
	printf("%s\n", wordle_answer);
}

