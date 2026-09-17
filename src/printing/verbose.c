#include "../include/header.h"

#include <stdarg.h>

void verbose_printing(char *flag, char letter, int indexed_letter_value, uint32_t affected_words, bool letter_is_present)
{
	/* add colour to options */
	verbose_print(BOLD_S"%s", flag);
	verbose_print(" flag caused ");
	verbose_print(UDRL_S BOLD_S"%d", affected_words);
	verbose_print(" word");

	/* craft sentence with appropriate words
	 * make sure it is grammatically correct (plural and negative statements) */

	if (affected_words != 1)
    	{
		verbose_print("s");
    	}

    	if (letter_is_present)
    	    	verbose_print(" with ");
    	else
    	    	verbose_print(" without ");

    	verbose_print(UDRL_S BOLD_S"%c"STYLE_END" ", letter);

	/* add colour to options */
    	if (indexed_letter_value != -1)
    	{
		/* in order to make it more user friendly because the user inputs a value 1-5 not 0-4 */
    	    	indexed_letter_value++; 
    	    	verbose_print("at index "UDRL_S BOLD_S"%d", indexed_letter_value);
    	}

	verbose_print(" to be moved to the filtered array");

	/* decrease the indenting by one */
	int temp_indenting = indenting;
	if (indenting >= 2)
	{
		temp_indenting--;
	}

	for (int i = 0; i < temp_indenting; i++)
	{
		printf("\n");
	}
}

void verbose_print(const char *restrict format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the verbose message */
	size_t msg_size = 1 + (size_t)vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	/* allocate memory for the verbose message */
	char *verbose_msg = malloc(msg_size);

	void *arr[2] = 
	{
		verbose_msg,
		NULL
	};

	if (verbose_msg == NULL)
	{
		err(MALLOC_FAIL);
		exit(1);
	}
	size_t ret = (size_t)vsnprintf(verbose_msg, msg_size, format, args);

	check_buf((int)ret, (int)msg_size, arr);

	va_end(args);

	if (ret > msg_size)
	{
		free(verbose_msg);
		err(VERBOSE_FAIL);
		exit(1);
	}

	/* set colours for verbose messages below */
	printf(ANSI_LCYAN"%s"STYLE_END, verbose_msg);
	free(verbose_msg);
}
