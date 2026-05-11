cond := $(wildcard build)
B = build
C = ./$(B)
W = wordle
FG = -Wall -Wextra -Wpedantic -std=c99 -Wconversion -Wshadow
BCMD = $(B).c -o $(B)

bin:

ifeq ($(cond),)
	@gcc $(BCMD)
endif

wordle: bin
	@$(C) G a

base:
	zig cc $(BCMD) $(FG)
	$(C) Z a 9 p x c s e

macos: bin
	@$(C) C

android: bin
	@cp -f $(B) ~
	chmod u+x ~/$(B)
	@~/$(B) G a
	cp -f $(W) ~
	chmod u+x ~/$(W)
	@echo "The \"$(W)\" file was copied to your home directory"
	@echo "execute it with ~/$(W)"

windows: 
	@echo "No."
