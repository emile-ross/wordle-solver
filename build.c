#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *ALL_FLAGS = "-Wall -Wextra -Wpedantic -std=c99 -Wconversion";
char *ZIG = "zig cc";

#define fp_size 32

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

int main(int argc, char *argv[])
{
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

	char cmd[512];
	/* hard coded command to compile */
	snprintf(cmd, sizeof(cmd),
			"zig cc src/main.c src/config.c src/parsing.c src/command-parsing.c src/word-lists/words.c src/word-lists/all-words.c src/word-lists/common-words.c -o binary %s"
			, ALL_FLAGS);
	system(cmd);

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

macos: clang

windows: 
	@echo "No."

# Linking the word list files but still compiling the BASE_SRC_FILES
main: 
	$(ZIG) $(BASE_SRC_FILES) $(LINK_WORD_OBJ_FP) $(OUT) $(FLAGS) -Werror

main-e: 
	$(ZIG) $(BASE_SRC_FILES) $(LINK_WORD_OBJ_FP) $(OUT) $(FLAGS)

link:
	$(ZIG) $(BASE_OBJ_FILES_FP) $(LINK_WORD_OBJ_FP) $(OUT) $(FLAGS)
	*/
