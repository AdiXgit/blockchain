#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "sha256.h"
#include <time.h>
#include "pow.h"


void calculate_hash(const Block *block, char output_hash[HASH_SIZE]) {
    char input[1024];
    snprintf(input, sizeof(input), "%d%s%s", block->index, block->data, block->prev_hash);

    BYTE hash_bin[32];
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (BYTE*)input, strlen(input));
    sha256_final(&ctx, hash_bin);

    for (int i = 0; i < 32; ++i) {
        sprintf(output_hash + (i * 2), "%02x", hash_bin[i]);
    }
    output_hash[64] = '\0';
}

Block create_block(Block *prev, const char *data) {
    Block new_block;
    new_block.index = prev->index + 1;
    new_block.timestamp = time(NULL);
    strncpy(new_block.data, data, sizeof(new_block.data));
    strncpy(new_block.prev_hash, prev->hash, sizeof(new_block.prev_hash));
    new_block.nonce = 0;

    mine_block(&new_block);  
    return new_block;
}
Blockchain *create_blockchain() {
    Blockchain *blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->head = NULL;
    blockchain->tail = NULL;
    blockchain->size = 0;
    return blockchain;
}

bool add_block(Blockchain *blockchain, Block new_block) {
    Block *block_ptr = (Block*)malloc(sizeof(Block));
    if (!block_ptr) return false;

    *block_ptr = new_block;

    if (blockchain->head == NULL) {
        blockchain->head = block_ptr;
    } else {
        blockchain->tail->next = block_ptr;
    }

    blockchain->tail = block_ptr;
    blockchain->size++;
    return true;
}

void print_blockchain(const Blockchain *blockchain) {
    Block *current = blockchain->head;
    while (current) {
        printf("Block #%d\n", current->index);
        printf("Data: %s\n", current->data);
        printf("Hash: %s\n", current->hash);
        printf("Prev Hash: %s\n\n", current->prev_hash);
        current = current->next;
    }
}

void free_blockchain(Blockchain *blockchain) {
    Block *current = blockchain->head;
    while (current) {
        Block *next = current->next;
        free(current);
        current = next;
    }
    free(blockchain);
}
