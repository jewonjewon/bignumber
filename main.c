#include <stdio.h>

#include "bi_local.h"
#include "bi_op.h"
#include "bi_test.h"

void test_bi_word_rshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
        int num1 = rand() % 0x0f + 1;
        // int x = 2;
        bi_gen_rand(&A, NON_NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_word_rshift(&A, x);

        printf("C = ");
        bi_print(A);

        printf("print(A >> (%d * %d) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

void test_MULC_karastuba(int TEST)
{
    printf("\n\n\n\n\n### 카라츄바 테스트\n\n");
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    // bi_MULC_karastuba TEST
    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, 20);
        bi_gen_rand(&B, NON_NEGATIVE, 20);
        bi_MULC_karatsuba(&C, A, B);
        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);

        printf("print(A * B == C) #%d\n", j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_bi_word_reduction(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_word_reduction(&A, x);
        printf("C = ");
        bi_print(A);
        printf("print(A %% (2 ** (%d * %d)) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

int main()
{
    srand((unsigned)time(NULL));

    // test_ADD(6);
    // test_SUB(900);
    // test_MUL(100);
    // test_SQU(100);

    // test_bi_lshift(10000);
    // test_SQU_A(100);

    // test_SQUC(1);
    // test_MULC(1);

    // test_bi_word_rshift(10);
    // test_MULC_karastuba(100);
    // test_KMUL(5000);
    test_KSQU(100);
    // test_bi_word_reduction(1);

    // // 시간 측정
    // printf("SHIFT 함수 시간 측정\n");
    // int cnt = 1000000;

    // double start1, start2;
    // double end1, end2;

    // start1 = (double)clock() / CLOCKS_PER_SEC;
    // test_bi_word_lshift1(cnt);
    // end1 = (((double)clock()) / CLOCKS_PER_SEC);

    // start2 = (double)clock() / CLOCKS_PER_SEC;
    // test_bi_word_lshift2(cnt);
    // end2 = (((double)clock()) / CLOCKS_PER_SEC);

    // printf("%.0d번 수행 기준\n\n", cnt);

    // printf("1번 함수 수행 시간 :%lf\n", (end1 - start1));
    // printf("2번 함수 수행 시간 :%lf\n", (end2 - start2));

    return 0;
}
