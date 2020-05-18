Get acquainted with command interpreters ("shell").
Understand how Unix/Linux fork() works.
Learn how to read the manual (man).
Write tedious code in C, and address non-trivial memory allocation/deallocation issues.
Learn to debug your code!

In this sequence of labs, you will be implementing a simple shell (command-line interpreter). 
Like traditional UNIX shells, your shell program will also be a user level process (just like all your programs to-date),
that will rely heavily on the operating system's services. Your shell should do the following:
Receive commands from the user.
Interpret the commands, and use the operating system to help starting up programs and processes requested by the user.
Manage process execution (e.g. run processes in the background, kill them, etc.), using the operating system's services.
The complicated tasks of actually starting up the processes, mapping their memory, files, etc. 
are strictly a responsibility of the operating system, and as such you will study these issues in the Operating Systems course. 
Your responsibility, therefore, is limited to telling the operating system which processes to run, 
how to run these processes (run in the background/foreground) etc.

Starting and maintaining a process involves many technicalities, 
and like any other command interpreter we will get assistance from system calls, such as execv, fork, waitpid 
(see man on how to use these system calls).
