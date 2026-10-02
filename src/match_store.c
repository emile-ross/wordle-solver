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
		{
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
		}
	}
}
