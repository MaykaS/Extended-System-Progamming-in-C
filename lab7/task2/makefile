all: mypipe
mypipe: mypipe.o
	gcc -g -m32 -Wall -o mypipe mypipe.o
mypipe.o: mypipe.c
	gcc -m32 -g -Wall -ansi -c -o mypipe.o mypipe.c

clean:
	rm -f *o mypipe
