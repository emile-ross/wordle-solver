cond := $(wildcard build)
C = ./build
W = wordle
BCMD = build.c -o build

bin:
ifeq ($(cond),)
	@gcc $(BCMD)
endif

wordle: bin
	@$(C) G

base:
	zig cc $(BCMD) -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
	$(C) Z B e

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
