CC = gcc
CFLAGS = -I./raylib/include

all: main util test


main: Main.c 
	gcc -c -o main.o Main.c

util: util.c util.h
	gcc -c -o util.o util.c


test: 
	gcc -Wall -o run util.o main.o

val_main: 
	valgrind --track-origins=yes --leak-check=full -s ./run

clean:
	rm -f main.o util.o run test