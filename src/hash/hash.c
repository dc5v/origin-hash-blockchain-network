#include "hash.h"
#include <stdio.h>
#include <string.h>

void create_block_hash(Block *block, char *output)
{
  char input[1024] = {0};
  int c;
  unsigned long hash = 5381;

  sprintf(input, "%d%ld%s", block->index, block->epoch, block->hash_prev);

  for (int i = 0; i < MAX_TRANSACTIONS; i++)
    if (strlen(block->transactions[i]) > 0)
      strcat(input, block->transactions[i]);

  char *str = input;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  sprintf(output, "%lx", hash);
}
