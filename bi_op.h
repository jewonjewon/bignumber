#ifndef __BI_OP_H__
#define __BI_OP_H__

#include "bi.h"
/* 수정 할 것 */
int min(IN int a, IN int b);
word pow2(int a);

#define get_j_bit(a, j) ((a >> j) & 0x1)

int bitlen(word a);
int bi_bit_cnt(bigint *A);

/* LOGICAL OPERATION */
void bi_word_lshift(IN OUT bigint **A, IN int x);
// void bi_word_lshift2(OUT bigint **C, IN bigint *A, IN int r);

void bi_lshift(OUT bigint **A, IN int x);

void bi_word_rshift(OUT bigint **A, IN int x);
void bi_rshift(OUT bigint **A, IN int x);

void bi_word_reduction(OUT bigint **A, IN int r);

int bi_get_j_bit(bigint *A, int n);

// word bi_get_j_bit(bigint *A, int j);

/* XOR */
void bi_XOR(bigint **C, bigint *A, bigint *B);
void bi_xor_asg(IN OUT bigint **C, IN bigint *A);

/* ARITHMETIC OPERATION */
void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_ADDC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_addc_asg(IN OUT bigint **C, IN bigint *A);
void bi_add_asg(IN OUT bigint **C, IN bigint *A);

// void bi_ADDC2(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_SUB_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_sub_asg(IN OUT bigint **C, IN bigint *A);

/* MULTIPLICATION */
void bi_MUL_AB(OUT bigint **C, IN word A, IN word B);
void bi_MULC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_MUL(OUT bigint **C, IN bigint *A, IN bigint *B);

// C *= A
void bi_mul_asg(IN OUT bigint **C, IN bigint *A);

void bi_MULC_karatsuba(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_KMUL(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_kmul_asg(OUT bigint **C, IN bigint *A);

/* SQUARING */
void bi_SQU_A(OUT bigint **C, word A);
void bi_SQUC(OUT bigint **C, IN bigint *A);
void bi_SQU(OUT bigint **C, IN bigint *A);

void bi_squ_asg(OUT bigint **C);

void bi_SQUC_karatsuba(OUT bigint **C, IN bigint *A);
void bi_KSQU(OUT bigint **C, IN bigint *A);

void bi_ksqu_asg(OUT bigint **C);

/* DIVISION */
word bi_long_div_2word(IN bigint *A, IN word B);
void bi_DIVCC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B);
void bi_DIVC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B);
void bi_DIV(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B);

void bi_long_div_bin(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B);

/* EXPONENTIATION */
// 지수도 bigint로 처리
void bi_l2r(bigint **C, bigint *x, bigint *n);
void bi_r2l(bigint **C, bigint *A, int n);
void bi_mns(bigint **C, bigint *A, int n);

void bi_mod_asg(OUT bigint **R, IN bigint *A);
void bi_div_asg(OUT bigint **Q, IN bigint *A);

/* MODULAR EXPONENTIATION */
void bi_mod_l2r(OUT bigint **C, IN bigint *A, IN int n, IN bigint *M);

/* GCD ALG.*/
// 유클리드 함수도 구현
void bi_gcd_bin(bigint **C, bigint *A, bigint *B); /* binary euclide algoritm */

/* XGCD ALG.*/
void bi_eea_itr(OUT bigint **C, IN bigint *A, IN bigint *B); /* extended euclide algoritm (iteration ver.) */

// void bi_xgcd_bin(bigint **C, bigint *A, bigint *B);

void bi_mont_red(OUT bigint **C, IN bigint *x, IN bigint *R, IN bigint *N);

#endif