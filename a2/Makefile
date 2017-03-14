all:

	gcc -c a2f.c -o a2f.o
	ar rcs libstream.a a2f.o
	rm *.o
	gcc -ansi -Wall -g addauthor.c -o addauthor libstream.a
	gcc -ansi -Wall -g post.c -o post libstream.a
	chmod u+x view.py
