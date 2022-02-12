#ifndef __BI_PRIME_H__
#define __BI_PRIME_H__

#include "bi.h"
#include "bi_op.h"

int bi_get_l(bigint *a);
int bi_is_composite(IN bigint *n, IN bigint *q, IN int l, IN bigint *a);
int bi_is_prime(bigint *n, int k);

void bi_gen_prime(bigint **p, int bitlen);

#endif