#ifndef __BI_OP_H__
#define __BI_OP_H__

#include "bi_local.h"

/* ARITHMETIC OPERATION */
void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_ADDC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_SUB_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_MUL_AB(OUT bigint **C, IN word A, IN word B);
void bi_MULC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_MUL(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_MULC_karatsuba(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_SQU_A(OUT bigint **C, word A);
void bi_SQUC(OUT bigint **C, IN bigint *A);
void bi_SQU(OUT bigint **C, IN bigint *A);

/* LOGICAL OPERATION */
void bi_word_lshift(IN OUT bigint **A, IN int x);
void bi_word_lshift2(OUT bigint **C, IN bigint *A, IN int r);

void bi_lshift(OUT bigint **A, IN int x);

void bi_word_rshift(OUT bigint **A, IN int x);

void bi_word_reduction(OUT bigint **A, IN int r);

#endif