#include "include/header.h"

bool cmp(const char *arg, const char *long_flag, const char *short_flag)
{
	/* match the argument to the flags */
	if (scmp(arg, short_flag))
	{
		return true;
	}
	else if (scmp(arg, long_flag))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool scmp(const char *arg, const char *str)
{
	/* match the argument to the string */
	uint16_t i = 0;	/* supports up to 65535 characters */
	while (arg[i] != '\0' && str[i] != '\0')
	{
		if (arg[i] != str[i])
		{
			return false;
		}
		i++;
	}
	return true;
}
