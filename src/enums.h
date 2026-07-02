typedef enum  
{
	en_nyt,
	en_common,
	en_all,
	fr_all,
	la_common,
	la_all,
	custom,
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
	NEGATIVE_INDEX = 4,
	CMD_INDEX_BOUNDS = 5,
	NO_SUCH_FILE = 6,
	FEAT_NOT_IMPLEMENTED = 7,
	CMD_INVALID_ARG = 10,
	UNKNOWN_WORD_LIST = 15,
	NO_POSSIBLE_ANSWERS = 20,
	WORD_TOO_LONG = 21,
	WORD_TOO_SHORT = 22,
	FORMATTING_ERROR = 31,
	BUFFER_WRITE_FAIL = 32,
	MALLOC_ERR = 33,
	FILENAME_FAIL = 50,
	FILEPATH_FAIL = 51,
} error_codes;
