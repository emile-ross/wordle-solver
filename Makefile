cond := $(wildcard build)
C = ./build
W = wordle
FG = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
BCMD = build.c -o build

bin:

ifeq ($(cond),)
	@gcc $(BCMD)
endif

wordle: bin
	@$(C) G a

base:
	zig cc $(BCMD) $(FG)
	$(C) Z B

macos: bin
	@$(C) C

android: bin
	@cp -f build ~
	chmod u+x ~/build
	@~/build G a
	cp -f $(W) ~
	chmod u+x ~/$(W)
	@echo "The \"$(W)\" file was copied to your home directory"
	@echo "execute it with ~/$(W)"

windows: 
	@$(C) W
