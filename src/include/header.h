#define HEADER_DOT_H
#define _POSIX_C_SOURCE 200809L

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "enums.h"
#include "macros.h"

/* Word lists */
	char (*list_match(ALL_WORD_LISTS word_list_enum, uint32_t *number_of_words, bool standard_word_list))[6];
	char *word_list_name(ALL_WORD_LISTS word_list_type, void *buf);	/* returns the name of the word list */
	extern uint8_t NUM_WORD_LISTS;

/* filtered array used to store filtered words and it is also used for printing results */
	extern char filtered_arr[NUM_ALL_WORDS][INDEX_LETTERS_WORD];

/* errors and error codes */
	void err(error_codes error_code);
	void warn(warnings warning_type); /* warnings */
	void invalid_flag(int total_args_index, int flag_index, const char *flag[]);
	void help_message(void);
	void check_buf(int return_value, int64_t size_of_buffer, void *buf_to_free[]);
	int buffer_write(void *buf_to_free[], char *string, size_t size_of_string, const char *restrict format, ...);

	/* used in err() in order to show; 
	 * the write size (in bytes) and the buffer size (in bytes) */
	extern int64_t err_buffer_size;
	extern int64_t err_buffer_write;

void print_as_table(uint16_t width, uint64_t total_elements, bool awsum_mode, char all_answers_print[NUM_ALL_WORDS][INDEX_LETTERS_WORD]);

void direct_parsing(char letter_indexed, int word_letter_index, bool filter_include_bl, bool letter_indexed_bl, bool *f_exec);

int parsing(struct prs_args parsing_args, bool filter_include_bl, bool letter_indexed_bl, const char *arguments[]);

/* command parsing */
	void command_parsing(int num_args, int flag_reading_index, const char *arguments[], bool *find_match_mode);
	bool arg_match(const char *arg, const char *long_flag, const char *short_flag);

void drawing(char wordle_answer[INDEX_LETTERS_WORD], bool x_pattern);
void validate_word(char *command_word_string);

/* Global variables */
	extern int ARGS_BEFORE_CUR_FLAG;
	extern ALL_WORD_LISTS word_list;
	extern ALL_WORD_LISTS default_word_list;
	extern uint32_t n_possible_answers;
	extern const char *word_list_flag;
	extern const char *word_list_long_flag;

	extern bool valid_expression;
	extern bool append_flag_ignore_msg;

/* General simple functions */
	uint8_t valid_user_index(long index, void *ptr_to_free);

/* config file */
	extern bool awsum_table_mode;
	extern uint16_t table_width;
	extern const bool verbose;
	extern const uint8_t indenting;
	extern bool ignore_warn;
	extern int command_arguments_context;

	extern uint64_t element_cap;
	extern bool cap_total_elements;
	extern char *custom_list_name;
	extern const char *default_config_list_name;
	extern const char *program_name;

void verbose_printing(char *flag, char letter, int indexed_letter_value, uint32_t affected_words, bool letter_is_present);
void verbose_print(const char *restrict format, ...);


/* file related */
	char (*read_words(char *file_path, uint32_t *num_words))[6];
	uint16_t get_num_lines(char *file_path);
	char *get_filename(ALL_WORD_LISTS word_list_type);
	char *get_custom_file(char *buffer, size_t buffer_size);
	extern char *custom_filename;	/* defined in functions.c */

	bool installed_package;

size_t prepend_fp(char *file_path_dst, size_t dst_size, char *filename);
