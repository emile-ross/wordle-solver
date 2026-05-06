cond := $(wildcard build)
B = build
W = wordle
FG = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
ZIG = zig cc
GCC = gcc
CLANG = clang
BCMD = build.c -o build

bin-g:

ifeq ($(cond),)
	@$(GCC) $(BCMD)
endif

bin-c:

ifeq ($(cond),)
	@$(CLANG) $(BCMD)
endif

wordle: bin-g
	@./build G a

base:
	$(ZIG) $(BCMD) $(FG)
	./build Z a 9 p x c

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
