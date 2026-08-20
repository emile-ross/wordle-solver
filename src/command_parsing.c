#include "include/header.h"

#include <ctype.h>

bool valid_expression;
bool append_flag_ignore_msg;

void command_parsing(int num_args, int arg_r, const char *arguments[], bool *find_match_mode)
{
	bool x_pattern = false;
	bool first_execution = true;
	bool validate_word_bl = false;

	if (num_args >= 2)
    	{
		const char *user_command = arguments[0];
		/* default is true */
		if (cmp(user_command, "wordle-solver"))
		{
			installed_package = true;
		}
		else if (cmp(user_command, "wordle"))
		{
			installed_package = true;
		}
		else if (cmp(user_command, "./wordle"))
		{
			installed_package = false;
		}
		else if (cmp(user_command, "./wordle-solver"))
		{
			installed_package = false;
		}
		else
		{
			if (strlen(user_command) > 2)
			{
				if ((user_command[0] == '.') && (user_command[1] == '/'))
				{
					installed_package = false;
				}
				else if (user_command[0] == '~')
				{
					installed_package = false;
				}
				else
				{
					installed_package = true;
				}
			}
		}

		/* set the default word list as the nyt word list */
		word_list = default_word_list;
		bool word_list_is_specified = false;

		int n_valid_args = 0;
		int valid_args_index[max_valid_args];
		append_flag_ignore_msg = false;	/* if a "ignored flag" message should appear at the end */

		for (uint8_t i = 0; i < num_args; i++)
		{
			if (arg_match(arguments[i], "--draw", "-d"))
			{
				if (!ignore_warn)
					warn(draw);
		
				*(find_match_mode) = false; /* we are making a cool pattern/drawing. We aren't matching words */
				valid_args_index[n_valid_args] = i;
				n_valid_args++;
			}
			else if (arg_match(arguments[i], word_list_long_flag, word_list_flag))
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

				int list_name_index = i + 1;

			
				if (num_args > list_name_index)
				{
					if (arg_match(arguments[list_name_index], "common", "common-words"))
					{
						word_list = en_common;
					}
					else if (arg_match(arguments[list_name_index], "all", "all-words"))
					{
						word_list = en_all;
					}
					else if (arg_match(arguments[list_name_index], "fr", "french"))
					{
						word_list = fr_all;
					}
					else if (arg_match(arguments[list_name_index], "la-com", "latin-common"))
					{
						word_list = la_common;
					}
					else if (arg_match(arguments[list_name_index], "la", "latin"))
					{
						word_list = la_all;
					}
					else if (arg_match(arguments[list_name_index], "nyt", "NYT") || cmp(arguments[list_name_index], "times"))
					{
						word_list = en_nyt;
					}
					else if (cmp(arguments[list_name_index], "custom"))
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
					valid_args_index[n_valid_args] = list_name_index;
					n_valid_args++;
					word_list_is_specified = true;
					/* break out of the flag checking loop 
					 * because a valid word list argument was provided 
					 * Valid word list argument: (-w all or something like that) */
				}
			}
			else if (arg_match(arguments[i], "-v", "--validate"))
			{
				*(find_match_mode) = false; /* We aren't matching words */
				validate_word_bl = true; /* we are validating a word */
				valid_args_index[n_valid_args] = i;
				n_valid_args++;
			}
		}

		if (*(find_match_mode))
		{
			struct prs_args parsing_arguments = 
			{
				&arg_r,
				word_list,
				num_args,
				&first_execution
			};

			while (arg_r < num_args)
			{
				if (arg_match(arguments[arg_r], "--strict", "-s"))
				{
					parsing(parsing_arguments, true, true, arguments);
				}
				else if (arg_match(arguments[arg_r], "--excludes", "-x") || cmp(arguments[arg_r], "-e"))
				{
					parsing(parsing_arguments, false, true, arguments);
				}
				else if (arg_match(arguments[arg_r], "--includes", "-i"))
				{
					parsing(parsing_arguments, true, false, arguments);
				}
				else if (arg_match(arguments[arg_r], "--absent", "-a"))
				{
					parsing(parsing_arguments, false, false, arguments);
				}
				else
				{
					if (word_list_is_specified)
					{
						if (arg_match(arguments[arg_r], word_list_long_flag, word_list_flag))
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
			int min_args_draw = 3;
			if (word_list_is_specified)
			{
				min_args_draw += 2;
			}

			if (num_args >= min_args_draw)
			{
				/* match arguments */
				char *command_word_string = malloc(INDEX_LETTERS_WORD);

				if (command_word_string == NULL)
				{
					err(MALLOC_FAIL);
				}

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

					if (unused_arg && !validate_word_bl && num_args > min_args_draw)
					{
						if (arg_match(arguments[flag_temp], "-x", "-X"))
						{
							arg_found = true;
							x_pattern = true;
						}
						/* if it's not -x flag it's probably an invalid or unused argument */
					}
					
					if (!arg_found)
					{
						if (unused_arg)
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
									if (!(isalpha(arguments[flag_temp][i])))
									{
										free(command_word_string);
										err(INVALID_LETTER);
									}
									command_word_string[i] = (char)toupper(arguments[flag_temp][i]);
								}

								/* ensure the string is null terminated */
								command_word_string[NUM_LETTERS_WORD] = '\0';
							}
						}
					}
				}

				if (validate_word_bl)
					validate_word(command_word_string);
				else
					drawing(command_word_string, x_pattern);

				free(command_word_string);
			}
		}
	}
	else
	{
		err(CMD_MISSING_ARGS);
	}
}

void invalid_flag(int total_args_index, int flag_index, const char *flag[])
{
	total_args_index--;
	/* determine the amount of arguments to print around the value */
	int num_args_surrounding = command_arguments_context;

	printf(ANSI_RED"Invalid flag"STYLE_END": \""BOLD_S"%s"STYLE_END"\" at position %d\n", flag[flag_index], flag_index);

	if (num_args_surrounding > 0)
	{
		int lower_bound = flag_index - num_args_surrounding;

		if (lower_bound < 0)
			lower_bound = 0;

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

bool arg_match(const char *arg, const char *long_flag, const char *short_flag)
{
	/* match the argument to the flags */
	if (strcmp(arg, long_flag) == 0)
	{
		return true;
	}
	else if (strcmp(arg, short_flag) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool cmp(const char *arg, const char *str)
{
	/* match the argument to the string */
	if (strcmp(arg, str) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
