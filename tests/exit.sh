#!/bin/sh
#this tests the exit command.

echo "Run this within the rshell directory"
echo
./bin/rshell<<EOF
echo first case:
echo hello || exit
echo second case:
meow_meow && exit
echo third case:
ls -a; pwd && echo Goodbye! && exit
EOF
echo
