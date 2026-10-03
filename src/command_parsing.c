#include "include/header.h"

#include <ctype.h>

bool valid_expression;
bool append_flag_ignore_msg;

void command_parsing(int num_args, int arg_r, const char *arguments[], bool *find_match_mode)
{
	bool first_execution = true;

	if (num_args < 2)
	{
		err(CMD_MISSING_ARGS);
	}

	installed_package = check_for_pkg(arguments[0]);

	/* set the default word list as the nyt word list */
	word_list = default_word_list;
	bool word_list_is_specified = false;

	uint8_t n_valid_args = 0;
	int valid_args_index[max_valid_args];
	append_flag_ignore_msg = false;	/* if a "ignored flag" message should appear at the end */

	for (uint8_t i = 0; i < num_args; i++)
	{
		/* compare argument against word list (-w flag) */
		if (cmp(arguments[i], word_list_long_flag, word_list_flag))
		{
			valid_args_index[n_valid_args] = i;
			n_valid_args++;

			bool valid_word_list = true;
			if (!first_execution)	/* print error message if -w comes after words have been filtered */
			{
				valid_word_list = false;
				if (!ignore_warn)
				{
					err(UNKNOWN_WORD_LIST);
				}
			}

			int next_index = i + 1;
		
			if (num_args > next_index)
			{
				if (cmp(arguments[next_index], "common", "common-words"))
				{
					word_list = en_common;
				}
				else if (cmp(arguments[next_index], "all", "all-words"))
				{
					word_list = en_all;
				}
				else if (cmp(arguments[next_index], "fr", "french"))
				{
					word_list = fr_all;
				}
				else if (cmp(arguments[next_index], "la-com", "latin-common"))
				{
					word_list = la_common;
				}
				else if (cmp(arguments[next_index], "la", "latin"))
				{
					word_list = la_all;
				}
				else if (cmp(arguments[next_index], "nyt", "NYT") || scmp(arguments[next_index], "times"))
				{
					word_list = en_nyt;
				}
				else if (scmp(arguments[next_index], "custom"))
				{
					word_list = custom_list;
				}
				else
				{
					valid_word_list = false;
					err(UNKNOWN_WORD_LIST);
					exit(1);
				}

				if (verbose)
				{
					verbose_print("using the "BOLD_S"%s"STYLE_END ANSI_LCYAN" word list\n", word_list_name(word_list, NULL));
				}
			}
			else /* missing arguments */
			{
				valid_word_list = false;
				err(CMD_MISSING_ARGS); 
			}

			if (valid_word_list)
			{
				valid_args_index[n_valid_args] = next_index;
				n_valid_args++;
				word_list_is_specified = true;
				/* break out of the flag checking loop 
				 * because a valid word list argument was provided 
				 * Valid word list argument: (-w all or something like that) */
			}
		}
		else if (cmp(arguments[i], "-v", "--validate"))
		{
			*(find_match_mode) = false; /* We aren't matching words */
			valid_args_index[n_valid_args] = i;
			n_valid_args++;
		}
		else if (cmp(arguments[i], "--release", "--version"))
		{
			printf("Current version : %s\n", VERSION);

			if (scmp(arguments[0], "wordle-solver"))
			{
				printf("wordle-solver-git package for Arch Linux (via AUR)\n");
			}
			/* done after printing */
			exit(0);
		}
	}

	if (*(find_match_mode))
	{
		int index = 0;

		struct prs_args parsing_arguments = 
		{
			&arg_r,
			word_list,
			num_args,
			&first_execution,
			'\0',
			index
		};


		while (arg_r < num_args)
		{
			if (cmp(arguments[arg_r], "--strict", "-s"))
			{
				char *letter_str = get_letters(arguments, arg_r, strict, &index);
				int i = 0;

				do
				{
					parsing_arguments.letter_indexed = letter_str[i];
					parsing(parsing_arguments, strict);
					i++;
				} while (letter_str[i] != '\0');
			}
			else if (cmp(arguments[arg_r], "--excludes", "-x") || scmp(arguments[arg_r], "-e"))
			{
				char *letter_str = get_letters(arguments, arg_r, exclude, &index);
				int i = 0;
				do
				{
					parsing_arguments.letter_indexed = letter_str[i];

					parsing(parsing_arguments, exclude);
					i++;
				} while (letter_str[i] != '\0');
			}
			else if (cmp(arguments[arg_r], "--includes", "-i"))
			{
				char *letter_str = get_letters(arguments, arg_r, include, &index);
				int i = 0;
				do
				{
					parsing_arguments.letter_indexed = letter_str[i];

					parsing(parsing_arguments, include);
					i++;
				} while (letter_str[i] != '\0');
			}
			else if (cmp(arguments[arg_r], "--absent", "-a"))
			{
				char *letter_str = get_letters(arguments, arg_r, absent, &index);
				int i = 0;
				do
				{
					parsing_arguments.letter_indexed = letter_str[i];

					parsing(parsing_arguments, absent);
					i++;
				} while (letter_str[i] != '\0');
			}
			else
			{
				if (word_list_is_specified)
				{
					if (cmp(arguments[arg_r], word_list_long_flag, word_list_flag))
					{
						arg_r += WORD_LIST_ARG_EXP;
					}
				}
				else 
				{
					/* can be improved */
					invalid_flag(num_args, arg_r, arguments);
					break;
				}
			}
			valid_expression = true;
		}
	}
	else
	{
		int min_args = 3;
		if (word_list_is_specified)
		{
			min_args += 2;
		}

		if (num_args < min_args)
		{
			err(CMD_MISSING_ARGS);
		}

		/* match arguments */
		char *command_word_string = smalloc(INDEX_LETTERS_WORD);

		for (int flag_temp = 1; flag_temp < num_args; flag_temp++)
		{
			bool arg_found = false;
			bool unused_arg = true;
			for (int j = 0; j < n_valid_args; j++)
			{
				if (flag_temp == valid_args_index[j])
				{
					unused_arg = false;
					break;
				}
			}
			
			if (!arg_found && unused_arg)
			{
				size_t command_word_string_size = strlen(arguments[flag_temp]);

				err_buffer_size = NUM_LETTERS_WORD;
				err_buffer_write = (int64_t)command_word_string_size;

				if (NUM_LETTERS_WORD < command_word_string_size)
				{
					/* word is too long */
					free(command_word_string);
					err(WORD_TOO_LONG);
				}
				else if (NUM_LETTERS_WORD > command_word_string_size)
				{
					/* word is too short 
					 * error code 22 is for when the word is too short */
					free(command_word_string);
					err(WORD_TOO_SHORT);
				}
				else
				{
					/* use the length of the buffer directly instead of getting the size of the buffer and using that */
					for (uint8_t i = 0; i < NUM_LETTERS_WORD; i++)
					{
						/* check if the letter indexed is actually a letter */
						if (!(is_letter(arguments[flag_temp][i])))
						{
							free(command_word_string);
							err(INVALID_LETTER);
						}
						command_word_string[i] = up_letter(arguments[flag_temp][i]);
					}

					/* ensure the string is null terminated */
					command_word_string[NUM_LETTERS_WORD] = '\0';
				}
			}
		}

		validate_word(command_word_string);
		free(command_word_string);
	}
}

void invalid_flag(int total_args_index, int flag_index, const char *restrict flag[])
{
	total_args_index--;
	/* determine the amount of arguments to print around the value */
	int num_args_surrounding = command_arguments_context;

	printf(ANSI_RED"Invalid flag"STYLE_END": \""BOLD_S"%s"STYLE_END"\" at position %d\n", flag[flag_index], flag_index);

	if (num_args_surrounding > 0)
	{
		int lower_bound = flag_index - num_args_surrounding;

		if (lower_bound < 0)
		{
			lower_bound = 0;
		}

		int upper_bound = flag_index + num_args_surrounding;
		if (upper_bound > total_args_index)
		{
			upper_bound = total_args_index;
		}

		printf("\nHere’s where the command uses an invalid argument:");
		printf("\n\""BOLD_S);

		for (int i = lower_bound; i < flag_index; i++)
		{
			printf("%s ", flag[i]);
		}

		printf(ANSI_RED"%s "STYLE_END BOLD_S, flag[flag_index]);
		for (int i = flag_index + 1; i < upper_bound; i++)
		{
			/* print arguments one at a time */
			printf("%s ", flag[i]);
		}
		printf(STYLE_END"\"");
		for (int i = 0; i < indenting; i++)
		{
			printf("\n");
		}
	}
	

	if (valid_expression && total_args_index - flag_index >= 0)
	{
		/* this means that we need to append a message at the end of the program */
		append_flag_ignore_msg = true;

		const char *ignored_flags_template = BOLD_S"Ignored flags: "ANSI_RED"%s"STYLE_END;
		
		size_t ignored_flags_size = 1 + (size_t)snprintf(NULL, 0, ignored_flags_template, flag[flag_index]);
		char *flags_ignored_msg = malloc(ignored_flags_size);

		int ret = snprintf(flags_ignored_msg, ignored_flags_size, ignored_flags_template, flag[flag_index]);
		check_buf(ret, (int)ignored_flags_size, (void*)flags_ignored_msg);	/* check buffer for possible truncation  */

		printf("%s\n\n", flags_ignored_msg);
		free(flags_ignored_msg);
	}
	else
	{
		err(CMD_INVALID_ARG);
	}
}

char *get_letters(const char *restrict args[], int arg_i, enum parsing_type mode_type, int *index)
{
	arg_i++;
	printf("letters: %s\n", args[arg_i]);
	printf("letters: %s\n", args[arg_i + 1]);
	size_t str_len = strlen(args[arg_i]);

	/* convert the string to an index into the word (user_index) 
	 * only required to do this if the user is in exclude mode or strict mode */
	if (mode_type == strict || mode_type == exclude)
	{
		char *endptr = NULL;
		long user_index = strtol(args[arg_i + 1], &endptr, 10);
		if (*(endptr) == args[arg_i + 1][0])
		{
			/* the strings are matching, therefore no valid characters were found */
			fprintf(stderr, "Invalid index, '%s' is supposed to be an number (index)\n", endptr);
			printf("%s is regex\n", endptr);
			err(INVALID_INDEX);
		}

		if (*(endptr) != '\0')
		{
			/* there was at least one invalid character */
			fprintf(stderr, "Invalid user index \"%s\" contains invalid index \"%s\"\n", 
					args[arg_i + 1], endptr);
			err(INVALID_INDEX);
		}

		*(index) = (int)user_index;
	}


	if (str_len > 1)
	{
		if (mode_type == strict)
		{
			/* TODO free all buffers (prevent memory leak) */
			err(MULTI_LET_SUPPORT);
		}

		if (str_len > 26)
		{
			fprintf(stderr, "Too many letters following the parsing flag\n");
		}
	}
	else
	{
		char *str = smalloc(2);
		strncpy(str, args[arg_i], 2);
		return str;
	}
	char *letters_string = smalloc(str_len + 1);

	size_t letter_entry = 0;
	for (int i = 0; i < (signed)str_len; i++)
	{
		if (is_letter(args[arg_i][i]))
		{
			letters_string[letter_entry] = (char)up_letter(args[arg_i][i]);
			letter_entry++;
		}
		/* otherwise it isn't a letter and it cannot be parsed */
	}

	printf("string: %s\n", letters_string);
	return letters_string;	 /* returns a pointer to the string */
}

bool check_for_pkg(const char *restrict cmd)
{
	/* default is true */
	if (cmp(cmd, "wordle-solver", "wordle"))
	{
		return true;
	}
	else if (cmp(cmd, "./wordle-solver", "./wordle"))
	{
		return false;
	}
	else
	{
		if (strlen(cmd) > 2)
		{
			if ((cmd[0] == '.') && (cmd[1] == '/'))
			{
				return false;
			}
			else if (cmd[0] == '~')
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}
