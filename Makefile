build_bin := $(wildcard build)
FLAGS = -Wall -Wextra -Wpedantic -std=c99 -Wconversion
ZIG = zig cc
build_bin_cmd = gcc build.c -o build
build_mac_cmd = clang build.c -o build

bin-c:

ifeq ($(build_bin),)
	@$(build_mac_cmd)
endif

bin:

ifeq ($(build_bin),)
	@$(build_bin_cmd)
endif

base: bin
	@./build

macos: bin-c
	@./build

windows: 
	@echo "No."
