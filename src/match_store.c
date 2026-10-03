#include "include/header.h"

#define GET_VALS() \

struct data_for_parsing convert_to_struct(bool list_specified, const char *restrict argv[], const int argc, int arg_i)
{
	bool success = false;
	int index = 0;
	for (int i = 0; i < argc; i++)
	{
		success = true;
		
		enum parsing_type type = 0;
		size_t len = strlen(argv[arg_i + 1]);

		if (cmp(argv[arg_i], "--strict", "-s"))
		{
			type = strict;
		}
		else if (cmp(argv[arg_i], "--excludes", "-x") || scmp(argv[arg_i], "-e"))
		{
			type = exclude;
		}
		else if (cmp(argv[arg_i], "--includes", "-i"))
		{
			type = include;
		}
		else if (cmp(argv[arg_i], "--absent", "-a"))
		{
			type = absent;
		}
		else
		{
			if (list_specified)
			{
				if (cmp(argv[arg_i], word_list_long_flag, word_list_flag))
				{
					arg_i += WORD_LIST_ARG_EXP;
				}
			}
			else 
			{
				success = false;
				/* can be improved */
				invalid_flag(argc, arg_i, argv);
			}
		}

		if (success)
		{
			if (type == exclude || type == strict)
			{
				char *endptr = NULL;
				long user_index = strtol(argv[arg_i + 1], &endptr, 10);
				if (*(endptr) == argv[arg_i + 1][0])
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
							argv[arg_i + 1], endptr);
					err(INVALID_INDEX);
				}

				*(index) = (int)user_index;

				if (type == strict)
				{
					/* TODO free all buffers (prevent memory leak) */
					err(MULTI_LET_SUPPORT);
				}
			}

			if (len > 26)
			{
				fprintf(stderr, "Warning: too many letters following the parsing flag\n");
			}

			char *letter_str = get_letters(argv, arg_i, strict, &index);
			int j = 0;

			do
			{
				parsing_arguments.letter_indexed = letter_str[j];
				parsing(parsing_arguments, strict);
				i++;
			} while (letter_str[j] != '\0');
		}
	}
}
