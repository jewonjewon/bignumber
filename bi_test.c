#include "bi_local.h"
#include "bi_operation.h"
#include "bi_test.h"

void py_test_ADD(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    int c = 0;

    printf("\n\n\n\n\n### ADD TEST ###\n");

    for (int j = 0; j < TEST; j++)
    {

        int sign1 = rand() % 0x02;
        int sign2 = rand() % 0x02;
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_ADD(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void py_test_SUB(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    int b = 0;

    printf("\n\n\n\n\n### SUB TEST ###\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 5);
        printf("A = ");
        bi_print(A);
        bi_gen_rand(&B, NON_NEGATIVE, 2);
        printf("B = ");
        bi_print(B);

        bi_SUBC(&C, A, B);
        printf("C = ");
        bi_print(C);

        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}