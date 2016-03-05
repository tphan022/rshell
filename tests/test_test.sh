#!/bin/sh
#this script tests the test command including brackets

echo "This file should run inside the rshell directory"
echo
./bin/rshell<<EOF
touch newfile
mkdir newdir
echo test newfile
test newfile
echo test newdir
test newdir
echo testing -e
test -e newfile
test -e new dir
echo testing -f
test -f newfile
test -f newdir
echo testing -d
test -d newfile
test -d newdir
echo testing brackets
[ -d newdir ] 
[ -f newfile ] 
echo testing connectors
[ newfile ] && echo hello world
[ newdir ] || echo do not output
rm -rf newfile
rm -rf newdir
exit
EOF
echo
