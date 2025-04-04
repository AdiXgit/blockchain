#include "pow.h"
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

#define DIFFICULTY 4
int is_valid_hash(const char *hash){
    for (int i = 0; i < DIFFICULTY; i++) {
        if (hash[i] != '0') {
            return 0;
        }
    }
    return 1;
}

void compute_hash(Block *block, char output[65]) {
    char input[1024];
    sprintf(input, "%d%d%s%s%d", block->index, block->timestamp, block->data, block->prev_hash, block->nonce);

    sha256_string(input, output);
}

void mine_block(Block *block) {
    block->nonce = 0;
    do {
        compute_hash(block, block->hash);
        block->nonce++;
    } while (!is_valid_hash(block->hash));
}
