#include "header.h"

bool valid_expression;
bool append_flag_ignore_msg;

void command_parsing(int num_args, int flag_reading_index, const char *arguments[], bool *find_match_mode)
{
	bool x_pattern = false;
	bool first_execution = true;
	bool validate_word_bl = false;

	if (num_args >= 2)
    	{
		/* set the default word list as the nyt word list */
		word_list = default_word_list;
		bool word_list_is_specified = false;

		int n_valid_args = 0;
		int valid_args_index[max_valid_args];
		append_flag_ignore_msg = false;	/* if a "ignored flag" message should appear at the end */
		for (int i = 0; i < num_args; i++)
		{
			if (arg_match(arguments[i], "--draw", "-d"))
			{
				if (!ignore_warn)
					warn(draw);
		
				*find_match_mode = false; /* we are making a cool pattern/drawing. We aren't matching words */
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
					if (strcmp(arguments[list_name_index], "common") == 0 || strcmp(arguments[list_name_index], "common-words") == 0)
					{
						word_list = en_common;
					}
					else if (strcmp(arguments[list_name_index], "all") == 0 || strcmp(arguments[list_name_index], "all-words") == 0)
					{
						word_list = en_all;
					}
					else if (strcmp(arguments[list_name_index], "fr") == 0 || strcmp(arguments[list_name_index], "french") == 0)
					{
						word_list = fr_all;
					}
					else if (strcmp(arguments[list_name_index], "la-com") == 0 || strcmp(arguments[list_name_index], "latin-common") == 0)
					{
						word_list = la_common;
					}
					else if (strcmp(arguments[list_name_index], "la") == 0 || strcmp(arguments[list_name_index], "latin") == 0)
					{
						word_list = la_all;
					}
					else if (strcmp(arguments[list_name_index], "nyt") == 0 || strcmp(arguments[list_name_index], "NYT") == 0 || strcmp(arguments[list_name_index], "times") == 0)
					{
						word_list = en_nyt;
					}
					else if (strcmp(arguments[list_name_index], "custom") == 0)
					{
						word_list = custom;
					}
					else
					{
						valid_word_list = false;
						err(UNKNOWN_WORD_LIST);
					}

					if (verbose)
    		    			{
    		    				printf(ANSI_LCYAN"using the "BOLD_S"%s"STYLE_END ANSI_LCYAN" word list\n"STYLE_END, word_list_name(word_list));
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
				*find_match_mode = false; /* We aren't matching words */
				validate_word_bl = true; /* we are validating a word */
				valid_args_index[n_valid_args] = i;
				n_valid_args++;
			}
		}

		if (*find_match_mode)
		{
			while (flag_reading_index < num_args)
			{
				if (arg_match(arguments[flag_reading_index], "--strict", "-s"))
    				{
					parsing(&flag_reading_index, word_list, &first_execution, true, true, arguments, num_args);
    				}
    				else if (arg_match(arguments[flag_reading_index], "--excludes", "-x") || strcmp(arguments[flag_reading_index], "-e") == 0)
    				{
					parsing(&flag_reading_index, word_list, &first_execution, false, true, arguments, num_args);
    				}
    				else if (arg_match(arguments[flag_reading_index], "--includes", "-i"))
    				{
					parsing(&flag_reading_index, word_list, &first_execution, true, false, arguments, num_args);
    				}
    				else if (arg_match(arguments[flag_reading_index], "--absent", "-a"))
    				{
					parsing(&flag_reading_index, word_list, &first_execution, false, false, arguments, num_args);
    				}
    				else
    				{
					if (word_list_is_specified)
					{
						if (strcmp(arguments[flag_reading_index], word_list_long_flag) == 0 || strcmp(arguments[flag_reading_index], word_list_flag) == 0)
						{
							flag_reading_index += WORD_LIST_ARG_EXP;
						}
					}
					else 
					{
						/* can be improved */
						invalid_flag(num_args, flag_reading_index, arguments);
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
				char *command_word_string = malloc((size_t)INDEX_LETTERS_WORD);

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
						if (strcmp(arguments[flag_temp], "-x") == 0 || strcmp(arguments[flag_temp], "-X") == 0)
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

							if (NUM_LETTERS_WORD < command_word_string_size)
							{
								/* word is too long */
								err(WORD_TOO_LONG);
							}
							else if (NUM_LETTERS_WORD > command_word_string_size)
							{
								/* word is too short 
								 * error code 22 is for when the word is too short */
								err(WORD_TOO_SHORT);
							}
							else
							{
								/* use the length of the buffer directly instead of getting the size of the buffer and using that */
								const size_t size = INDEX_LETTERS_WORD;
								int ret = snprintf(command_word_string, size,
										"%s", arguments[flag_temp]);
								
								check_buf(ret, (int)size);	/* check buffer for possible truncation  */
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
		check_buf(ret, (int)ignored_flags_size);	/* check buffer for possible truncation  */

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
