#include "include/header.h"

typedef enum
{
	UNDEFINED = 0,
	EXPECT_FLAG,
	EXPECT_LETTER,
	EXPECT_INDEX
} state_type;

struct data_for_parsing *convert_to_struct(size_t *p_num_entries, const bool list_specified, const char *restrict argv[], const int argc, int arg_i)
{
	state_type state = EXPECT_FLAG;
	size_t size_increment = 2;

	size_t num_entries = (unsigned int)((argc - arg_i) / 3);
	struct data_for_parsing *data_ptr;
	
	data_ptr = calloc(num_entries + 1, sizeof(struct data_for_parsing));

	data_ptr[0].type = undefined;
	data_ptr[0].index = -1;
	data_ptr[0].character = '\0';

	int i = 0;

	/* arg_i is incremented at the end of the loop */
	for (; arg_i < argc; arg_i++)
	{
		if (state == EXPECT_FLAG)
		{
			if (cmp(argv[arg_i], "--strict", "-s"))
			{
				if (arg_i + P_FILTERS_ARG_EXP > argc)
				{
					err(CMD_MISSING_ARGS);
				}
				data_ptr[i].type = strict;
			}
			else if (cmp(argv[arg_i], "--excludes", "-x") || scmp(argv[arg_i], "-e"))
			{
				if (arg_i + P_FILTERS_ARG_EXP > argc)
				{
					err(CMD_MISSING_ARGS);
				}
				data_ptr[i].type = exclude;
			}
			else if (cmp(argv[arg_i], "--includes", "-i"))
			{
				if (arg_i + G_FILTERS_ARG_EXP > argc)
				{
					err(CMD_MISSING_ARGS);
				}
				data_ptr[i].type = include;
			}
			else if (cmp(argv[arg_i], "--absent", "-a"))
			{
				if (arg_i + G_FILTERS_ARG_EXP > argc)
				{
					err(CMD_MISSING_ARGS);
				}
				data_ptr[i].type = absent;
			}
			else
			{
				printf("No flag found\n");
				if (list_specified)
				{
					if (cmp(argv[arg_i], word_list_long_flag, word_list_flag))
					{
						arg_i += WORD_LIST_ARG_EXP;
					}
				}
				else 
				{
					/* can be improved */
					invalid_flag(argc, arg_i, argv);
				}
			}
			state = EXPECT_LETTER;
		}
		else if (state == EXPECT_LETTER)
		{
			if (strlen(argv[arg_i]) > 26)
			{
				fprintf(stderr, "Warning: too many letters following the parsing flag\n");
			}

			if (data_ptr[i].type == strict && strlen(argv[arg_i]) > 1)
			{
				/* TODO free all buffers (prevent memory leak) */
				err(MULTI_LET_SUPPORT);
			}
			data_ptr[i].character = up_letter(argv[arg_i][0]);
			if (data_ptr[i].type == exclude || data_ptr[i].type == strict)
			{
				state = EXPECT_INDEX;
			}
			else
			{
				state = EXPECT_FLAG;
				i++;
			}
		}
		else if (state == EXPECT_INDEX)
		{
			char *endptr = NULL;
			long value = strtol(argv[arg_i], &endptr, 10);
			
			if (*endptr == argv[arg_i][0])
			{
				fprintf(stderr, "Invalid index: %s\n", endptr);
				err(INVALID_INDEX);
			}

			if (*(endptr) != '\0')
			{
				/* there was at least one invalid character */
				fprintf(stderr, "Invalid user index \"%s\" contains invalid index \"%s\"\n", 
						argv[arg_i], endptr);
				err(INVALID_INDEX);
			}

			if (value < 0 || value > NUM_LETTERS_WORD)
			{
				fprintf(stderr, "User index is out of bounds (minimum 0, maximum %d)\n", NUM_LETTERS_WORD);
				exit(EXIT_FAILURE);
			}
			data_ptr[i].index = (int)value - 1;

			i++;
			state = EXPECT_FLAG;
		}
		else
		{
			fprintf(stderr, "Logic error (undefined state)\n");
			exit(EXIT_FAILURE);
		}

		if (i > (signed)num_entries)
		{
			num_entries += size_increment;
			data_ptr = realloc(data_ptr, (sizeof(struct data_for_parsing) * num_entries));
			size_increment <<= 1;
		}
	}

	printf("%d is the index\n", data_ptr[0].index);
	printf("%c is the character\n", data_ptr[0].character);

	*p_num_entries = (unsigned)(i + 1);
	return data_ptr;
}
