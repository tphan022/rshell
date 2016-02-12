Script started on Fri 12 Feb 2016 01:41:52 AM PST
]0;tphan022@hammer:~/rshell/tests[?1034h[tphan022@hammer tests]$ /home/csmajs/tphan022/rshell/bin/rshell
<tphan022@hammer.cs.ucr.edu>$ echo hello
hello
<tphan022@hammer.cs.ucr.edu>$ echo hello && world
hello 
Error in execution! : No such file or directory
<tphan022@hammer.cs.ucr.edu>$ echo hello && echo world
hello 
Error in execution! : No such file or directory
<tphan022@hammer.cs.ucr.edu>$ echo heelo   llo&&echo world
hello
world
<tphan022@hammer.cs.ucr.edu>$ ls -a; pwd
.  ..  commented_command.sh  exit.sh  multi_command.sh	single_command.sh
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ meow || ls
Error in execution! : No such file or directory
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls && pwd
ls: cannot access : No such file or directory
<tphan022@hammer.cs.ucr.edu>$ ls || pwd
ls: cannot access : No such file or directory
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ ls
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls||pwd
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls;  ; ls || ls
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
ls: cannot access : No such file or directory
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls||pwd
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls
commented_command.sh  exit.sh  multi_command.sh  single_command.sh
<tphan022@hammer.cs.ucr.edu>$ ls || pwd
ls: cannot access : No such file or directory
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ exit
Program Exited.
]0;tphan022@hammer:~/rshell/tests[tphan022@hammer tests]$ exit
exit

Script done on Fri 12 Feb 2016 01:52:29 AM PST
