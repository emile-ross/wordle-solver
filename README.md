# wordle

This is a wordle solver engine

## Download and compile

```sh
git clone https://github.com/imawsumm/wordle
make base
```

## Usage

The wordle engine currently accepts 4 different flags:

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



example command:
```sh
./binary -s A 1 -s D 2
```
the following command will search for all words with the following characteristics:
- first letter is A
- second letter is D

There is no limit to the amount of flags one can use but more than 5 would be useless with the current features 
