# wordle

This is a wordle solver engine

## Download and compile

```sh
git clone https://github.com/imawsumm/wordle
make base
```

## Usage

The program currently only accepts the "-s" flag (strict)

example command:
```sh
./binary -s A 1 -s D 2
```
the following command will search for all words with the following characteristics:
- first letter is A
- second letter is D

There is no limit to the amount of flags one can use but more than 5 would be useless with the current features 
