#include <stdio.h>
#include <string.h>

#include "blockchain/blockchain.h"
#include "blockchain/block.h"
#include "transaction/transaction.h"

int main()
{
  Blockchain *blockchain = create_blockchain();
  Block *new_block = block_create(1, blockchain->blocks[blockchain->block_count - 1]->hash);

  block_transaction_push(new_block, "Alice contributed code to project X");
  add_block(blockchain, new_block);

  if (blockchain_validate(blockchain))
  {
    printf("Blockchain valid\n");
  }
  else
  {
    printf("Blockchain invalid.\n");
  }

  for (int i = 0; i < blockchain->block_count; i++)
  {
    Block *block = blockchain->blocks[i];

    printf("Block %d:\n", block->index);
    printf("Timestamp: %ld\n", block->epoch);
    printf("Previous Hash: %s\n", block->hash_prev);
    printf("Hash: %s\n", block->hash);
    printf("Transactions:\n");

    for (int j = 0; j < MAX_TRANSACTIONS; j++)
    {
      if (strlen(block->transactions[j]) > 0)
      {
        printf("  %s\n", block->transactions[j]);
      }
    }

    printf("\n");
  }

  blockchain_free(blockchain);

  return 0;
}
