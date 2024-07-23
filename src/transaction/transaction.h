#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../blockchain/block.h"

void transaction_push(Block *block, const char *transaction);

#endif
