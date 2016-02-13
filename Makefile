# This is the makefile for the rshell
#

flags= -Wall -Werror -ansi -pedantic

all :
	if [ ! -d bin ]; then mkdir ./bin; fi
	g++ $(flags) src/main.cpp -o bin/rshell

rshell:
	g++ $(flags) src/main.cpp -o bin/rshell
