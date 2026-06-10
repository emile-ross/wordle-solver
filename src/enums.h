typedef enum  
{
	fr_all,
	la_all,
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
	CMD_MISSING_ARGS = 1,
	CMD_INDEX_BOUNDS = 5,
	FEAT_NOT_IMPLEMENTED = 7,
	CMD_INVALID_ARG = 10,
	UNKNOWN_WORD_LIST = 15,
	NO_POSSIBLE_ANSWERS = 20,
	WORD_TOO_LONG = 21,
	WORD_TOO_SHORT = 22,
} error_codes;
