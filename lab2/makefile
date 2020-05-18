all: menu
menu: task3.o
	gcc -g -m32 -Wall -o menu task3.o
task3.o: task3.c
	gcc -g -m32 -Wall -ansi -c -o task3.o task3.c
.PHONY: clean
clean:
	rm -f *.o menu              
