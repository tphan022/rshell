# rshell
## Overview
In this project, we built a simple command shell that processes inputs and executes them.

This shell is able to handle connectors and correctly runs each command whether it is a single argument like `ls`, or has parameters such as `ls -a`. 

The connectors that are usable with this shell include `||`, `&&`, `;`, and `#`.

To execute a command, user must type:

    command = executable [ argumentList ] [ connector cmd ]
    connector = || or && or ;

It does not have to strictly follow this format format. The user can type it in any combination as long as executables are not stuck together without a connector.

## Connectors
The OR connector, denoted by `||`, will connect two arguments and OR them, meaning it will run the first argument and then run the second argument only if the first one failed. For example: 

    mkdir newdirectory || ls

will create the directory called newdirectory but will not run ls since the first command succeeded. However, when running the arguments:

    meowmeow || ls

ls will run since meowmeow is not a valid command.

The AND connector is similar to the OR connector, but will run the second command only when the first one **succeeds**.

    echo hello && echo world
    meow && echo woof

In this case the shell would output `hello world` while the second part will throw an error code and not echo woof since the first instance failed.

The semicolon will run the next command regardless of whether the first once succeeded or not.

    ls; pwd
    meow; pwd

In both instances, pwd would run, since it ignores the successfulness of the first argument.

Anything that appears after a # will be considered a COMMENT, meaning `echo ILIKEPIZZA; # echo ILIKEPIE` will echo ILIKEPIZZA but will not echo ILIKEPIE because everything after # is ignored by the shell.

## BuiltIns
The first built in is `exit`, which will exit the program. This command can be chained using the connectors also.

The second built in is the test command, which, depending on the flag, will check if the file/directory exists. `-e` and no flag will check if the target is a file **OR** directory. `-f` will check if the target is a regular file. `-d` will check if the target is a directory. 

The test case has several ways of implementations:

    test main.cpp
    test -e main.cpp
    [ main.cpp ]
    [ -e main.cpp ]

`-e` can be replaced with the other two flags and the brackets **need** to have spacing between the arguments otherwise the command breaks.

## Bugs
1. A current bug is that # will only work if it is not connected to any argument so that:

    echo hello; # echo world

will print only hello while

    echo hello; #echo world

will break the command argument and try to unsuccessfully register `#echo` as an argument in the shell.

2. A limitation we have for our command shell is that pressing the up and down arrow will not bring up the previous inputs.

3. There are also no redirection commands such as:

    cat oldFile.cpp >> newFile.cpp

4. Argument line can only take up to 1024 characters.

5. A large limitation is that our shell does not utilize and parse quotation marks correctly. So if you were to input the command:

    echo "ls -a && pwd"

the shell would echo `"ls-a` and then be unable to find the command `pwd"`.

6. The test command using the brackets will work even if the end bracket is missing: `[ -f src/main.cpp `.

