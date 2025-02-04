#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>  // Include for size_t

#define HASH_SIZE 65
#define MAX_TRANSACTIONS 15

typedef struct {
    char sender[64];
    char recipient[64];
    float amount;
} Transaction;

typedef struct {
    uint32_t index;
    uint32_t timestamp;
    Transaction transactions[MAX_TRANSACTIONS];
    int transaction_count;
    char previous_hash[HASH_SIZE];
    uint32_t nonce;
    char hash[HASH_SIZE];
} Block;

typedef struct {
    Block *chain;
    size_t size;
    size_t capacity;
} Blockchain;

Blockchain *create_blockchain();
Block create_genesis_block();
Block create_block(Blockchain *blockchain, Transaction transactions[], int count);
bool add_block(Blockchain *blockchain, Block new_block);
bool validate_blockchain(Blockchain *blockchain);
void hash_block(const Block *block, char output[HASH_SIZE]);
void calculate_sha256(const char *str, unsigned char hash[HASH_SIZE]);
void print_hash(unsigned char hash[HASH_SIZE]);
void free_blockchain(Blockchain *blockchain);

#endif