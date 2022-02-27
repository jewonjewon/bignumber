#ifndef _INCLUDE_BI_TEST_H
#define _INCLUDE_BI_TEST_H

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"
#include "basic.h"
// #include "../include/basic.h"

/* 테스트용 서브 함수들 */
void sage_show_add(bigint **C, bigint *A, bigint *B, int j);
void sage_show_sub(bigint **C, bigint *A, bigint *B, int j);
void sage_show_mul(bigint **C, bigint *A, bigint *B, int j);
void sage_show_squ(bigint **C, bigint *A, int j);
void sage_show_div(bigint **Q, bigint **R, bigint *A, bigint *B, int j);
void sage_show_exp(bigint **C, bigint *A, bigint *B, int j);
void sage_show_mod_exp(bigint **C, bigint *A, bigint *n, bigint *M, int j);
void sage_show_gcd(bigint **C, bigint *A, bigint *B, int j);
void sage_show_xgcd(bigint **C, bigint *A, bigint *B, int j);
void sage_show_is_prime(bigint *n, int k, int v, int j);
void sage_show_prime_gen(bigint *n, int j);

void bi_delete_3(bigint **C, bigint **A, bigint **B);
void bi_delete_2(bigint **C, bigint **A);

/* ADD Accuracy Verification */
void sub_test_ADD1(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_ADD2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_ADD3(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_ADD4(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_ADD5(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_ADD6(bigint **C, bigint *A, bigint *B, IN int TEST);

void test_ADD(IN int TEST);
//

/* SUB Accuracy Verification */
void sub_test_SUB1(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB3(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB4(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB5(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB6(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB7(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB8(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_SUB9(bigint **C, bigint *A, bigint *B, IN int TEST);

void test_SUB(IN int TEST);
//

void test_MUL_AB(int TEST);
void test_MULC(int TEST);

/* MUL Accuracy Verification */
void sub_test_MUL1_1(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL1_2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL1_3(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL3(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL4(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL5(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_MUL6(bigint **C, bigint *A, bigint *B, IN int TEST);

void test_MUL(IN int TEST);

/* karatsuba MUL Accuracy Verification */
void sub_test_KMUL1_1(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL1_2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL1_3(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL3(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL4(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL5(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL6_1(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL6_2(bigint **C, bigint *A, bigint *B, IN int TEST);
void sub_test_KMUL6_3(bigint **C, bigint *A, bigint *B, IN int TEST);

void test_KMUL(IN int TEST);

void test_SQU_A(int TEST);
void test_SQUC(int TEST);

/* SQU Accuracy Verification */
void sub_test_SQU1_1(bigint **C, bigint *A, IN int TEST);
void sub_test_SQU1_2(bigint **C, bigint *A, IN int TEST);
void sub_test_SQU1_3(bigint **C, bigint *A, IN int TEST);
void sub_test_SQU2(bigint **C, bigint *A, IN int TEST);

void test_SQU(IN int TEST);

void sub_test_KSQU1_1(bigint **C, bigint *A, IN int TEST);
void sub_test_KSQU1_2(bigint **C, bigint *A, IN int TEST);
void sub_test_KSQU1_3(bigint **C, bigint *A, IN int TEST);
void sub_test_KSQU2(bigint **C, bigint *A, IN int TEST);

void test_KSQU(IN int TEST);

/* LEFT SHIFT TEST */
void test_bi_word_lshift(int TEST);
void test_bi_word_lshift2(int TEST);
void test_bi_lshift(int TEST);
void test_bi_rshift(int TEST);
void test_bi_word_rshift(int TEST);

/* word reduction */
void test_bi_word_reduction(int TEST);

void test_MULC_karastuba(int TEST);
/* DIVISION */
void test_long_div_bin(int TEST);

void test_bi_long_div_2word(int TEST);
void test_DIVCC(int TEST);
void test_DIVC(int TEST);
void test_DIV(int TEST);
/* EXPONENTIATION */
void test_exp(int TEST, void (*func)(bigint **, bigint *, bigint *));

/* MODULO EXPONENTIATION */
void test_mod_exp(int TEST, void (*func)(bigint **, bigint *, bigint *, bigint *));

/* GCD */
void test_gcd(int TEST, void (*func)(bigint **, bigint *, bigint *));

/* XGCD */
void test_xgcd(int TEST, void (*func)(bigint **, bigint *, bigint *));

/* MONTGOMERY REDUCTION */
void test_mont_red(int TEST);

/* PRIME */
void test_is_prime(int TEST, int (*func)(bigint *, int k));
void test_prime_gen(int TEST, void (*func)(bigint **, int));

/* RSA */

#endif