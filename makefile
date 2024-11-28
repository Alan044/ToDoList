CC = gcc
CFLAGS = -I./raylib/include

all: Main

Main: Main.c
	gcc `pkg-config --cflags gtk+-3.0` -o Main Main.c `pkg-config --libs gtk+-3.0`


run: 
	./Main
val_main: 
	valgrind ./Main

clean:
	rm -f Main