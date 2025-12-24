GDB Commands:
-------------
gdb can start to debug an application by using the command gdb executable_file name. gdb loads the executable's symbols. Then the display prompt is available to start using the debugger. 
There are three ways to view a process with this debugger: 
1.Use the attach command to view a running process. attach stops the process.
2.Use the run command to start the program.
3.Look at an existing core file to determine the state the process was in when it crashed or was killed. To view a core file, start gdb with the command gdb executable_file corefile.

Before the program is run or before attaching it to a running program, list the source code where the bug is believed to be, and then set break points to start debugging the program. 


Some Useful gdb Commands
Many gdb commands have abbreviations, as shown in the following list: 
1. attach - at - Attaches to a running process.
2. backtrace -bt - Prints a stack trace.
3. break - b -sets a break point.
4. clear - Clears a break point.
5. continue - c - Allows the program to continue executing.
6. delete - Clears a break point by number.
7. detach - detaches from the currently attached process.
display
8. Displays the value of an expression every time execution stops.
9. finish - Runs to the end of the function and displays return values of that function.
help
10. Displays help for gdb commands.
11.jump - Jumps to an address and continues the execution there.
12. listl - Lists the next 10 lines.
13.next - n Steps to the next machine language instruction.
14. print - p Prints the value of an expression.
15.run - r Runs the current program from the start.
16.set - Changes the value of a variable.
17.step -s - Steps the program instruction by instruction.
18. where - w Prints a stack trace.


Compiling a Program That Is to Be Debugged with gdb:
--------------------------------------------------
The source code of the program that is to be debugged using gdb must first be successfully compiled. Once the program source code compiles successfully, compile it one more time using the -g compiler option: 
g++ -g source_code_file.cpp

or 
gcc -g source_code_file.c



Debugging Using a Core File:
--------------------------
ulimit -a
umlimt -c 500000


core-file core

 
Graphical GDB Interface:
-----------------------

DDD (Data Display Debugger)






c
