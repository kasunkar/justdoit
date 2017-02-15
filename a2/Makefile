all:
	gcc -ansi -Wall -g a2.c -o post libstream.a 
lib:
	gcc -c a2f.c stream.h -o a2f.o
	ar rcs libstream.a a2f.o
	rm *.o
