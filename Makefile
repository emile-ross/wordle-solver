FLAGS = -Wall -Wextra -pedantic -std=c99
ZIG = zig cc
CMD = src/main.c src/words.c src/config.c -o binary

base: 
	$(ZIG) $(CMD) $(FLAGS) -Werror

zig: 
	$(ZIG) $(CMD) $(FLAGS)

gcc:
	gcc $(CMD) $(FLAGS)

clang:
	clang $(CMD) $(FLAGS)


linux: gcc

macos: clang

windows: 
	@echo "No."
