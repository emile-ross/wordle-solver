#include "header.h"

void command_parsing(int argc, int flag_reading_index, char *arguments[], bool *find_match_mode)
{
    bool first_execution = true;
    if (argc >= 2)
    {
		/* set the default word list as the nyt word list */
		word_list = default_word_list;
		bool word_list_is_specified = false;

		int n_valid_args = 0;
		int valid_args_index[max_valid_args];
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(arguments[i], "--draw") == 0 || strcmp(arguments[i], "-d") == 0)
			{
				find_match_mode = false; /* we are making a cool pattern/drawing. We aren't matching words */
				valid_args_index[n_valid_args] = i;
				n_valid_args++;
			}
			else if (strcmp(arguments[i], "--word-list") == 0 || strcmp(arguments[i], "-w") == 0)
    	    {
				valid_args_index[n_valid_args] = i;
				n_valid_args++;

				bool valid_word_list = true;
				if (!first_execution)	/* print error message if -w comes after words have been filtered */
				{
					valid_word_list = false;
					if (!ignore_warn)
					{
						err(16);
					}
				}
				int list_name_index;
				if (argc >= 3)
    			{
    			    list_name_index = i + 1;  /* read 1 argument ahead of the "-w" flag */
    			    if (strcmp(arguments[list_name_index], "common") == 0 || strcmp(arguments[list_name_index], "common-words") == 0)
    			    {
						word_list = common;
    			    }
    			    else if (strcmp(arguments[list_name_index], "all") == 0 || strcmp(arguments[list_name_index], "all-words") == 0)
    			    {
    			    	word_list = all;
    			    }
    			    else if (strcmp(arguments[list_name_index], "nyt") == 0 || strcmp(arguments[list_name_index], "NYT") == 0 || strcmp(arguments[list_name_index], "times") == 0)
    			    {
						word_list = nyt;
					}
					else
					{
						valid_word_list = false;
						err(15);
					}
    		        
					if (verbose)
    		    	{
    		    		printf(ANSI_LCYAN"using the "BOLD_S"%s"STYLE_END ANSI_LCYAN" word list\n"STYLE_END, word_list_text[word_list]);
    		    	}
    		        
				}
    			else /* missing arguments */
    			{
					valid_word_list = false;
					err(1); 
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
		}

		if (find_match_mode)
		{
			while(flag_reading_index < argc)
    		{
    			if (strcmp(arguments[flag_reading_index], "--strict") == 0 || strcmp(arguments[flag_reading_index], "-s") == 0)
    			{
    			    parsing(&flag_reading_index, word_list, &first_execution, true, true, arguments);
    			}
    			else if (strcmp(arguments[flag_reading_index], "--exclude") == 0 || strcmp(arguments[flag_reading_index], "-x") == 0 || strcmp(arguments[flag_reading_index], "-e") == 0)
    			{
    			    parsing(&flag_reading_index, word_list, &first_execution, false, true, arguments);
    			}
    			else if (strcmp(arguments[flag_reading_index], "--includes") == 0 || strcmp(arguments[flag_reading_index], "-i") == 0)
    			{
    			    parsing(&flag_reading_index, word_list, &first_execution, true, false, arguments);
    			}
    			else if (strcmp(arguments[flag_reading_index], "--absent") == 0 || strcmp(arguments[flag_reading_index], "-a") == 0 || strcmp(arguments[flag_reading_index], "-d") == 0)
    			{
    			    parsing(&flag_reading_index, word_list, &first_execution, false, false, arguments);
    			}
    			else
    			{
					if (word_list_is_specified)
					{
						if (strcmp(arguments[flag_reading_index], "--word-list") == 0 || strcmp(arguments[flag_reading_index], "-w") == 0)
						{
							flag_reading_index += WORD_LIST_ARG_EXP;
						}
					}
					else 
					{
						/* can be improved */
						invalid_flag(argc, flag_reading_index, arguments);
					}
    			}
    		}
		}
		else
		{
			int min_args_draw = 3;
			bool x_pattern = false;
			if (word_list_is_specified)
			{
				min_args_draw += 2;
			}
			if (argc >= min_args_draw)
			{

			}
		}
    }
}

void invalid_flag(int total_args_index, int flag_index, char *flag[])
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
			printf("%s ", flag[i]);
		}
		printf(STYLE_END"\"\n\n");
	}
	err(10);
}
