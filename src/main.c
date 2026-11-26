#include "include/header.h"

char filtered_arr[NUM_ALL_WORDS][INDEX_LETTERS_WORD];

ALL_WORD_LISTS word_list;

int c_main(const int argc, const char *restrict argv[])
{
	uint32_t num_possible_answers = 0;
	valid_expression = false;
	bool find_match_mode = true; /* true by default
	 * true: finds all possible words matching all criterias
	 * false: tries to make a pattern with the letter colour */

	if (argc >= 2)  /* or else there's nothing */
	{
		int flag_r = ARGS_BEFORE_FLAG_BASE;
		/* execute command parsing and provide the address of find_match_mode
		 * in order to then dereference the address */
		command_parsing(argc, flag_r, argv, &find_match_mode, &num_possible_answers);
	}
	else
	{
		err(CMD_MISSING_ARGS);
		return 1;
	}

	if (find_match_mode)
		print_as_table(table_width, num_possible_answers, awsum_table_mode, filtered_arr);

	return 0;
}

