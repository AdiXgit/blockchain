CC=gcc
CFLAGS=-Wall -std=c99

all: main

main: main.o blockchain.o sha256.o
	$(CC) $(CFLAGS) -o main main.o blockchain.o sha256.o

main.o: main.c blockchain.h sha256.h
	$(CC) $(CFLAGS) -c main.c

blockchain.o: blockchain.c blockchain.h sha256.h
	$(CC) $(CFLAGS) -c blockchain.c

sha256.o: sha256.c sha256.h
	$(CC) $(CFLAGS) -c sha256.c

clean:
	rm -f *.o main
