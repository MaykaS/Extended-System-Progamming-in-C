Learn how to use linux shell, together with some basic commands.
Learn how to write basic programs in C.
Number representation, and bit-wise operators.

# task 1a-
Write a program that receives characters from the standard input and prints their ascii codes in decimal (space separated). 
The program runs in a loop until EOF is received.
# task 1b-
Extend your previous program to print the ascii code in binary if a -b flag is received, 
from least significant bit to the most significant bit. Write a function that receives a char and an array of 8 cells, 
and returns the binary representation of the char in the array. 
The program must run like task 1a if not given any flags.
# task 1c-
Extend your previous program and add the following feature if a -c flag is received: 
the program still receives characters from the standard input but now prints upper case letters if the input is lower case and vice versa, 
lower case letter if the input is upper case.
# task 2-
Extend the program from task1 to write the output to a file instead of stdout if the -o flag is given. 
Extend the program from task1 to read the input from a file instead of stdin if the -i flag is given.
