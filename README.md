# wordle cheat

This is a wordle solver engine

It finds all words matching your criterias (see [examples](#example-commands))

## Download and compile

```sh
git clone https://github.com/imawsumm/wordle
make wordle
```

## Usage

[Skip to examples](#example-commands)

The wordle engine accepts 4 different flags:

## Wordle solving

### ``--strict``

Use this flag if letter is at the correct position.  (the letter is green)  
Specify the letter and it's position.  

``-s [LETTER] [POSITION]``

### ``--exclude``

Use this flag if the letter is not in the word at (x) position.  (the letter is yellow)
The flag can be used to tell the program the letter isn't at a specific position.  Use it to specify you got a yellow letter at (x) position.  

``-x [LETTER] [POSITION]``

### ``--includes``

Use this flag if the letter is in the word somewhere.  (the letter is yellow)

``-i [LETTER]``

### ``--absent``

Use this flag if the letter is not in the word.  (the letter is grey)

``-a [LETTER]``

## example commands:

### simple command
the following command will search for all words with the following characteristics:
- first letter is A (-s A 1)
- second letter is D (-s D 2)
```sh
./wordle -s A 1 -s D 2
```

### complex command
This command searches for all words following these characteristics:
- first letter is A (-s A 1)
- the letter D is somewhere in the word (-i D)
- there isn't the letter D at the third position (-x D 3)
- the letter Z is not in this word (-a Z)

```sh
./wordle -s A 1 -i D -x D 3 -a Z
```

# real scenario

Lets say you typed "K I T T Y" as your first guess for the wordle.  If the K in KITTY is green and the Y is yellow, you can narrow the answer to a single word with this information.  
Since K was green and it was the first letter, you can use the flag ``-s K 1``

## Word validation

### ``--validate``
The ``-v`` flag can be used in order to check if a word exists.  

The ``-v`` flag takes in the word to lookup directly from the command

example command:
```sh
./wordle -v share
```
This command would check if the word "share" can be found in the New-York Times word list, the common word list and the "all words" list

The program will then display a message for each word list it can be found in.  
There is no limit to the amount of flags one can use.  

## Drawing

For drawing you can use the ``-d`` flag
It will provide the user with every word they can use in order to make a staircase with valid (green) letters


## word lists
This program includes several word lists:

### all words

The ``all_words`` list includes a list of [all english words](https://raw.githubusercontent.com/ImAwsumm/wordle/refs/heads/main/src/word-lists/all_words.c) including some that may be valid only in certain parts of the world.  
The ``-w all`` flag specifies the ``all_words`` list.  

### common words
The ``common_words`` list is a list of the most [common 5 letter words](https://raw.githubusercontent.com/ImAwsumm/wordle/refs/heads/main/src/word-lists/common_words.c).  It is shorter than the ``all_words`` list while being longer than the ``myt_words`` list.  
The ``-w common`` flag specifies the ``common_words`` list.  

### New York Times words

The ``nyt_words`` list is a list of all possible [New York Times answers](https://raw.githubusercontent.com/ImAwsumm/wordle/refs/heads/main/src/word-lists/nyt_words.c).  
This the default word list the program will use whenever you don't specify a word list.  
The ``-w nyt`` flag specifies the ``nyt_words`` list.  

### all french words

The ``fr_all_words`` list is a list of [all 5 letter french words](https://raw.githubusercontent.com/ImAwsumm/wordle/refs/heads/main/src/word-lists/fr_all_words.c).  The ``-w fr`` flag specifies the french word list.  
