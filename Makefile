CC := gcc
# CC := clang
# CC := zig cc

binary_file = wordle

WORD_DIR := src/word-lists

# printing
# found at /src/printing/*
libs_filenames := ctype compare 
LIBS := $(addprefix src/libs/, $(libs_filenames))
LIBS_FP := $(addsuffix .c, $(LIBS))

# printing
# found at /src/printing/*
printing_filenames := table verbose 
PRINTING := $(addprefix src/printing/, $(printing_filenames))
PRINTING_FP := $(addsuffix .c, $(PRINTING))

# found at /src/*.c
src_filenames := command_parsing config errors file_reading functions list_matching main parsing validate

# memory management
# found at /src/memory/*
mem_filenames := buffers checks
MEMORY := $(addprefix src/memory/, $(mem_filenames))
MEMORY_FP := $(addsuffix .c, $(MEMORY))


# files under src/ (directly no recursive)
FILES := $(addprefix src/, $(src_filenames))
SRC_FP := $(addsuffix .c, $(FILES)) 

ALL_FP = $(SRC_FP) $(PRINTING_FP) $(MEMORY_FP) $(LIBS_FP)

ALL_FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow -Wswitch-enum
OUT = -o $(binary_file)

wordle:
	$(CC) $(ALL_FP) $(OUT) -O2

install: wordle
	sudo cp -f $(binary_file) /usr/bin/

# used for the base and base-e recipes
all_flags_cmd = $(CC) $(OUT) $(ALL_FLAGS)

all: base-e
base-e:
	$(all_flags_cmd) $(ALL_FP) 

base:
	$(all_flags_cmd) $(ALL_FP)  -Werror -g

print:
	$(all_flags_cmd) $(PRINTING_FP)

mem:
	$(all_flags_cmd) $(MEMORY_FP)

android: wordle
	cp -f $(binary_file) ~
	chmod u+x ~/$(binary_file)
	@echo "The \"$(binary_file)\" file was copied to your home directory"
	@echo "execute it with ~/$(binary_file)"
