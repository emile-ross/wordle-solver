FLAGS = -Wall -Wextra -pedantic -std=c99
ZIG = zig cc

PARSING_FILE_PATH = src/parsing.c
CONFIG_FILE_PATH = src/config.c
MAIN_FILE_PATH = src/main.c
CMDPARS_FILE_PATH = src/command-parsing.c

BASE_ALL_WORDS_FILE_PATH = src/all-words
BASE_COM_WORDS_FILE_PATH = src/common-words
BASE_NYT_WORDS_FILE_PATH = src/words

SRC_ALL_WORDS = $(BASE_ALL_WORDS_FILE_PATH).c
SRC_COM_WORDS = $(BASE_COM_WORDS_FILE_PATH).c
SRC_NYT_WORDS = $(BASE_NYT_WORDS_FILE_PATH).c

OBJ_ALL_WORDS_FP = $(BASE_ALL_WORDS_FILE_PATH).o
OBJ_COM_WORDS_FP = $(BASE_COM_WORDS_FILE_PATH).o
OBJ_NYT_WORDS_FP = $(BASE_NYT_WORDS_FILE_PATH).o

BASE_SRC_FILES = $(MAIN_FILE_PATH) $(CONFIG_FILE_PATH) $(PARSING_FILE_PATH) $(CMDPARS_FILE_PATH)
WORD_SRC_FILES = $(SRC_NYT_WORDS) $(SRC_ALL_WORDS) $(SRC_COM_WORDS)

OUT_ALL_OBJ_F = -c $(SRC_ALL_WORDS) -o $(OBJ_ALL_WORDS_FP) 
OUT_COM_OBJ_F = -c $(SRC_COM_WORDS) -o $(OBJ_COM_WORDS_FP)
OUT_NYT_OBJ_F = -c $(SRC_NYT_WORDS) -o $(OBJ_NYT_WORDS_FP) 

LINK_WORD_OBJ_FP = $(OBJ_ALL_WORDS_FP) $(OBJ_COM_WORDS_FP) $(OBJ_NYT_WORDS_FP)

OUT_BIN_NAME = binary

OUT = -o $(OUT_BIN_NAME)

all:
	$(ZIG) $(OUT_ALL_OBJ_F) $(FLAGS)
	$(ZIG) $(OUT_COM_OBJ_F) $(FLAGS)
	$(ZIG) $(OUT_NYT_OBJ_F) $(FLAGS)

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

main: 
	$(ZIG) $(LINK_WORD_OBJ_FP) $(BASE_SRC_FILES) $(OUT) $(FLAGS) -Werror

main-e: 
	$(ZIG) $(LINK_WORD_OBJ_FP) $(BASE_SRC_FILES) $(OUT) $(FLAGS)
