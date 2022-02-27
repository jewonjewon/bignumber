#ifndef _INCLUDE_BI_RAND_H
#define _INCLUDE_BI_RAND_H

#include "bi.h"
#include "bi_op.h"
#include "bi_prime.h"
#include "bi_test.h"

void arr_rand_range(word *dst, IN int lbound, int ubound);
void arr_rand(word *dst, IN int wordlen);

void bi_gen_rand(OUT bigint **A, IN int sign, IN int wordlen);
void bi_gen_rand_range(OUT bigint **A, IN int sign, IN int lbound, int ubound);

void bi_SPDM(bigint **C, bigint *A);
void bi_gen_rand_bit(bigint **C, bigint *A);

void bi_gen_random_element(OUT bigint **C, int sign, int bitlen);

#endif