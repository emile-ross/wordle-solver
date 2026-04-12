FLAGS = -Wall -Wextra -pedantic -std=c99
ZIG = zig cc
COMPILE_CMD = src/main.c src/words.c src/config.c -o binary

base: 
	$(ZIG) $(COMPILE_CMD) $(FLAGS) -Werror

zig: 
	$(ZIG) $(COMPILE_CMD) $(FLAGS)

gcc:
	gcc $(COMPILE_CMD) $(FLAGS)

clang:
	clang $(COMPILE_CMD) $(FLAGS)

macos: clang
	@# "make macos" redirects to "make clang"

linux: gcc
	@# "make linux" redirects to "make gcc"
