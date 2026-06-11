#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char *source_files_cmd(void);

#define compiler_name_len (8)
char *CLANG_COMPILER_NAME = "clang";
char *ZIG_COMPILER_NAME = "zig cc";
char *GCC_COMPILER_NAME = "gcc";

#define fp_size (32)
#define base_args (1)

#define num_src_files (16)
char *all_src_files[num_src_files] = 
{
	"src/command_parsing",
	"src/config",
	"src/drawing",
	"src/errors",
	"src/functions",
	"src/list_matching",
	"src/main",
	"src/parsing",
	"src/printing",
	"src/validate",
	"src/word-lists/all_words",
	"src/word-lists/common_words",
	"src/word-lists/fr_all_words",
	"src/word-lists/la_all_words",
	"src/word-lists/la_com_words",
	"src/word-lists/nyt_words",
};

#define num_base_src_files (10)
const char *source_files_base_path = "src/";
const char *source_files_ext = ".c";
char *source_files[num_base_src_files] = 
{
	"command_parsing",
	"config",
	"drawing",
	"errors",
	"functions",
	"list_matching",
	"main",
	"parsing",
	"printing",
	"validate",
};

#define num_word_lists (6)
const char *word_lists_base_path = "src/word-lists/";
const char *word_lists_file_ext = ".c";
char *word_lists[num_word_lists] = 
{
	"all_words",
	"common_words",
	"fr_all_words",
	"la_all_words",
	"la_com_words",
	"nyt_words",
};

char *src_file_extention = ".c";

typedef enum 
{
	CLANG,
	GCC,
	ZIG,
} compiler_enum;

compiler_enum compiler_choice;

int main(int argc, char *argv[])
{
	bool Wall_flag = false;
	bool Wextra_flag = false;
	bool Wconversion_flag = false;
	bool Wpedantic_flag = false;
	bool Werror_flag = false;
	bool C99_flag = false;
	bool Wshadow_flag = false;
	bool verbose = false; /* false by default */

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
			case 'W':
				/* Windows compilation is not supported. 
				 * I hardcoded forward slashes everywhere in here */
				printf("Windows compilation is not supported.\n");
				return 32;
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
			case 'v':
				verbose = true;
				break;
			case 'B':
				C99_flag = true;
				Wall_flag = true;
				Wconversion_flag = true;
				Wextra_flag = true;
				Wpedantic_flag = true;
				Wshadow_flag = true;
				verbose = true;
				num_flags += 6;
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
	}

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

	char *flags_string_base = "-o wordle";
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
			strcat(all_custom_flags, "-Wshadow -g ");
		}
		if (Werror_flag)
		{
			strcat(all_custom_flags, "-Werror ");
		}
		if (C99_flag)
		{
			strcat(all_custom_flags, "-std=c99 ");
		}
	}


	/*
	char *command_file_path = source_files_cmd();
	*/

	size_t mem_needed_output_flags = strlen(flags_string_base);
	mem_needed_output_flags++;
	char *flags_string = malloc(mem_needed_output_flags);
	snprintf(flags_string, (size_t)mem_needed_output_flags, "%s", flags_string_base);

	int full_cmp_size = 1; /* for the NULL terminator */
	int cmd_cmp_size[num_src_files];

	for (int i = 0; i < num_src_files; i++)
	{
		int temp_size = snprintf(NULL, 0, "%s.c ", all_src_files[i]);
		full_cmp_size += temp_size;
		cmd_cmp_size[i] = temp_size;
	}

	full_cmp_size += snprintf(NULL, 0, "%s ", compiler);
	full_cmp_size += snprintf(NULL, 0, "%s %s ", flags_string, all_custom_flags);

	char full_compilation_path[full_cmp_size];
	
	snprintf(full_compilation_path, (size_t)full_cmp_size, "%s ", compiler);

	for (int j = 0; j < num_src_files; j++)
	{
		size_t command_size = 1 + (size_t)cmd_cmp_size[j];

		char *temp_file_path = malloc(command_size);	/* allocate memory for temp_file_path */
		snprintf(temp_file_path, (size_t)command_size, "%s.c ", all_src_files[j]);
		strcat(full_compilation_path, temp_file_path);

		free(temp_file_path);	/* free after use */
	}

	/* concatenates the strings with a space in between them */
	strcat(full_compilation_path, flags_string);

	free(flags_string);	/* free after last flags_string use */

	/* if there are more than 0 flags,
	 * and verbose if false
	 * if verbose is false, it's still true if num_flags is greater than 1 */
	if (num_flags > 0 && ((verbose && num_flags > 1) || !verbose))
	{
		/* append space if there are flags */
		strcat(full_compilation_path, " ");
		strcat(full_compilation_path, all_custom_flags);
	}

	if (verbose) 
	{
		printf("%s\n", full_compilation_path);
	}
	system(full_compilation_path);

	return 0;
}



char *source_files_cmd(void)
{
	int num_total_src_files = num_src_files + num_word_lists;

	size_t full_string_size = 0;
	size_t base_word_list_path_size = strlen(word_lists_base_path);
	base_word_list_path_size += strlen(word_lists_file_ext);

	size_t base_src_path_size = strlen(source_files_base_path);
	base_src_path_size += strlen(source_files_ext);

	for (int i = 0; i < num_word_lists; i++)
	{
		size_t temp_path_size = base_word_list_path_size;
		temp_path_size += strlen(word_lists[i]);
		full_string_size += temp_path_size + 1; /* 1 is for the space */
	}

	for (int i = 0; i < num_base_src_files; i++)
	{
		size_t temp_path_size = base_src_path_size;
		temp_path_size += strlen(source_files[i]);
		full_string_size += temp_path_size + 1; /* 1 is for the space */
	}

	char *full_cmd_string = malloc(full_string_size);

	for (int i = 0; i < num_word_lists; i++)
	{
		strcat(full_cmd_string, word_lists_base_path);	/* add file path */
		strcat(full_cmd_string, word_lists[i]);		/* add file name */
		strcat(full_cmd_string, word_lists_file_ext);	/* add file extention */
		strcat(full_cmd_string, " ");	/* add space */
	}

	for (int i = 0; i < num_word_lists; i++)
	{
		strcat(full_cmd_string, source_files_base_path);	/* add file path */
		strcat(full_cmd_string, source_files[i]);		/* add file name */
		strcat(full_cmd_string, source_files_ext);	/* add file extention */
		strcat(full_cmd_string, " ");	/* add space */
	}

	printf("%s", full_cmd_string);

	return NULL;
}
