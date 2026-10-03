#include "../include/header.h"

char *mode_to_text(enum parsing_type type)
{
	switch (type)
	{
	case exclude:
		return "--excludes";
	case include:
		return "--includes";
	case absent:
		return "--absent";
	case strict:
		return "--strict";
	case undefined:
		fprintf(stderr, "error: undefined case in mode_to_text switch()\n");
		exit(1);
	default:
		return NULL;
	}
}
