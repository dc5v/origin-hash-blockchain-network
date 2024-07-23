#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "blockchain/blockchain.h"
#include "blockchain/block.h"
#include "transaction/transaction.h"
#include "network/network.h"
#include "util/util.h"

#define PORT 44333

int main(int argc, char *argv[])
{
  Blockchain *blockchain = create_blockchain();
  Block *new_block = create_block(1, blockchain->blocks[blockchain->block_count - 1]->hash);

  block_transaction_push(new_block, "Alice contributed code to project X");
  add_block(blockchain, new_block);

  if (blockchain_validate(blockchain))
  {
    logmsg("Blockchain is valid.");
    logmsgf("Blockchain is valid.");
  }
  else
  {
    logmsg("Blockchain is invalid.");
    logmsgf("Blockchain is invalid.");
  }

  for (int i = 0; i < blockchain->block_count; i++)
  {
    Block *block = blockchain->blocks[i];

    logmsg("Block %d:", block->index);
    logmsg("Timestamp: %ld", block->epoch);
    logmsg("Previous Hash: %s", block->hash_prev);
    logmsg("Hash: %s", block->hash);
    logmsg("Transactions:");

    for (int j = 0; j < MAX_TRANSACTIONS; j++)
    {
      if (strlen(block->transactions[j]) > 0)
      {
        logmsg("  %s", block->transactions[j]);
      }
    }

    logmsg("");
  }

  create_server(PORT);
  blockchain_free(blockchain);

  return 0;
}
