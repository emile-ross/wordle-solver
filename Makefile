# chose your compiler

CC := gcc
# CC := clang
# CC := zig cc

binary_file = wordle

WORD_DIR := src/word-lists
w_list_filenames := en_nyt_words en_all_words en_common_words fr_all_words la_all_words la_com_words

WORD_LIST_FILES := $(addprefix $(WORD_DIR)/, $(w_list_filenames))
WORD_LISTS := $(addsuffix .c, $(WORD_LIST_FILES))

SOURCE_DIR := src
src_filenames := command_parsing config drawing errors functions list_matching main parsing printing validate file_reading

FILES := $(addprefix $(SOURCE_DIR)/, $(src_filenames))
SRC_FILES := $(addsuffix .c, $(FILES))

ALL_FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
OUT = -o $(binary_file)

macos: wordle
wordle:
	$(CC) $(SRC_FILES) $(WORD_LISTS) $(OUT) -O2

all_flags_cmd = $(CC) $(SRC_FILES) $(WORD_LISTS) $(OUT) $(ALL_FLAGS)

base-e:
	$(all_flags_cmd) -g

base:
	$(all_flags_cmd) -Werror -g

android: wordle
	cp -f $(binary_file) ~
	chmod u+x ~/$(binary_file)
	@echo "The \"$(binary_file)\" file was copied to your home directory"
	@echo "execute it with ~/$(binary_file)"


