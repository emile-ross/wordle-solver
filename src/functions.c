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

		case 20:
		    printf(BOLD_S"No possible answers.\n"STYLE_END);
		    printf(BOLD_S"Try editing your filters.\n"STYLE_END);
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

void warn(warnings warning_type)
{
	/* the message title is displayed for every valid warning */
	char *warning_message_title = "Warning!";

	bool critical = false;
	char *message = NULL;
	char *solution = NULL;

	switch (warning_type)
	{
		case draw:
			message = "the --draw option isn't fully functional yet";
			solution = "you might encounter some problems/errors with it";
			break;

		case xdraw:
			message = "the -x option isn't fully functional yet";
			solution = "you might encounter some problems/errors with it";
			break;

		default: 
			printf("Unknown warning\n");
			critical = true;
			break;
	}

	if (critical)
	{
		/* cast the enum to an int 
		 * this exits the program if the warning is a critical one */
		exit((int)warning_type);
	}

	/* use the message template including the solution if it was specified */
	if (solution != NULL)
	{
		const char *warning_message_s_template = BOLD_S ANSI_RED"%s"STYLE_END ANSI_RED" %s,\n%s"STYLE_END;

		int message_size = 1 + snprintf(NULL, 0, warning_message_s_template, warning_message_title, message, solution);

		char warning_message[(size_t)message_size];
		snprintf(warning_message, (size_t)message_size, warning_message_s_template, warning_message_title, message, solution);

		printf("%s\n", warning_message);
	}
	else
	{
		const char *warning_message_template = BOLD_S ANSI_RED"%s"STYLE_END ANSI_RED" %s"STYLE_END;

		int message_size = 1 + snprintf(NULL, 0, warning_message_template, warning_message_title, message);

		char warning_message[(size_t)message_size];
		snprintf(warning_message, (size_t)message_size, warning_message_template, warning_message_title, message);

		printf("%s\n", warning_message);
	}

	printf("Press any key to continue");

	getchar();

	printf("\n");
}
