#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdbool.h>
#include "block.h"

#define MAX_BLOCKS 100

typedef struct
{
    Block *blocks[MAX_BLOCKS];
    int block_count;
} Blockchain;

Blockchain *create_blockchain();
void add_block(Blockchain *blockchain, Block *block);
bool blockchain_validate(Blockchain *blockchain);
void blockchain_free(Blockchain *blockchain);

#endif
