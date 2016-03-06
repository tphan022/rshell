#!/bin/sh
#this script tests precedence.

echo "run this within the rshell directory"
echo
./bin/rshell<<EOF
echo tests for precedence
(echo A && echo B)
(echo A) && (echo B)
echo and connector b/w precedence
(echo A && echo B) && (echo C && echo D)
echo or connector b/w precedence
(echo A && echo B) || (echo C && echo D)
echo testing (echo A || echo B) && (echo C || echo D)
(echo A || echo B) && (echo C || echo D)
echo testing multiple commands within precedence
(echo A && echo B && echo C && echo D) && (echo e || echo f)
(echo A || echo B && echo C) || (echo D && echo e) && (echo F && echo g)
exit
EOF
echo
