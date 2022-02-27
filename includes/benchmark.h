#ifndef _INCLUDE_BENCHMARK_H
#define _INCLUDE_BENCHMARK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "basic.h"
#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"

void bench_bi_ADD(IN int TEST);

void bench_ADD();

/* == == == == == BENCHMARKING MUL == == == == == */
void bench_bi_MUL(IN int TEST, int len);
void bench_bi_KMUL(IN int TEST, int len);
void bench_bi_check_KMUL(IN int TEST, int FLAG);
void bi_check_KMUL(OUT bigint **C, IN bigint *A, IN bigint *B, int FLAG);
void bi_check_MULC_karatsuba(OUT bigint **C, IN bigint *A, IN bigint *B, int FLAG);

void bench_MUL();

void bench_bi_long_div_bin(IN int TEST);
void bench_bi_DIV(IN int TEST);
void bench_DIV();

void bench_lshift();

void bench_bi_gcd(IN int TEST, void (*func)(bigint **, bigint *, bigint *));
void bench_gcd();

void bench_bi_SPDM(IN int TEST, void (*func)(bigint **, bigint *));
void bench_SPDM();

void bench_bi_prime(IN int TEST, void (*func)(bigint **n, int k));
void bench_prime();
void bench_RSA();
// void TIME_MSRMN(void (*func)(RSA_key, RSA_key, int));

#endif