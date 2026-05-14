#include "header.h"

void drawing(char wordle_answer[INDEX_LETTERS_WORD], bool x_pattern)
{
	char wordle_answer_temp[INDEX_LETTERS_WORD];
	for (int i = 0; i < NUM_LETTERS_WORD; i++)
	{
		/* convert the wordle answer to uppercase for easier parsing */
		wordle_answer_temp[i] = (char)to_uppercase(wordle_answer[i]);
	}

	wordle_answer = wordle_answer_temp;

	char all_answers[INDEX_LETTERS_WORD][NUM_ALL_WORDS][NUM_LETTERS_WORD];

	int num_all_answers[NUM_LETTERS_WORD];

	if (!x_pattern)
	{
		for (int entry_i = 0; entry_i < NUM_LETTERS_WORD; entry_i++)
		{
			char grey_letters[5];
			char green_letter;
			int green_letter_index = 0;

			for (int i = 0; i < NUM_LETTERS_WORD; i++)
			{
				if (i == entry_i)
				{
					green_letter = wordle_answer[i];
				}
				else
				{
					if (i >= 1)
					{
						bool duplicate = false;
						for (int j = 0; j < i; j++)
						{
							if (grey_letters[j] == wordle_answer[i])
							{
								duplicate = true;
							}
						}

						if (!duplicate)
						{
							grey_letters[green_letter_index] = wordle_answer[i];
							green_letter_index++;
						}
					}
					else
					{
						grey_letters[green_letter_index] = wordle_answer[i];
						green_letter_index++;
					}
				}
			}

			char filtered_words[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			char filtered_words_temp[NUM_ALL_WORDS][INDEX_LETTERS_WORD];
			int num_answers = 0;
			for (int j = 0; j < NUM_ALL_WORDS; j++)
			{
				if (green_letter == all_words[j][entry_i])
				{
					strcpy(filtered_words_temp[num_answers], all_words[j]);
					num_answers++;
				}
			}
			int temp_count = 0;
			for (int word_iteration = 0; word_iteration < num_answers; word_iteration++)
			{
				bool all_letters_are_grey = true;
				/* loop for every letter in the original word (answer) */
				for (int answer_letter_index = 0; answer_letter_index < NUM_LETTERS_WORD; answer_letter_index++)
				{
					/* if the letter in the orignal word matches the index of the temporary word to check,
					 * we have to go to the next letter */
					if (answer_letter_index != entry_i)
					{
						for (int letter_iteration = 0; letter_iteration < NUM_LETTERS_WORD; letter_iteration++)
						{
							if (green_letter != filtered_words_temp[word_iteration][letter_iteration])
							{
								for (int i = 0; i < NUM_LETTERS_WORD; i++)
								{
									if (wordle_answer[answer_letter_index] == filtered_words_temp[word_iteration][letter_iteration])
									{
										all_letters_are_grey = false;
										/* break out of the answer_letter_index loop 
										 * since a letter is matching in the word */
										break; 
									}
								}
							}
						}

						if (!all_letters_are_grey)
						{
							break;
						}
					}
				}
			
				if (all_letters_are_grey)
				{
					strcpy(filtered_words[temp_count], filtered_words_temp[word_iteration]);
					temp_count++;
				}
			}
			num_answers = temp_count;
			int user_letter_index = entry_i + 1;
			printf(BOLD_S"\nEntry %d \n"STYLE_END, user_letter_index);

			if (num_answers < 1)
			{
				printf("No matches were found\n");
			}

			for (int j = 0; j < num_answers; j++)
			{
				strcpy(all_answers[entry_i][j], filtered_words[j]);
			}
			num_all_answers[entry_i] = num_answers;
			print_as_table(table_width, num_answers, awsum_table_mode, filtered_words);
		}
	}
	else
	{
		err(7);
	}
	
	printf("\n");

	for (int entry_i = 0; entry_i < NUM_LETTERS_WORD; entry_i++)
	{
		int entry_user_num = entry_i + 1;

		printf(BOLD_S"Entry #%d"STYLE_END": "BOLD_S, entry_user_num);

		if (num_all_answers[entry_i] > 1)
		{
			printf("%d"STYLE_END, num_all_answers[entry_i]);
		}
		else
		{
			printf("no"STYLE_END);
		}
		printf(" possible words\n");
	}

	printf("Wordle answer: "BOLD_S"%s\n"STYLE_END, wordle_answer);

	for (int i = 1; i < indenting; i++)
	{
		printf("\n");
	}
	exit(0);
}
