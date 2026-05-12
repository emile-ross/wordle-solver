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

void err(int error_code)
{
	bool critical = true;
    switch (error_code)
    {
		case 1:
		    printf("Missing arguments\n");
		    break;
		    
		case 5:
		    printf("Index value must be between 1 and 5 (inclusive)\n");
		    break;

		case 7:
		    printf("This feature hasn't been implemented\n");
		    break;

		case 10:
		    printf("The only valid flags are:\n\n");
		    printf(BOLD_S" -e"STYLE_END" (exclude)\n");
		    printf(BOLD_S" -x"STYLE_END" (exclude)\n");
		    printf(BOLD_S"   --excludes"STYLE_END" (the letter \'X\' isn't at position Y)\n");
		    printf(BOLD_S" -s"STYLE_END" (strict)\n");
		    printf(BOLD_S"   --strict"STYLE_END" (the letter \'X\' is at position Y)\n\n");
		    printf(BOLD_S" -a"STYLE_END" (letter is absent)\n");
		    printf(BOLD_S"   --absent"STYLE_END" (the letter \'X\' isn't in the word)\n");
		    printf(BOLD_S" -i"STYLE_END" (includes)\n");
		    printf(BOLD_S"   --includes"STYLE_END" (the letter \'X\' is in the word)\n\n");
		    break;

		case 15:
		    printf("Unknown word list\n");
		    break;

		default:
		    printf("Missing error message\n");
			critical = false;
		    break;
    }
	if (critical)
	{
		exit(error_code);
	}
}
