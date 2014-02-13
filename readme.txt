Name:Huang Zhu
Student #:15509094
------------------------

Assignment: [OS lab3] mini Shell program
----------


Description:
-----------
Use C++ to to make a mini shell which execute basic
system commands.

My assignment solution consists of the following files:
Shell.h
Shell.cpp
Shell-driver.cpp
makefile
readme.txt
Shell-driver

Running my solution:
-------------------
You can run my assignment as follows:
> make
> ./Shell-driver

Compiler:
------------
g++

Running procedure:
-----------------
Basically, you can do following tests:
1. Type basic system command(or with optional parameter) like: ls and ls -al.
2. You can run any program with absolute path. 
3. This program can deal with spaces in the command. You can test this too.

Assumptions:
-----------
Because I didn't implement cd. You can't use cd here.

Conclusions/Remarks:
-------------------
I had problem with convert between string and char*. But it works now.


Errors/Bugs:
-------------------
Everytime, you run a command. There is extra prompt.  
