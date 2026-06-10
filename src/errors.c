#include "header.h"

void err(error_codes error_code)
{
	error_message_init();
	bool critical = true;

	switch (error_code)
    	{
	case 1:
		printf("Missing arguments");
		break;
		
	case 5:
		printf("Index value must be between 1 and 5 (inclusive)");
		break;
		
	case 7:
		printf("This feature hasn't been implemented");
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
		printf(BOLD_S"   --includes"STYLE_END" (the letter \'X\' is in the word)");
		break;
		
	case 15:
		printf("Unknown word list");
		break;
		
	case 20:
		printf(BOLD_S"No possible answers.\n"STYLE_END);
		printf(BOLD_S"Try editing your filters."STYLE_END);
		break;

	case 21:
		printf("Word is too long");
		break;
	case 22:
		printf("Word is too short");
		break;
	
	default:
		printf("Missing error message\n");
		critical = false;
		break;
    	}

	for (int i = 0; i < indenting; i++)
    	{
    	        printf("\n");
    	}

	if (critical)
	{
		exit((int)error_code);
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
			err((error_codes)warning_type);
			break;
	}

	if (critical)
	{
		/* cast the enum to an int 
		 * this exits the program if the warning is a critical one */
		exit((int)warning_type);
	}

	/* use the message template including the solution if it was specified */
	if (solution == NULL)
	{
		const char *warning_message_template = BOLD_S ANSI_RED"%s"STYLE_END ANSI_RED" %s"STYLE_END;

		size_t message_size = 1 + (size_t)snprintf(NULL, 0, warning_message_template, warning_message_title, message);

		char warning_message[message_size];
		snprintf(warning_message, message_size, warning_message_template, warning_message_title, message);

		printf("%s\n", warning_message);
	}
	else
	{
		const char *warning_message_s_template = BOLD_S ANSI_RED"%s"STYLE_END ANSI_RED" %s,\n%s"STYLE_END;

		size_t message_size = 1 + (size_t)snprintf(NULL, 0, warning_message_s_template, warning_message_title, message, solution);

		char warning_message[message_size];
		snprintf(warning_message, message_size, warning_message_s_template, warning_message_title, message, solution);

		printf("%s\n", warning_message);
	}

	printf("Press any key to continue");

	getchar();

	for (int i = 0; i < indenting; i++)
	{
		printf("\n");
	}
}
