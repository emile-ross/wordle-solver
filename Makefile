USER_FLAGS = -Wall
FLAGS = -Wall -Wextra -pedantic -std=c99
ZIG = zig cc
COMPILE_CMD = src/main.c src/words.c src/config.c -o binary

base: 
	$(ZIG) $(COMPILE_CMD) $(FLAGS)

full: 
	$(ZIG) $(COMPILE_CMD) $(FLAGS) -Werror

gcc:
	gcc $(COMPILE_CMD) $(FLAGS)
