# TicTacToe
A simple Tic-Tac-Toe game (Human vs AI).  

## Requirement
I tested the following environment.  
- GNU Make 3.81
- gcc 12.2.0

## Usage
### Build
```console
TicTacToe % make
gcc -Wall -o src/board.o -c src/board.c
gcc -Wall -o src/main.o -c src/main.c
gcc -Wall -o src/strategy.o -c src/strategy.c
gcc -Wall -o TicTacToe src/board.o src/main.o src/strategy.o
```

### Start the Game
```console
TicTacToe % ./TicTacToe 
TicTacToe version 1.00
https://github.com/kazumasa-kusaba/TicTacToe

Which do you play? (0: first, 1: second)
Input: 0
You are first, computer is second.
  012
 |---|
0|...|
1|...|
2|...|
 |---|
Where do you place?
Input Row: 0
Input Column: 0
  012
 |---|
0|O..|
1|...|
2|...|
 |---|
Computer ROW: 1, COLUMN: 1.
  012
 |---|
0|O..|
1|.X.|
2|...|
 |---|
Where do you place?
Input Row: 
~~ omitted ~~
  012
 |---|
0|OXO|
1|XXO|
2|OOX|
 |---|
Draw
```

