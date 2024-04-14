#Makefile
CC = gcc
CFLAGS = -Wall

#Default target to build client1 and client2 
all: client1 client2

client1: client1.c util.c
	$(CC) $(CFLAGS) -o $@ $^

client2: client2.c util.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f client1 client2