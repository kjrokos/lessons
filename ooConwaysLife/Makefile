# The CC variable is the compiler
CC=g++

# CFLAGS will be the options passed to the compiler.
CFLAGS=-c -Wall -Wno-deprecated

# Libraries required to link to OpenGL
OGLLIBS=-framework OpenGL -framework GLUT

# Library required to link to ncurses
NCURSESLIBS=-lncurses

all: ncurses opengl

ncurses: main.ncurses.o gameOfLife.o
	$(CC) $(NCURSESLIBS) main.ncurses.o gameOfLife.o -o ncursesLife

opengl: main.opengl.o gameOfLife.o
	$(CC) $(OGLLIBS) main.opengl.o gameOfLife.o -o openglLife

main.ncurses.o: main.ncurses.cpp
	$(CC) $(CFLAGS) main.ncurses.cpp

main.opengl.o: main.opengl.cpp
	$(CC) $(CFLAGS) main.opengl.cpp

gameOfLife.o: gameOfLife.cpp
	$(CC) $(CFLAGS) gameOfLife.cpp

clean:
	rm -rf *o ncursesLife openglLife
