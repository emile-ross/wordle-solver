#include "include/header.h"

#define GET_VALS() \

struct data_for_parsing convert_to_struct(const char *restrict argv[], const int argc, int arg_i)
{
	bool success = false;
	for (int i = 0; i < argc; i++)
	{
		success = true;
		
		enum parsing_type type = 0;
		if (cmp(arguments[arg_i], "--strict", "-s"))
		if (cmp(argv[arg_i], "--strict", "-s"))
		{
		else if (cmp(arguments[arg_i], "--excludes", "-x") || scmp(arguments[arg_i], "-e"))
		else if (cmp(arguments[arg_i], "--includes", "-i"))
		else if (cmp(arguments[arg_i], "--absent", "-a"))
		}
		else
		{
			if (word_list_is_specified)
			{
				if (cmp(arguments[arg_i], word_list_long_flag, word_list_flag))
				{
					arg_i += WORD_LIST_ARG_EXP;
				}
			}
			else 
			{
			}
		}

		if (success)
		{
			if (parsing_type == exclude || parsing_type == strict)
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
			char *letter_str = get_letters(arguments, arg_i, strict, &index);
			int i = 0;

			do
			{
				parsing_arguments.letter_indexed = letter_str[i];
				parsing(parsing_arguments, strict);
				i++;
			} while (letter_str[i] != '\0');
		}
	}
}
