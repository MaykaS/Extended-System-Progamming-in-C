ELF

# task 0c-
Write a program that uses the mmap to examine the header of a 32bit ELF file (include and use the structures in elf.h).
# task 1-
Write a program which prints all the Section names in an 32bit ELF file (like readelf -S). 
Your program should exit if invoked on a non 32bit ELF file.
Your program should go over all sections in the sections table, and for each one print its index, name, address, offset, and size in bytes.
# task 2-
Using your program from task 1 as a starting point, you should now write a program which prints all the symbol names in a 32bit ELF file,
notice that there might be more than once symbol table, and that you need to print them all. 
For each symbol, print its index number, its name and the name of the section in which it is defined. (similar to readelf -s).
# task 3-
Create a new program with a correct digit counter function (should get a char* and return an int)
