#ifndef __INCLUDE_BASIC_H_
#define __INCLUDE_BASIC_H_

#include "bi.h"

word pow2(int a);

int bitlen(word a);

// min(a, b)
int min(IN int a, IN int b);

// max(a, b) → max(a, b)
int max(IN int a, IN int b);

#define get_j_bit(a, j) ((a >> j) & 0x1)

#endif