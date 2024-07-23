#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"

#define MAX_BLOCKS 100

typedef struct {
    Block *blocks[MAX_BLOCKS];
    int block_count;
} Blockchain;

Blockchain* create_blockchain();
void add_block(Blockchain *blockchain, Block *block);
int is_blockchain_valid(Blockchain *blockchain);
void free_blockchain(Blockchain *blockchain);

#endif // BLOCKCHAIN_H
