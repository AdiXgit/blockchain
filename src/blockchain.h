#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdbool.h>

#define MAX_DATA_SIZE 256
#define HASH_SIZE 65
#include <time.h>

typedef struct Block {
    int index;
    time_t timestamp;
    char data[256];
    char prev_hash[65];
    char hash[65];
    int nonce; 
    struct Block *next;
} Block;

typedef struct {
    Block *head;
    Block *tail;
    int size;
} Blockchain;

Blockchain *create_blockchain();
Block create_block(Block *prev, const char *data);
bool add_block(Blockchain *blockchain, Block new_block);
void print_blockchain(const Blockchain *blockchain);
void free_blockchain(Blockchain *blockchain);

void calculate_hash(const Block *block, char output_hash[HASH_SIZE]);

#endif