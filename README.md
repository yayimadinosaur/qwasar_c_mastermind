# Welcome to My Mastermind

## Task
SPECIFICATIONS
Write a program called mastermind; it will be an implementation of the famous game.

NAME
my_mastermind

SYNOPSIS
my_mastermind [-ct]

DESCRIPTION
Mastermind is a game composed of 8 pieces of different colors.
A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code.
After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.

If the player finds the code, he wins, and the game stops.
A misplaced piece is a piece that is present in the secret code butthat is not in a good position.

You must read the player's input from the standard input.

Your program will also receive the following parameters:
-c [CODE]: specifies the secret code. If no code is specified, a random code will be generated.
-t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.

## Description
The problem was solved by the following steps:
1)  parse user input via command line arguments
2)  check arguments if there are any
3)  start the game by taking user input via the command line
4)  compare user input to randomly generated code or user specified code
5)  print round and results to user
6)  repeat until rounds reach 0 or user exits program

## Installation
GCC - compiler to compile C file + header file
[Makefile options]
make - to start the Makefile to create an executable
make clean - to delete all object files
make fclean - to delete all object files and executable
make re - to delete all object files and executable, recompile executable

## Usage
./my_mastermind flag1 flag1param flag2 flag2param
flag1 and flag2 options:
-t attempts
-c code
flag1param options:
number greater than 0
flag2param options:
4 numbers, 0 - 8
i.e. 1235
example of usage:
./my_mastermind -t 9 -c 1954

### The Core Team
fung_w

<span><i>Made at <a href='https://qwasar.io'>Qwasar Silicon Valley</a></i></span>
<span><img alt='Qwasar Silicon Valley Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
