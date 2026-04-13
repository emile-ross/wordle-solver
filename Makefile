FG = -Wall -Wextra -pedantic -std=c99
ZIG = zig cc
CMD = src/main.c src/words.c src/config.c src/common-words -o binary

base: 
	$(ZIG) $(CMD) $(FLAGS) -Werror

zig: 
	$(ZIG) $(CMD) $(FG)

gcc:
	gcc $(CMD) $(FG)

clang:
	clang $(CMD) $(FG)


linux: gcc

macos: clang

windows: 
	@echo "No."
