all: bcmp
bcmp: bcmp.o
	gcc -g -m32 -Wall -o bcmp bcmp.o
bcmp.o: task2.c
	gcc -g -m32 -Wall -ansi -c -o bcmp.o task2.c
.PHONY: clean
clean:
	rm -f *.o bcmp
	
