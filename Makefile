--all: mygrep

mygrep: mygrep.o
	gcc -o mygrep mygrep.o

mygrep.o: mygrep.c mygrep.h
	gcc -c -o mygrep.o -pedantic -Wall -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_SVID_SOURCE -D_POSIX_C_SOURCE=200809L -g -c mygrep.c

clean:
	rm -f mygrep mygrep.o