#include "blockchain.h"
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Blockchain *create_blockchain() {
    Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
    blockchain->chain = (Block *)malloc(sizeof(Block) * 1);
    blockchain->size = 1;
    blockchain->capacity = 1;
    blockchain->chain[0] = create_genesis_block();
    return blockchain;
}

Block create_genesis_block() {
    Block genesis;
    genesis.index = 0;
    genesis.timestamp = (uint32_t)time(NULL);
    genesis.transaction_count = 0;
    strcpy(genesis.previous_hash, "0");
    genesis.nonce = 0;
    hash_block(&genesis, genesis.hash);
    return genesis;
}

Block create_block(Blockchain *blockchain, Transaction transactions[], int count) {
    Block new_block;
    new_block.index = blockchain->size;
    new_block.timestamp = (uint32_t)time(NULL);
    new_block.transaction_count = count;
    memcpy(new_block.transactions, transactions, sizeof(Transaction) * count);
    strcpy(new_block.previous_hash, blockchain->chain[blockchain->size - 1].hash);
    new_block.nonce = 0;
    hash_block(&new_block, new_block.hash);
    return new_block;
}

bool add_block(Blockchain *blockchain, Block new_block) {
    if (blockchain->size == blockchain->capacity) {
        blockchain->capacity *= 2;
        blockchain->chain = (Block *)realloc(blockchain->chain, sizeof(Block) * blockchain->capacity);
    }
    blockchain->chain[blockchain->size++] = new_block;
    return true;
}

void hash_block(const Block *block, char output[HASH_SIZE]) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%u%u%s%u", block->index, block->timestamp, block->previous_hash, block->nonce);
    calculate_sha256(buffer, (unsigned char *)output);
    output[HASH_SIZE - 1] = '\0'; // Ensure null-termination
}

bool validate_blockchain(Blockchain *blockchain) {
    for (size_t i = 1; i < blockchain->size; i++) {
        Block current = blockchain->chain[i];
        Block previous = blockchain->chain[i - 1];
        char recalculated_hash[HASH_SIZE];
        hash_block(&current, recalculated_hash);

        if (strcmp(current.hash, recalculated_hash) != 0) {
            printf("Block %lu: Hash mismatch\n", (unsigned long)i);
            printf("Expected: ");
            print_hash((unsigned char *)current.hash);
            printf("Recalculated: ");
            print_hash((unsigned char *)recalculated_hash);
            printf("Expected length: %zu\n", strlen(current.hash));
            printf("Recalculated length: %zu\n", strlen(recalculated_hash));
            return false;
        }

        if (strcmp(current.previous_hash, previous.hash) != 0) {
            printf("Block %lu: Previous hash mismatch\n", (unsigned long)i);
            printf("Expected: ");
            print_hash((unsigned char *)previous.hash);
            printf("Found: ");
            print_hash((unsigned char *)current.previous_hash);
            return false;
        }
    }
    return true;
}

void free_blockchain(Blockchain *blockchain) {
    free(blockchain->chain);
    free(blockchain);
}