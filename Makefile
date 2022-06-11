
CC = gcc
CFLAGS = -Wall


all: project3 

project:project3.c
	$(CC) $(CFLAGS) -o project3 project3.c -lpthread



exec:
	./project3

clean:
	rm -rf project3

