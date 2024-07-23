#include "blockchain.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

Blockchain *create_blockchain()
{
    Blockchain *blockchain = (Blockchain *)malloc(sizeof(Blockchain));
    Block *genesis_block = block_create(0, "0");

    blockchain->block_count = 0;
    add_block(blockchain, genesis_block);

    return blockchain;
}

void add_block(Blockchain *blockchain, Block *block)
{
    blockchain->blocks[blockchain->block_count++] = block;
}

bool blockchain_validate(Blockchain *blockchain)
{
    for (int i = 1; i < blockchain->block_count; i++)
    {
        Block *current_block = blockchain->blocks[i];
        Block *previous_block = blockchain->blocks[i - 1];

        if (strcmp(current_block->hash_prev, previous_block->hash) != 0)
        {
            return false;
        }

        char calculated_hash[HASH_SIZE];
        block_gen_hash(current_block, calculated_hash);

        if (strcmp(current_block->hash, calculated_hash) != 0)
        {
            return false;
        }
    }

    return true;
}

void blockchain_free(Blockchain *blockchain)
{
    for (int i = 0; i < blockchain->block_count; i++)
    {
        free(blockchain->blocks[i]);
    }
    free(blockchain);
}
