//blockchain
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"sha256.h"

typedef struct Block{
    int index;time_t timestamp;char data[256];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char prev_hash[SHA256_DIGEST_LENGTH];
    struct Block *next;
} Block;


Block* create_block(int index,char *previous_hash,char*data)
{
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->index = index; new_block->timestamp = time(NULL);
    strncpy(new_block->data,data,sizeof(new_block->data)-1);


    char prev_hash[SHA256_DIGEST_LENGTH];
    if(previous_hash != NULL){
        memcpy(prev_hash,previous_hash,SHA256_DIGEST_LENGTH);
    }

    char block_content[1024];
    snprintf(block_content,sizeof(block_content),"%d%ld%s",new_block->index,new_block->timestamp,new_block->data);
    calculate_sha256(block_content,new_block->hash);
    return new_block;
}

typedef struct Blockchain{
    Block*head;Block*tail;
}Blockchain;

Blockchain*create_blockchain(){
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    blockchain->head = NULL;
    blockchain->tail = NULL;
    return blockchain;
}


void add_block(Blockchain*blockchain,Block*new_block){
    if(blockchain->tail == NULL){
        blockchain->head = blockchain->tail = new_block;
    } else {
        blockchain->tail->next = new_block;
        blockchain->tail = new_block;
    }
}

void print_blockchain(Blockchain*blockchain){
    Block*current = blockchain->head;
    while(current != NULL){
        printf("Block %d\n", current->index);
        printf("Timestamp: %ld\n", current->timestamp);
        printf("Data: %s\n", current->data);
        printf("Hash: ");
        print_hash(current->hash);
        printf("\n");
        current = current->next;
    }
}



