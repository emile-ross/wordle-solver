#include "include/header.h"

#define init_var_value (-255)

int64_t err_buffer_size = -1;
int64_t err_buffer_write = -1;

void err(error_codes error_code)
{
	bool report_issue = false;
	bool buffer_related = false;

	char *error_message = NULL;
	switch (error_code)
    	{
	case CMD_MISSING_ARGS:
		error_message = "Missing arguments";
		break;
		
	case NEGATIVE_INDEX:
		error_message = "Index value is negative";
		/* this error message falls through and triggers CMD_INDEX_BOUNDS on purpose because both errors are heavily related */
		__attribute__((fallthrough));

	case INTEGER_BOUNDS:
		error_message = "Integer is out of bounds";
		break;

	case CMD_INDEX_BOUNDS:
		error_message = "Index value must be between 1 and 5 (inclusive)";
		break;
		
	case FEAT_NOT_IMPLEMENTED:
		error_message = "This feature hasn't been implemented";
		break;

	case NO_SUCH_FILE:
		error_message = "Failed to open file\nNo such file or directory.";
		break;
		
	case CMD_INVALID_ARG:
		error_message = "You provided an invalid argument, here is a list of all possible arguments:";
		help_message();
		break;
		
	case UNKNOWN_WORD_LIST:
		error_message = "Unknown word list";
		break;
		
	case NO_POSSIBLE_ANSWERS:
		error_message = "No possible answers.\nTry editing your filters.";
		break;

	case WORD_TOO_LONG:
		error_message = "Word is too long";
		buffer_related = true;
		break;

	case WORD_TOO_SHORT:
		error_message = "Word is too short";
		buffer_related = true;
		break;

	case FORMATTING_ERROR:
		error_message = "Formatting error\nThe string provided doesn't fit within the bounds";
		buffer_related = true;
		report_issue = true;
		break;

	case MALLOC_FAIL:
		fprintf(stderr, "Failed to allocate memory\nThe call to malloc() failed and returned NULL");
		exit(1);

	case FILENAME_FAIL:
		error_message = "Failed to get the filename for the word list";
		break;

	case FILEPATH_FAIL:
		error_message =
			"Failed to get the full filepath to the word list file\nReport this bug, use a custom word list in the meantime";
		report_issue = true;
		break;

	case INPUT_FAIL:
		error_message = "Failed to parse input from stdin";
		break;

	case INVALID_WORD:
		/* User is at fault */
		error_message = "The word provided is invalid";
		break;
	
	case INVALID_LETTER:
		/* User is at fault */
		error_message = "The letter you provided isn't valid (it isn't composed of letters)";
		break;

	case INVALID_INDEX:
		/* User is at fault */
		error_message = "The index into the word is invalid";
		break;

	case VERBOSE_FAIL:
		error_message = "Failed to write the verbose message\n";
		report_issue = true;
		break;

	case BUFFER_WRITE_FAIL:
		error_message = "Buffer write failed\nThe string provided doesn't fit within the bounds, snprintf() made an invalid call to it";
		report_issue = true;
		/* buffer_related = true;
		 * make sure the variable is initialised before un commenting this line */
		break;

	case ZERO_SIZED_BUF:
		error_message = "A zero-sized buffer can't be written into (zero-sized buffer)\n";
		report_issue = true;
		buffer_related = true;
		break;

	case INVALID_CONFIG:
		error_message = "Fix the errors in the src/config.c file\n";
		break;

	case UNDEFINED_LIST:
		error_message = "The word list was never defined\n";
		report_issue = true;
		break;

	case NO_WORD_LIST:
		error_message = "The word list is not a word list (no_word_list)\n";
		report_issue = true;
		break;
	
	default:
		printf("Missing error message\n");
		break;
    	}

	if (buffer_related)
	{
		if ((err_buffer_write != init_var_value) && (err_buffer_size != init_var_value))
		{
			fprintf(stderr, "Writing %ld bytes into a buffer of size %ld", err_buffer_write, err_buffer_size);
		}
	}

	if (error_message)
	{
		char *message_template = "%s: %s";

		/* calculate string length */
		int message_size = 1 + snprintf(NULL, 0, message_template, program_name, error_message);
		char *full_error_message = malloc((size_t)message_size);	/* allocate memory for the base error message string */
		if (full_error_message == NULL)
		{
			/* do not call err(MALLOC_FAIL); in order to avoid recursion and a possible stack overflow */
			fprintf(stderr, "Failed to allocate memory\nThe call to malloc() failed and returned NULL");
			exit(1);
		}

		/* write to error_msg_base buffer */
		int ret = snprintf(full_error_message, (size_t)message_size, message_template, program_name, error_message);
		check_buf(ret, message_size, (void*)full_error_message);	/* check buffer for possible truncation  */

		printf(ANSI_RED"%s"STYLE_END, full_error_message);

		free(full_error_message);
	}

	if (report_issue)
	{
		fprintf(stderr, "Report this issue at: https://github.com/emile-ross/wordle/issues\n");
		fprintf(stderr, "Create an issue, provide your full log, file hierarchy and valgrind log if needed\n");
	}

	for (int i = 0; i < indenting; i++)
    	{
    	        printf("\n");
    	}

	exit((int)error_code);
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
			fprintf(stderr, "Unknown warning\n");
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

		int message_size = 1 + snprintf(NULL, 0, warning_message_template, warning_message_title, message);

		char *warning_message = malloc((size_t)message_size);
		int ret = snprintf(warning_message, (size_t)message_size, warning_message_template, warning_message_title, message);
		check_buf(ret, message_size, (void*)warning_message);	/* check buffer for possible truncation  */

		fprintf(stderr, "%s\n", warning_message);
		free(warning_message);
	}
	else
	{
		const char *warning_message_s_template = BOLD_S ANSI_RED"%s"STYLE_END ANSI_RED" %s,\n%s"STYLE_END;

		int message_size = 1 + snprintf(NULL, 0, warning_message_s_template, warning_message_title, message, solution);

		char *warning_message = malloc((size_t)message_size);
		int ret = snprintf(warning_message, (size_t)message_size, warning_message_s_template, warning_message_title, message, solution);
		check_buf(ret, message_size, (void*)warning_message);	/* check buffer for possible truncation  */

		fprintf(stderr, "%s\n", warning_message);
		free(warning_message);
	}

	printf("Press any key to continue");
	getchar();

	for (int i = 0; i < indenting; i++)
	{
		printf("\n");
	}
}

void help_message(void)
{
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
	printf(STYLE_END);
}
