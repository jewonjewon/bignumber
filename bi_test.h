#ifndef __BI_TEST_H__
#define __BI_TEST_H__

#include "bi_local.h"
#include "bi_op.h"
#include "bi_test.h"

/* ADD Accuracy Verification */
void sub_test_ADD1(IN int TEST);
void sub_test_ADD2(IN int TEST);
void sub_test_ADD3(IN int TEST);
void sub_test_ADD4(IN int TEST);
void sub_test_ADD5(IN int TEST);
void sub_test_ADD6(IN int TEST);

void test_ADD(IN int TEST);

/* SUB Accuracy Verification */
void sub_test_SUB1(IN int TEST);
void sub_test_SUB2(IN int TEST);
void sub_test_SUB3(IN int TEST);
void sub_test_SUB4(IN int TEST);
void sub_test_SUB5(IN int TEST);
void sub_test_SUB6(IN int TEST);
void sub_test_SUB7(IN int TEST);
void sub_test_SUB8(IN int TEST);
void sub_test_SUB9(IN int TEST);

void test_SUB(IN int TEST);

void test_MUL_AB(int TEST);
void test_MULC(int TEST);

/* MUL Accuracy Verification */
void sub_test_MUL1_1(IN int TEST);
void sub_test_MUL1_2(IN int TEST);
void sub_test_MUL1_3(IN int TEST);
void sub_test_MUL2(IN int TEST);
void sub_test_MUL3(IN int TEST);
void sub_test_MUL4(IN int TEST);
void sub_test_MUL5(IN int TEST);
void sub_test_MUL6(IN int TEST);

void test_MUL(IN int TEST);

/* karatsuba MUL Accuracy Verification */
void sub_test_KMUL1_1(IN int TEST);
void sub_test_KMUL1_2(IN int TEST);
void sub_test_KMUL1_3(IN int TEST);
void sub_test_KMUL2(IN int TEST);
void sub_test_KMUL3(IN int TEST);
void sub_test_KMUL4(IN int TEST);
void sub_test_KMUL5(IN int TEST);
void sub_test_KMUL6(IN int TEST);
void sub_test_KMUL6_2(int TEST);
void sub_test_KMUL6_3(int TEST);
void sub_test_KMUL6_4(int TEST);

void test_KMUL(IN int TEST);

void test_SQU_A(int TEST);
void test_SQUC(int TEST);

/* SQU Accuracy Verification */
void sub_test_SQU1_1(IN int TEST);
void sub_test_SQU1_2(IN int TEST);
void sub_test_SQU1_3(IN int TEST);
void sub_test_SQU2(IN int TEST);

void test_SQU(IN int TEST);

/* LEFT SHIFT TEST */
void test_bi_word_lshift(int TEST);
void test_bi_word_lshift2(int TEST);
void test_bi_lshift(int TEST);

#endif