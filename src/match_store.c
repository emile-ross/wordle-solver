#include "include/header.h"

typedef enum
{
	UNDEFINED = 0,
	EXPECT_FLAG,
	EXPECT_LETTER,
	EXPECT_INDEX
} state_type;

void convert_to_struct(struct data_for_parsing **data_ptr[], bool list_specified, const char *restrict argv[], const int argc, int arg_i)
{
	bool success = false;
	int index = 0;
	char character = '\0';

	size_t size_increment = 2;

	size_t num_entries = (unsigned int)((argc - arg_i) / 3);
	*(data_ptr) = smalloc(sizeof(struct data_for_parsing) * num_entries);

	(*data_ptr[0])->type = undefined;
	(*data_ptr[0])->index = -1;
	(*data_ptr[0])->character = '\0';

	/* arg_i is incremented at the end of the loop */
	for (int i = 0; arg_i < argc; i++)
	{
		success = true;
		character = '\0';
		index = 0;
		bool flag_found = true;
		
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
			flag_found = false;
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

				index = (int)user_index;

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
			if (flag_found)
			{
				character = argv[arg_i + 1][0];
				/* TODO add logic for other types with enums maybe */

			}


		}
		if (i > num_entries)
		{
			num_entries += size_increment;
			data_ptr = realloc(data, (sizeof(struct data_for_parsing) * num_entries));
			size_increment <<= 1;
		}
		(*data_ptr[i])->type = type;
		(*data_ptr[i])->index = index;
		(*data_ptr[i])->character = character;
		arg_i++;
	}
}
