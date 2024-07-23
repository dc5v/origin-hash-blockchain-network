#include "transaction.h"
#include <string.h>

void transaction_push(Block *block, const char *transaction)
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
