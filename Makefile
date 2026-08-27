# chose your compiler

CC := gcc
# CC := clang
# CC := zig cc

binary_file = wordle

WORD_DIR := src/word-lists

src_filenames := buffers command_parsing config drawing errors functions list_matching main parsing checks printing validate file_reading

FILES := $(addprefix src/, $(src_filenames))
SRC_FILES := $(addsuffix .c, $(FILES))

ALL_FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow -Wswitch-enum
OUT = -o $(binary_file)

wordle:
	$(CC) $(SRC_FILES) $(OUT) -O2

install: wordle
	sudo cp -f $(binary_file) /usr/bin/

# used for the base and base-e recipes
all_flags_cmd = $(CC) $(SRC_FILES) $(OUT) $(ALL_FLAGS)

base-e:
	$(all_flags_cmd)

base:
	$(all_flags_cmd) -Werror -g

android: wordle
	cp -f $(binary_file) ~
	chmod u+x ~/$(binary_file)
	@echo "The \"$(binary_file)\" file was copied to your home directory"
	@echo "execute it with ~/$(binary_file)"
