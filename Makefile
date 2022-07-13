all: pgm.o lbp.o
	gcc pgm.o lbp.o main.c -o main.exe

pgm.o: pgm.h
	gcc -c pgm.c

lbp.o: lbp.h
	gcc -c lbp.c

clean:
	rm -f *.o main.exe