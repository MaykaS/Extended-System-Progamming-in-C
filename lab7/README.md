enrich the set of capabilities of your shell by implementing input/output redirection and pipelines.
 Your shell will then be able to execute non-trivial commands such as "tail -n 2 in.txt| cat > out.txt", 
demonstrating the power of these simple concepts.

# task 0-
Implement a simple program called mypipe, which creates a child process that sends the message "hello" to its parent process. 
The parent then prints the incoming message and terminates. Use the pipe system call (see man) to create the pipe.
# task 1-
Add standard input/output redirection capabilities to your shell (e.g. "cat < in.txt > out.txt"). 
# task 2-
Write a short program called mypipeline which creates a pipeline of 2 child processes. 
Essentially, you will implement the shell call "ls -l | tail -n 2".
# task 3-
Go back to your shell and add support to a single pipe. 
Your shell must be able now to run commands like: 
ls|wc -l which basically counts the number of files/directories under the current working dir. 
The most important thing to remember about pipes is that the write-end of the pipe needs to be closed in all processes, 
otherwise the read-end of the pipe will not receive EOF, unless the main process terminates


