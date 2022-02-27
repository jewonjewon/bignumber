#ifndef _INCLUDE_BI_PRIME_H
#define _INCLUDE_BI_PRIME_H

#include "bi.h"
#include "bi_op.h"
#include "bi_prime.h"
#include "bi_test.h"
// #include "benchmark.h"
#include "bi_rand.h"
#include "RSA.h"

// #include <index/basic.h>
// #include <index/bi_prime.h>
// #include <index/bi_op.h>
// #include <index/bi_test.h>
// #include <index/bi_rand.h>
// #include <index/RSA.h>

int bi_get_l(bigint *a);
int bi_is_composite(IN bigint *n, IN bigint *q, IN int l, IN bigint *a);
int bi_is_prime(bigint *n, int k);

void bi_gen_prime(bigint **p, int bitlen);

#endif