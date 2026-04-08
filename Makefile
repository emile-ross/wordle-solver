USER_FLAGS = -Wall
FLAGS = -Wall -Wextra -pedantic -std=c99

COMPILE_CMD = zig cc src/main.c src/words.c -o binary

base: 
	$(COMPILE_CMD) $(ZIG_FLAGS)

full: 
	$(COMPILE_CMD) $(ZIG_FLAGS) -Werror
