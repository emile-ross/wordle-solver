#include "header.h"

void command_parsing(int argc, int flag_reading_index, char *arguments[])
{
    bool first_execution = true;
    if (argc >= 2)
    {
		while(flag_reading_index < argc)
    	{
			if (strcmp(arguments[flag_reading_index], "--word-list") == 0 || strcmp(arguments[flag_reading_index], "-w") == 0)
    	    {
				if (!first_execution)	// print error message if -w comes after words have been filtered
				{
					if (!ignore_warn)
					{
						err(16);
					}
				}
    		
				if (argc >= 3)
    			{
    			    int wlist_indx_t = flag_reading_index + 1;  // read 1 argument ahead of the "flag_reading_index" integer
    			    if (strcmp(arguments[wlist_indx_t], "common") == 0 || strcmp(arguments[wlist_indx_t], "common-words") == 0)
    			    {
						word_list = common;
    			    }
    			    else if (strcmp(arguments[wlist_indx_t], "all") == 0 || strcmp(arguments[wlist_indx_t], "all-words") == 0)
    			    {
    			    	word_list = all;
    			    }
    			    else if (strcmp(arguments[wlist_indx_t], "nyt") == 0 || strcmp(arguments[wlist_indx_t], "NYT") == 0 || strcmp(arguments[wlist_indx_t], "times") == 0)
    			    {
						word_list = nyt;
					}
					else
					{
						err(15);
					}
    		        
    		    if (verbose)
    		    {
    		    	printf(ANSI_LCYAN"using the "BOLD_S"%s"STYLE_END ANSI_LCYAN" word list\n"STYLE_END, word_list_text[word_list]);
    		    }
    		        
    		}
    		else // missing arguments
    		{
				err(1); 
    		}
    		
    		// this sets the word list as the common word list (5700 words)
    		flag_reading_index += WORD_LIST_ARG_EXP;

    		}
    		else if (strcmp(arguments[flag_reading_index], "--strict") == 0 || strcmp(arguments[flag_reading_index], "-s") == 0)
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
    		    err(10);
    		}
    	}
    }
}
