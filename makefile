CC = gcc
CFLAGS = -I./raylib/include

all: util main


main: Main.c 
	gcc -c -o main.o Main.c

util: util.c util.h
	gcc -c -o util.o util.c


test: 
	gcc -Wall -o run util.o main.o
	./run

val_main: 
	valgrind ./Main

clean:
	rm -f main.o util.o run test