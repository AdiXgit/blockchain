#include "blockchain.h"
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void hash_block(const Block *block,char output[HASH_SIZE]){
        char buffer[1024] = {0};
        snprintf(buffer,sizeof(buffer),"%d%d%s%d",
        block->index,block->timestamp,block->previous_hash,block->nonce);
        sha256(buffer,output);
}

Blockchain *create_blockchain(){
    Blockchain *blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->size = 0;
    blockchain->capacity = 10;
    blockchain->chain = (Block*)malloc(blockchain->capacity * sizeof(Block));

    Block genesis = create_genesis_block();
    blockchain->chain[blockchain->size++] = genesis;
    return blockchain;
}

Block create_genesis_block(){
    Block genesis = {0};
    genesis.index = 0;
    genesis.timestamp = time(NULL);
    genesis.transaction_count = 0;
    strcpy(genesis.previous_hash,"0");
    genesis.nonce = 0;
    hash_block(&genesis,genesis.hash);
    return genesis;
}

//creating new block
Block create_block(Blockchain *blockchain,Transaction transactions [],int count){
    Block new_block = {0};
    new_block.index = blockchain->size;
    new_block.timestamp = time(NULL);
    new_block.transaction_count = count;
    memcpy(new_block.transactions, transactions, count * sizeof(Transaction));
    strcpy(new_block.previous_hash, blockchain->chain[blockchain->size - 1].hash);

    do{
        new_block.nonce++;
        hash_block(&new_block,new_block.hash);
    } while(strncmp(new_block.hash,"0000",4) != 0);
    return new_block;
}

bool add_block(Blockchain *blockchain, Block new_block) {
    if (blockchain->size >= blockchain->capacity) {
        blockchain->capacity *= 2;
        blockchain->chain = (Block *)realloc(blockchain->chain, blockchain->capacity * sizeof(Block));
    }
    blockchain->chain[blockchain->size++] = new_block;
    return true;
}

bool validate_blockchain(Blockchain *blockchain) {
    for (size_t i = 1; i < blockchain->size; i++) {
        Block current = blockchain->chain[i];
        Block previous = blockchain->chain[i - 1];
        char recalculated_hash[HASH_SIZE];
        hash_block(&current, recalculated_hash);

        if (strcmp(current.hash, recalculated_hash) != 0 || strcmp(current.previous_hash, previous.hash) != 0) {
            return false;
        }
    }
    return true;
}


void free_blockchain(Blockchain *blockchain) {
    free(blockchain->chain);
    free(blockchain);
}







