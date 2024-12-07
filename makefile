CC = gcc
CFLAGS = -I./raylib/include

all: main helper util link


main: Main.c 
	gcc -c -o main.o Main.c

util: util.c util.h
	gcc -c -o util.o util.c

link: 
	gcc -Wall -o main util.o main.o helper.o

helper:	helper.c helper.h
	gcc -Wall -Wextra -c -o helper.o helper.c

run:
	./main

memcheck: 
	valgrind --track-origins=yes --leak-check=full -s ./main

clean:
	rm -f main.o util.o main run