Script started on Fri 12 Feb 2016 01:26:19 AM PST
]0;tphan022@hammer:~/rshell/tests[?1034h[tphan022@hammer tests]$ /home/csmajs/tphan022/rshell/bin/rshell
<tphan022@hammer.cs.ucr.edu>$ pwd
/home/csmajs/tphan022/rshell/tests
<tphan022@hammer.cs.ucr.edu>$ mkdir newdir'
mkdir: cannot create directory `newdir': File exists
<tphan022@hammer.cs.ucr.edu>$ ls -a
.  ..  commented_command.sh  exit.sh  multi_command.sh	newdir	single_command.sh
<tphan022@hammer.cs.ucr.edu>$ echo hello
hello
<tphan022@hammer.cs.ucr.edu>$ meow
Error in execution! : No such file or directory
<tphan022@hammer.cs.ucr.edu>$ vim rm -rf newdir
<tphan022@hammer.cs.ucr.edu>$ ls -a
.  ..  commented_command.sh  exit.sh  multi_command.sh	single_command.sh
<tphan022@hammer.cs.ucr.edu>$ exit
Program Exited.
]0;tphan022@hammer:~/rshell/tests[tphan022@hammer tests]$ exit
exit

Script done on Fri 12 Feb 2016 01:31:41 AM PST
