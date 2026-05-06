build_bin := $(wildcard build)
FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
ZIG = zig cc
build_bin_cmd = gcc build.c -o build $(FLAGS)
build_compat_cmd = clang build.c -o build

bin-c:

ifeq ($(build_bin),)
	@$(build_compat_cmd)
endif

bin:

ifeq ($(build_bin),)
	@$(build_bin_cmd)
endif

base: bin
	@./build Z a 9 p x c

macos: bin-c
	@./build G a 9 p x c

windows: 
	@echo "No."
