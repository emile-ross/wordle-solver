#!/usr/bin/sh

# execute command & check for memory leaks
#
valgrind --leak-check=full ./wordle


