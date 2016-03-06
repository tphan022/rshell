#!/bin/sh
#this script tests comment cases.

echo "Run the within the rshell dir"
echo
./bin/rshell<<EOF
echo first case:
# ls -a && pwd
echo second case:
ls -a # ls; ls; ls; echo hello!
echo third case:
ls #echo hello world!
echo fourth case:
pwd#mkdir newdir
(echo A && echo B) # meow meow
(echo A # meow meow
exit
EOF
echo

