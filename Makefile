build_bin := $(wildcard build)
B = build
W = wordle
FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
ZIG = zig cc
GCC = gcc
CLANG = clang
build_bin_cmd = build.c -o build

bin-g:

ifeq ($(build_bin),)
	@$(GCC) $(build_bin_cmd)
endif

bin-c:

ifeq ($(build_bin),)
	@$(CLANG) $(build_bin_cmd)
endif

bin-z:

ifeq ($(build_bin),)
	@$(ZIG) $(build_bin_cmd) $(FLAGS)
endif

wordle: bin-g
	@./build G a

base: bin-z
	@./build Z a 9 p x c

macos: bin-c
	@./build C

android: bin-g
	@cp -f $(B) ~
	chmod u+x ~/$(B)
	@~/$(B) G a
	cp -f $(W) ~
	chmod u+x ~/$(W)
	@echo "The \"wordle\" file was copied to your home directory"
	@echo "execute it with ~/$(W)"

windows: 
	@echo "No."
