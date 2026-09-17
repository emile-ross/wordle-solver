#include "include/header.h"

bool is_letter(const char restrict ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' || ch <= 'z'))
	{
		return true;
	}
	return false;
}
