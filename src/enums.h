typedef enum  
{
	fr_all,
	all,
	common,
	nyt,
} ALL_WORD_LISTS ;

typedef enum 
{
	draw,
	strict,
	xdraw,
} warnings;

typedef enum
{
	drawing_mode,
	matching_mode,
	validating_mode,
} parsing_modes;


typedef enum
{
	UNKNOWN_WORD_LIST = 15,
	WORD_TOO_LONG = 21,
	WORD_TOO_SHORT = 22,
} error_codes;
