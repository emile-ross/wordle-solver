cond := $(wildcard build)
C = ./build
W = wordle
BCMD = build.c -o build

WORD_DIR := src/word-lists
w_list_filenames := en_nyt_words en_all_words en_common_words fr_all_words la_all_words la_com_words

WORD_LIST_FILES := $(addprefix $(WORD_DIR)/, $(w_list_filenames))
WORD_LISTS := $(addsuffix .c, $(WORD_LIST_FILES))

SOURCE_DIR := src
src_filenames := command_parsing config drawing errors functions list_matching main parsing printing validate file_reading

FILES := $(addprefix $(SOURCE_DIR)/, $(src_filenames))
SRC_FILES := $(addsuffix .c, $(FILES))

ALL_FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
OUT = -o wordle

bin:
ifeq ($(cond),)
	@gcc $(BCMD)
endif

wordle: bin
	@$(C) G

base:
	zig cc $(BCMD) $(OUT) $(ALL_FLAGS) -Werror
	zig cc $(SRC_FILES) $(WORD_LISTS) $(OUT) $(ALL_FLAGS) -Werror

macos: bin
	@$(C) C

android: bin
	@cp -f build ~
	chmod u+x ~/build
	@~/build G a
	cp -f $(W) ~
	chmod u+x ~/$(W)
	@echo "The \"$(W)\" file was copied to your home directory"
	@echo "execute it with ~/$(W)"


