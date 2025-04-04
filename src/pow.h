//proof of work
#ifndef PROOF_OF_WORK_H
#define PROOF_OF_WORK_H

#include "blockchain.h"
void mine_block(Block *block);
void compute_hash(Block *block, char output[65]);
int is_valid_hash(const char *hash);

#endif