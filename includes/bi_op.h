#ifndef _INCLUDE_BI_OP_H
#define _INCLUDE_BI_OP_H

#include "bi.h"

int bi_bit_cnt(bigint *A);
int bi_get_j_bit(bigint *A, int n);

/* LOGICAL OPERATION */
void bi_word_lshift(IN OUT bigint **A, IN int x);

void bi_lshift(OUT bigint **A, IN int x);

void bi_word_rshift(OUT bigint **A, IN int x);
void bi_rshift(OUT bigint **A, IN int x);

void bi_word_reduction(OUT bigint **A, IN int r);
void bi_red(OUT bigint **A, IN int x);

int bi_get_j_bit(bigint *A, int n);

// word bi_get_j_bit(bigint *A, int j);

/* XOR */
void bi_xor(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_xor_asg(IN OUT bigint **C, IN bigint *A);

void bi_or_asg(IN OUT bigint **C, IN bigint *A);

/* ARITHMETIC OPERATION */

/* ADD */
void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_add_core(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_add(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_addc_asg(IN OUT bigint **C, IN bigint *A);
void bi_add_asg(IN OUT bigint **C, IN bigint *A);

void bi_addi(IN OUT bigint **A, IN word a);

/* SUB */
void bi_SUB_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_sub_core(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_sub(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_sub_asg(IN OUT bigint **C, IN bigint *A);
void bi_sub_minus_one(bigint **A);
void bi_subi(IN OUT bigint **A, IN word a);

/* MULTIPLICATION */
void bi_MUL_AB(OUT bigint **C, IN word A, IN word B);
void bi_mul_core(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_mul(OUT bigint **C, IN bigint *A, IN bigint *B);

// C *= A
void bi_mul_asg(IN OUT bigint **C, IN bigint *A);

void bi_kmul_core(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_kmul(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_kmul_asg(OUT bigint **C, IN bigint *A);

/* SQUARING */
void bi_SQU_A(OUT bigint **C, word A);
void bi_squ_core(OUT bigint **C, IN bigint *A);
void bi_squ(OUT bigint **C, IN bigint *A);

void bi_squ_asg(OUT bigint **C);

void bi_ksqu_core(OUT bigint **C, IN bigint *A);
void bi_ksqu(OUT bigint **C, IN bigint *A);

void bi_ksqu_asg(OUT bigint **C);

/* DIVISION */
word bi_long_div_2word(IN bigint *A, IN word B);
void bi_div_core2(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B);
void bi_div_core(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B);
void bi_div(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B);

void bi_long_div_bin(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B);

void bi_mod_asg(OUT bigint **R, IN bigint *A);
void bi_div_asg(OUT bigint **Q, IN bigint *A);

/* 임의의 정수 A와 B를 입력받아 !!몫(=Q)!!만 반환하는 나눗셈 함수 */
void bi_div_q(OUT bigint **Q, IN bigint *A, IN bigint *B);

/* 임의의 정수 A와 B를 입력받아 !!나머지(=R)!!만 반환하는 나눗셈 함수 */
void bi_div_r(OUT bigint **R, IN bigint *A, IN bigint *B);

/* EXPONENTIATION */
void bi_l2r(OUT bigint **C, IN bigint *A, IN bigint *n);
void bi_r2l(OUT bigint **C, IN bigint *A, IN bigint *n);
void bi_mns(OUT bigint **C, IN bigint *A, IN bigint *n);

/* MODULAR EXPONENTIATION */
void bi_mod_exp_l2r(OUT bigint **C, IN bigint *A, IN bigint *n, IN bigint *M);
void bi_mod_exp_r2l(OUT bigint **C, IN bigint *A, IN bigint *n, IN bigint *M);
void bi_mod_exp_mns(OUT bigint **C, IN bigint *A, IN bigint *n, IN bigint *M);

void bi_mod_exp_l2r_asg(OUT bigint **C, IN bigint *n, IN bigint *M);

/* GCD ALG.*/
void bi_ea_rcs(bigint **C, bigint *A, bigint *B);
void bi_ea_itr(bigint **C, bigint *A, bigint *B);
void bi_ea_bin_itr(bigint **C, bigint *A, bigint *B); /* Use binary euclide algoritm iterative ver. */
void lehmer_gcd(OUT bigint **C, IN bigint *A, IN bigint *B);

/* XGCD ALG.*/
void bi_eea_itr(OUT bigint **C, IN bigint *A, IN bigint *B);     /* extended euclide algoritm (iteration ver.) */
void bi_eea_bin_itr(OUT bigint **C, IN bigint *A, IN bigint *B); /* binary extended euclide algoritm (iteration ver.) */
void bi_eea_rcs(bigint **d, bigint **alpha, bigint **beta, bigint *a, bigint *b);

void bi_mont_red(OUT bigint **C, IN bigint *x, IN bigint *R, IN bigint *N, bigint *nn);

#endif