#!/bin/sh
#this script tests single command arguments

echo "This file should run inside the rshell directory"
echo
./bin/rshell<<EOF
echo Running program
mkdir newdir
ls
echo hello
echo world
pwd
rm -rf newdir
ls -a
exit
EOF
echo

