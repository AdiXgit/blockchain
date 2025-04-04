CC = gcc
CFLAGS = -Wall -Wextra

OBJS = main.o blockchain.o sha256.o

all: blockchain

blockchain: $(OBJS)
	$(CC) $(CFLAGS) -o blockchain $(OBJS)

main.o: main.c blockchain.h sha256.h
	$(CC) $(CFLAGS) -c main.c

blockchain.o: blockchain.c blockchain.h sha256.h
	$(CC) $(CFLAGS) -c blockchain.c

sha256.o: sha256.c sha256.h
	$(CC) $(CFLAGS) -c sha256.c

clean:
	rm -f *.o blockchain
