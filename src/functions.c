#include "header.h"



char *word_list_text[NUM_WORD_LISTS] =
{
	"all french words",
	"all words",
	"common words",
	"New-York-Times words",
};

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

	int num_matches = 0;
	bool word_list_matches[NUM_WORD_LISTS];
	char *word_list_names[NUM_WORD_LISTS];

	word_list_names[nyt]	= "New-York Times word list";
	word_list_names[common]	= "the \"common words\" list";
	word_list_names[all]	= "\"all words\" list";

	word_list_names[fr_all]	= "french \"all words\" list";
	word_list_names[la_all]	= "latin \"all words\" list";

	for (int i = 0; i < NUM_WORD_LISTS; i++)
	{
		word_list_matches[i] = false;
	}

	if (command_word_string != NULL)
	{
		for (int i = 0; i < NUM_WORD_LISTS; i++)
		{
			char (*ptr)[INDEX_LETTERS_WORD];


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
		if (word_list_matches[nyt])
		{
			printf(ANSI_GREEN"New-York Times word list\n"STYLE_END);
		}
		if (word_list_matches[common])
		{
			printf(ANSI_GREEN"the \"common words\" list\n"STYLE_END);
		}

		if (word_list_matches[all])
		{
			printf(ANSI_GREEN"\"all words\" list\n"STYLE_END);
		}

		if (word_list_matches[fr_all])
		{
			if (word_list_matches[all])
			{
				printf("\n");
			}
			printf(ANSI_GREEN"french \"all words\" list\n"STYLE_END);
		}

		if (word_list_matches[la_all])
		{
			if (!word_list_matches[fr_all])
			{
				if (word_list_matches[all])
				{
					printf("\n");
				}
			}

			printf(ANSI_GREEN"latin \"all words\" list\n"STYLE_END);
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
	    	err(CMD_INDEX_BOUNDS);
	}
}

