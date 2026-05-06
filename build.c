#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *ALL_FLAGS = "-Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow";

#define compiler_name_len (8)
char *CLANG_COMPILER_NAME = "clang";
char *ZIG_COMPILER_NAME = "zig cc";
char *GCC_COMPILER_NAME = "gcc";

#define fp_size 32
#define base_args 1

char PARSING_FILE_PATH[fp_size] = "src/parsing";
char CONFIG_FILE_PATH[fp_size] = "src/config";
char MAIN_FILE_PATH[fp_size] = "src/main";
char CMDPARS_FILE_PATH[fp_size] = "src/command-parsing";

char ALL_WORDS_FILE_PATH[fp_size] = "src/word-lists/all-words";
char COM_WORDS_FILE_PATH[fp_size] = "src/word-lists/common-words";
char NYT_WORDS_FILE_PATH[fp_size] = "src/word-lists/words";
char *src_file_extention = ".c";
char *obj_file_extention = ".c";
bool compile_into_objects = false; /* hard coded right now but it will be dynamic in the future */

typedef enum 
{
    CLANG,
    GCC,
    ZIG,
} compiler_enum;

compiler_enum compiler_choice;

int main(int argc, char *argv[])
{
	int total_flags_size = 16;
	bool Wall_flag = false;
	bool Wextra_flag = false;
	bool Wconversion_flag = false;
	bool Wpedantic_flag = false;
	bool Werror_flag = false;
	bool C99_flag = false;
	bool Wshadow_flag = false;
	bool verbose = false; /* false by default */

	int flag_mem_size = 16;

	int num_flags = 0;
	if (argc > base_args)
	{
		int flag_r = base_args + 1;

		int base_flag_r = 1;
		bool compiler_found = false;
		while (base_args < argc)
		{
			char compiler_arg_temp = argv[base_flag_r][0];
			switch (compiler_arg_temp)
			{
				case 'C':
					compiler_choice = CLANG;
					compiler_found = true;
					break;
				case 'G':
					compiler_choice = GCC;
					compiler_found = true;
					break;
				case 'Z':
					compiler_choice = ZIG;
					compiler_found = true;
					break;
				default:
					printf("Missing compiler or unknown compiler\n");
					printf("%c", compiler_arg_temp);
					exit(1);
					break;
			}
			if (compiler_found)
			{
				break;
			}
			base_flag_r++;
		}

		while (argc > flag_r)
		{
			char flag_temp = argv[flag_r][0];
			bool success = true;

			switch (flag_temp)
			{
				case 'a':
					Wall_flag = true;
					break;
				case 'c':
					Wconversion_flag = true;
					break;
				case 'e':
					Werror_flag = true;
					break;
				case 'p':
					Wpedantic_flag = true;
					break;
				case 'x':
					Wextra_flag = true;
					break;
				case 's':
					Wshadow_flag = true;
					break;
				case '9':
					C99_flag = true;
					break;
				default:
					success = false;
					break;
			}

			if (success)
			{
				num_flags++;
				flag_r++;
			}
			else
			{
				/* this is an error */
				printf("Unknown argument: %c\n", flag_temp);
				exit(1);
			}
		}

		if (num_flags > 0)
		{
			int temp_total_flag_size = flag_mem_size * num_flags;
			total_flags_size += temp_total_flag_size;
		}
	}

	const char *src_files_template = " %s %s %s %s.c %s.c %s.c %s.c ";

	char SRC_ALL_WORDS[fp_size];
	char SRC_COM_WORDS[fp_size];
	char SRC_NYT_WORDS[fp_size];
	
	char OBJ_ALL_WORDS_FP[fp_size];
	char OBJ_COM_WORDS_FP[fp_size];
	char OBJ_NYT_WORDS_FP[fp_size];

	strcpy(SRC_ALL_WORDS, ALL_WORDS_FILE_PATH);
	strcpy(SRC_COM_WORDS, COM_WORDS_FILE_PATH);
	strcpy(SRC_NYT_WORDS, NYT_WORDS_FILE_PATH);

	strcat(SRC_ALL_WORDS, src_file_extention);
	strcat(SRC_COM_WORDS, src_file_extention);
	strcat(SRC_NYT_WORDS, src_file_extention);

	if (compile_into_objects)
	{
		/* create and initialize object file paths */
		strcpy(OBJ_ALL_WORDS_FP, ALL_WORDS_FILE_PATH);
		strcpy(OBJ_COM_WORDS_FP, COM_WORDS_FILE_PATH);
		strcpy(OBJ_NYT_WORDS_FP, NYT_WORDS_FILE_PATH);

		strcat(OBJ_ALL_WORDS_FP, obj_file_extention);
		strcat(OBJ_COM_WORDS_FP, obj_file_extention);
		strcat(OBJ_NYT_WORDS_FP, obj_file_extention);
	}

	int mem_needed_src = 0;
	if (!compile_into_objects)
	{
		char *parsing = PARSING_FILE_PATH;
		char *configp = CONFIG_FILE_PATH;
		char *main_fp = MAIN_FILE_PATH;
		char *cmd_parsing = CMDPARS_FILE_PATH;

		mem_needed_src = 1 + snprintf(NULL, 0, src_files_template, SRC_NYT_WORDS, SRC_ALL_WORDS, SRC_COM_WORDS, cmd_parsing, configp, parsing, main_fp);

		char compiler[compiler_name_len];

		switch (compiler_choice)
		{
			case GCC:
				strcpy(compiler, GCC_COMPILER_NAME);
				break;

			case CLANG:
				strcpy(compiler, CLANG_COMPILER_NAME);
				break;

			case ZIG:
				strcpy(compiler, ZIG_COMPILER_NAME);
				break;

			default:
				printf("Unknown compiler\n Very weird error\n");
				exit(1);
		}

		int mem_needed = mem_needed_src + snprintf(NULL, 0, "%s ", compiler);


		char *flags_string_base = "-o wordle";

		int mem_needed_all_c_flags = 1;

		char all_custom_flags[1024] = ""; 
		if (num_flags > 0)
		{
			if (Wall_flag)
			{
				strcat(all_custom_flags, "-Wall ");
			}
			if (Wextra_flag)
			{
				strcat(all_custom_flags, "-Wextra ");
			}
			if (Wconversion_flag)
			{
				strcat(all_custom_flags, "-Wconversion ");
			}
			if (Wpedantic_flag)
			{
				strcat(all_custom_flags, "-Wpedantic ");
			}
			if (Wshadow_flag)
			{
				strcat(all_custom_flags, "-Wshadow ");
			}
			if (Werror_flag)
			{
				strcat(all_custom_flags, "-Werror ");
			}
			if (C99_flag)
			{
				strcat(all_custom_flags, "-std=c99 ");
			}

			mem_needed_all_c_flags = 1 + snprintf(NULL, 0, "%s ", all_custom_flags);
		}

		int mem_needed_output_flags = snprintf(NULL, 0, "%s", flags_string_base);
		mem_needed_output_flags++;
		total_flags_size += mem_needed_output_flags;
		mem_needed += mem_needed_all_c_flags;
		mem_needed += total_flags_size;
		char flags_string[mem_needed_output_flags];
		snprintf(flags_string, (size_t)mem_needed_output_flags, "%s", flags_string_base);

		/* TODO craft cmd */

		char source_files[mem_needed_src];
		snprintf(source_files, (size_t)mem_needed_src, src_files_template, SRC_NYT_WORDS, SRC_ALL_WORDS, SRC_COM_WORDS, cmd_parsing, configp, parsing, main_fp);

		char safe_cmd[mem_needed];

		snprintf(safe_cmd, (size_t)mem_needed, "%s%s%s %s", compiler, source_files, flags_string, all_custom_flags);

		if (verbose)
		{
			printf("%s", safe_cmd);
		}

		system(safe_cmd);
	}
	return 0;
}

/*
 * We are replacing this entire thing.. 

OBJ_ALL_WORDS_FP = $(ALL_WORDS_FILE_PATH).o
OBJ_COM_WORDS_FP = $(COM_WORDS_FILE_PATH).o
OBJ_NYT_WORDS_FP = $(NYT_WORDS_FILE_PATH).o

PARSING_SRC_FILE_PATH = $(PARSING_FILE_PATH).c
CONFIG_SRC_FILE_PATH = $(CONFIG_FILE_PATH).c
MAIN_SRC_FILE_PATH = $(MAIN_FILE_PATH).c
CMDPARS_SRC_FILE_PATH = $(CMDPARS_FILE_PATH).c

PARSING_OBJ_FILE_PATH = $(PARSING_FILE_PATH).o
CONFIG_OBJ_FILE_PATH = $(CONFIG_FILE_PATH).o
MAIN_OBJ_FILE_PATH = $(MAIN_FILE_PATH).o
CMDPARS_OBJ_FILE_PATH = $(CMDPARS_FILE_PATH).o

BASE_SRC_FILES = $(MAIN_SRC_FILE_PATH) $(CONFIG_SRC_FILE_PATH) $(PARSING_SRC_FILE_PATH) $(CMDPARS_SRC_FILE_PATH)
WORD_SRC_FILES = $(SRC_NYT_WORDS) $(SRC_ALL_WORDS) $(SRC_COM_WORDS)

OUT_ALL_OBJ_F = -c $(SRC_ALL_WORDS) -o $(OBJ_ALL_WORDS_FP) 
OUT_COM_OBJ_F = -c $(SRC_COM_WORDS) -o $(OBJ_COM_WORDS_FP)
OUT_NYT_OBJ_F = -c $(SRC_NYT_WORDS) -o $(OBJ_NYT_WORDS_FP) 

LINK_WORD_OBJ_FP = $(OBJ_ALL_WORDS_FP) $(OBJ_COM_WORDS_FP) $(OBJ_NYT_WORDS_FP)
BASE_OBJ_FILES_FP = $(CMDPARS_OBJ_FILE_PATH) $(MAIN_OBJ_FILE_PATH) $(CONFIG_OBJ_FILE_PATH) $(PARSING_OBJ_FILE_PATH)

OUT_BIN_NAME = binary

OUT = -o $(OUT_BIN_NAME)

all:
	$(ZIG) $(OUT_ALL_OBJ_F) $(FLAGS)
	$(ZIG) $(OUT_COM_OBJ_F) $(FLAGS)
	$(ZIG) $(OUT_NYT_OBJ_F) $(FLAGS)
	$(ZIG) -c $(PARSING_SRC_FILE_PATH) -o $(CMDPARS_OBJ_FILE_PATH) $(FLAGS)
	$(ZIG) -c $(CONFIG_SRC_FILE_PATH) -o $(PARSING_OBJ_FILE_PATH) $(FLAGS)
	$(ZIG) -c $(MAIN_SRC_FILE_PATH) -o $(CONFIG_OBJ_FILE_PATH) $(FLAGS)
	$(ZIG) -c $(CMDPARS_SRC_FILE_PATH) -o $(MAIN_OBJ_FILE_PATH) $(FLAGS)

clean: 
	@rm $(OBJ_ALL_WORDS_FP)
	@rm $(OBJ_COM_WORDS_FP)
	@rm $(OBJ_NYT_WORDS_FP)

base: 
	$(ZIG) $(BASE_SRC_FILES) $(WORD_SRC_FILES) $(OUT) $(FLAGS) -Werror

zig: 
	$(ZIG) $(BASE_SRC_FILES) $(WORD_SRC_FILES) $(OUT) $(FLAGS)

gcc:
	gcc $(BASE_SRC_FILES) $(WORD_SRC_FILES) $(OUT) $(FLAGS)

clang:
	clang $(BASE_SRC_FILES) $(WORD_SRC_FILES) $(OUT) $(FLAGS)

linux: gcc
	
android: gcc
	chmod u+x $(OUT_BIN_NAME)
	cp $(OUT_BIN_NAME) ~
	@echo "Binary file was copied to your home directory"
	@echo "execute it with ~/$(OUT_BIN_NAME)"

link:
	$(ZIG) $(BASE_OBJ_FILES_FP) $(LINK_WORD_OBJ_FP) $(OUT) $(FLAGS)
	*/
