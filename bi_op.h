#ifndef __BI_OP_H__
#define __BI_OP_H__

#include "bi.h"

word pow2(int a);

#define get_j_bit(a, j) ((a >> j) & 0x1)

int bitlen(word a);

/* ARITHMETIC OPERATION */
void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_ADDC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_SUB_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B);

/* MULTIPLICATION */
void bi_MUL_AB(OUT bigint **C, IN word A, IN word B);
void bi_MULC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_MUL(OUT bigint **C, IN bigint *A, IN bigint *B);

// C *= A
void bi_MUL_assign(IN OUT bigint **C, IN bigint *A);

void bi_KMUL(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_MULC_karatsuba(OUT bigint **C, IN bigint *A, IN bigint *B);

/* SQUARING */
void bi_SQU_A(OUT bigint **C, word A);
void bi_SQUC(OUT bigint **C, IN bigint *A);
void bi_SQU(OUT bigint **C, IN bigint *A);

void bi_SQU_assign(OUT bigint **C);

void bi_SQUC_karatsuba(OUT bigint **C, IN bigint *A);
void bi_KSQU(OUT bigint **C, IN bigint *A);

/* DIVISION */
word bi_long_div_2word(IN bigint *A, IN word B);
void bi_DIVCC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B);
void bi_DIVC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B);
void bi_DIV(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B);

/* EXPONENTIATION */
void bi_l2r(bigint **C, bigint *x, int n);
void bi_r2l(bigint **C, bigint *A, int n);
void bi_mns(bigint **C, bigint *A, int n);

/* LOGICAL OPERATION */
void bi_word_lshift(IN OUT bigint **A, IN int x);
void bi_word_lshift2(OUT bigint **C, IN bigint *A, IN int r);

void bi_lshift(OUT bigint **A, IN int x);
void bi_rshift(OUT bigint **A, IN int x);

void bi_word_rshift(OUT bigint **A, IN int x);

void bi_word_reduction(OUT bigint **A, IN int r);

/* GCD ALG.*/

void bi_gcd_bin(bigint **C, bigint *A, bigint *B);

#endif