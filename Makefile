# Compiler and flags
CC = gcc
CFLAGS = -I../include ../include/cs50.c -Wall -Wextra -std=c11

# Default target
tideman: tideman.c
	$(CC) $(CFLAGS) tideman.c -o tideman

clean:
	rm -f tmp*.html

