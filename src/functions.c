#include "header.h"

char to_uppercase(char letter)
{
	/* if the letter is lowercase, 
	 * then, return the uppercase version */
	switch (letter)
	{
		case 'a':
			return 'A';
		case 'b':
			return 'B';
		case 'c':
			return 'C';
		case 'd':
			return 'D';
		case 'e':
			return 'E';
		case 'f':
			return 'F';
		case 'g':
			return 'G';
		case 'h':
			return 'H';
		case 'i':
			return 'I';
		case 'j':
			return 'J';
		case 'k':
			return 'K';
		case 'l':
			return 'L';
		case 'm':
			return 'M';
		case 'n':
			return 'N';
		case 'o':
			return 'O';
		case 'p':
			return 'P';
		case 'q':
			return 'Q';
		case 'r':
			return 'R';
		case 's':
			return 'S';
		case 't':
			return 'T';
		case 'u':
			return 'U';
		case 'v':
			return 'V';
		case 'w':
			return 'W';
		case 'x':
			return 'X';
		case 'y':
			return 'Y';
		case 'z':
			return 'Z';

		default:
			return letter;
	}
}

void validate_word(char command_word_string[INDEX_LETTERS_WORD])
{
	char command_word_string_temp[INDEX_LETTERS_WORD];
	for (int i = 0; i < NUM_LETTERS_WORD; i++)
	{
		command_word_string_temp[i] = to_uppercase(command_word_string[i]);
	}

	strcpy(command_word_string, command_word_string_temp);

	int list_num = -1;
	bool match = false;

	if (command_word_string != NULL)
	{
		list_num++;
		for (int i = 0; i < NUM_WORDS; i++)
		{
			if (strcmp(command_word_string, nyt_words[i]) == 0)
			{
				match = true;
				goto match;
			}
		}
		list_num++;
		for (int i = 0; i < NUM_COMMON_WORDS; i++)
		{
			if (strcmp(command_word_string, common_words[i]) == 0)
			{
				match = true;
				goto match;
			}
		}
		list_num++;
		for (int i = 0; i < NUM_ALL_WORDS; i++)
		{
			if (strcmp(command_word_string, all_words[i]) == 0)
			{
				match = true;
				goto match;
			}
		}
	}
	match:	/* goto is used to go here whenever a word has been matched in any word list */
	printf(BOLD_S"\nThe word: "UDRL_S"%s\n"STYLE_END, command_word_string);

	if (match)
	{
		printf("was found in the following lists:\n\n");
		switch (list_num)
		{
			case 0:
				printf(ANSI_GREEN"New-York Times word list\n"STYLE_END);
				__attribute__ ((fallthrough));
			case 1:
				printf(ANSI_GREEN"the \"common words\" list\n"STYLE_END);
				__attribute__ ((fallthrough));
			case 2:
				printf(ANSI_GREEN"\"all words\" list\n"STYLE_END);
				break;
			default:
				err(15);
		}
	}
	else
	{
		printf("was not found in any word list\n");
	}
	exit(0);
}

void user_index_validation(int index)
{
    if (index < 0 || index > 5 )
    {
		/* display error message for invalid value (invalid index into the word) */
		err(5);
    }
}
