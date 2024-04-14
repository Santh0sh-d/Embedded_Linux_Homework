#Makefile
CC = gcc
CFLAGS = -Wall

# Source Files 
SRCS = client1.c util.c

#Object Files
OBJS = $(SRCS:.c=.o)

#Target exe
TARGET = client1

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

clean:
#	rm -f client2 *.o
	rm -f $(OBJS) $(TARGET)	
