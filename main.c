#include <stdio.h>

#include "bi_local.h"
#include "bi_op.h"
#include "bi_test.h"

void test_MUL_AB(int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 1);
        bi_gen_rand(&B, NON_NEGATIVE, 1);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        bi_MUL_AB(&C, A->a[0], B->a[0]);
        printf("C = ");
        bi_print(C);

        printf("print(A * B == C) #%d\n", j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_bi_word_lshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_word_lshift(&A, x);
        printf("C = ");
        bi_print(A);

        printf("print(A << (%d * %d) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

// void test_MULC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     bigint *C = NULL;

//     // bi_MULC TEST
//     for (int j = 0; j < TEST; j++)
//     {
//         int num1 = rand() % 0x0f + 1;
//         int num2 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num2);

//         bi_MULC(&C, A, B);

//         printf("A = ");
//         bi_print(A);

//         printf("B = ");
//         bi_print(B);

//         printf("C = ");
//         bi_print(C);

//         printf("print(A * B == C) #%d\n", j);
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&C);
// }

int main()
{
    srand((unsigned)time(NULL));
    // py_test_ADD(1000);
    // py_test_SUB(1000);
    // test_MULC(100);
    // py_test_MUL(100);

    return 0;
}
