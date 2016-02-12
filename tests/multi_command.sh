Script started on Fri 12 Feb 2016 03:08:39 AM PST
]0;tphan022@hammer:~/rshell/tests[?1034h[tphan022@hammer tests]$ exit/home/csmajs/tphan022/rshell/bin/rshell
<tphan022@hammer.cs.ucr.edu>$ ls; pwd
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ echo hello && echo world
hello
world
<tphan022@hammer.cs.ucr.edu>$ echo hello || echo cats
hello
<tphan022@hammer.cs.ucr.edu>$ echo hello # echo world; ls && pwd
hello
<tphan022@hammer.cs.ucr.edu>$ meow || ls -a
Error in execution! : No such file or directory
.  ..  commented_command.sh  exit.sh  multi_command.sh	single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls&&pwd
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ ls -a; echo this works!
.  ..  commented_command.sh  exit.sh  multi_command.sh	single_command.sh
this works!
<tphan022@hammer.cs.ucr.edu>$ pwd||echo this shouldnt print
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ echo he; llo#echo world
hello#echo world
<tphan022@hammer.cs.ucr.edu>$ mkdir testdir; ls -a; && pwd || ls
.  ..  commented_command.sh  exit.sh  multi_command.sh	single_command.sh  testdir
Error in execution! : No such file or directory
commented_command.sh  exit.sh  multi_command.sh  single_command.sh  testdir
<tphan022@hammer.cs.ucr.edu>$ rm -rf testdir && echo directory removed || echo moo
directory removed
<tphan022@hammer.cs.ucr.edu>$ exit
Program Exited.
]0;tphan022@hammer:~/rshell/tests[tphan022@hammer tests]$ exit
exit

Script done on Fri 12 Feb 2016 03:16:19 AM PST
