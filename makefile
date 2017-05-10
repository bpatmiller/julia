# makefile for main.c and render.h
CC=g++
CFLAGS=-pg -O3 -I. -I/usr/include/freetype2 -lpngwriter -lpng -lfreetype
# a a wip for faster rendering
# DEPS=hsv2rgb.h

mainmake: main.c
	$(CC) $(CFLAGS) -o run.o main.c 
