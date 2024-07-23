#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Block *create(int index, const char *previous_hash)
{
  Block *block = (Block *)malloc(sizeof(Block));
  
  block->index = index;
  block->epoch = time(NULL);

  strcpy(block->hash_prev, previous_hash);
  memset(block->transactions, 0, sizeof(block->transactions));
  gen_hash(block, block->hash);

  return block;
}

void gen_hash(Block *block, char *output)
{
  unsigned long hash = 5381;
  char input[1024] = {0};
  int c;

  sprintf(input, "%d%ld%s", block->index, block->epoch, block->hash_prev);

  for (int i = 0; i < MAX_TRANSACTIONS; i++)
  {
    if (strlen(block->transactions[i]) > 0)
    {
      strcat(input, block->transactions[i]);
    }
  }

  char *str = input;

  while ((c = *str++))
  {
    hash = ((hash << 5) + hash) + c;
  }

  sprintf(output, "%lx", hash);
}

void add_transaction(Block *block, const char *transaction)
{
  for (int i = 0; i < MAX_TRANSACTIONS; i++)
  {
    if (strlen(block->transactions[i]) == 0)
    {
      strcpy(block->transactions[i], transaction);
      break;
    }
  }
}

int get_transaction_count(Block *block)
{
  int count = 0;

  for (int i = 0; i < MAX_TRANSACTIONS; i++)
  {
    if (strlen(block->transactions[i]) > 0)
    {
      count++;
    }
  }

  return count;
}
