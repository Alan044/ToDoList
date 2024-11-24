CC = gcc
CFLAGS = -I./raylib/include
LDFLAGS = -L./raylib/lib -lraylib -lm -ldl -lpthread -lGL -lX11

all: Main

Main: Main.c
	gcc -o Main Main.c 
run: 
	./Main
val_main: 
	valgrind ./Main

clean:
	rm -f Main