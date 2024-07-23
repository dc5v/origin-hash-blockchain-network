#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>

#define MAX_TRANSACTIONS 256
#define HASH_SIZE 256

typedef struct 
{
    int index;
    char hash[HASH_SIZE];
    char hash_prev[HASH_SIZE];
    char transactions[MAX_TRANSACTIONS][256];
    time_t epoch;
} Block;

Block* create_block(int index, const char *previous_hash);
void block_gen_hash(Block *block, char *output);
void block_transaction_push(Block *block, const char *transaction);

#endif
