#!/usr/bin/sh

# execute command & check for memory leaks
#
#
filename=$(date --iso-8601="minutes")
valgrind --leak-check=full --log-file=$filename ./wordle -s A 1 -w all -s l 2



