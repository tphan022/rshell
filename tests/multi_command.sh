#!/bin/sh
#this script tests multiple commands ran in conjuction.

echo run the from the rshell directory
echo
./bin/rshell<<EOF
echo first case:
ls -a && pwd
echo second case:
ls -a&&pwd
echo third case:
mkdir newdir; ls -a || echo hello!
echo fourth case:
echo removing newdir && rm -rf newdir && ls -a;
echo fifth case:
echo "ls -a && pwd"
echo sixth case:
pwd # echo hello world! && ls
echo seventh case:
pwd #echo this shouldn't print
echo eighth case:
meow_meow || ls -a && pwd
exit
EOF
echo
