all: LineParser

LineParser: LineParser.o myShell.o
	gcc -g -m32 -Wall -o LineParser LineParser.o myShell.o

LineParser.o: LineParser.c LineParser.h
	gcc -m32 -g -Wall -ansi -c -o LineParser.o LineParser.c

myShell.o: myShell.c
	gcc -m32 -g -Wall -ansi -c -o myShell.o myShell.c

.PHONY: clean
clean:
	rm -f *.o LineParser
