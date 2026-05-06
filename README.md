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


There is no limit to the amount of flags one can use.  
