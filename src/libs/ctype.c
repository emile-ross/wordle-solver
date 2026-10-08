#include "../include/header.h"

bool is_letter(const char ch)
{
	/* match all letters in the ascii table 
	 * (uppercase & lowercase matches) */
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' || ch <= 'z'))
	{
		return true;
	}
	return false;
}

char up_letter(int ch)
{
	if (ch > 96 && ch < 123)
	{
		char ret = (char)(ch - 32);
		return ret;
	}
	else if (!(is_letter((char)ch)))
	{
		err(INVALID_LETTER);
		exit(EXIT_FAILURE);
	}


	return (char)ch;
}
