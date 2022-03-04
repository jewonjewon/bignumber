#include "../includes/bi.h"
#include "../includes/bi_op.h"

void sage_show_squ(bigint **C, bigint *A, int j)
{
    bi_print("A", A);
    bi_print("C", *C);
    printf("if (C != A ** 2):\n");
    printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}
void test_SQU_A(int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 1);

        bi_SQU_A(&C, A->a[0]);

        bi_print("A", A);
        bi_print("C", C);
        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }

    bi_delete(&A);
    bi_delete(&C);
}

void test_SQUC(int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    // bi_squ_core TEST
    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        bi_squ_core(&C, A);

        bi_print("A", A);

        bi_print("C", C);

        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }
    bi_delete(&A);
    bi_delete(&C);
}

// Case 1_1: A = 0
void sub_test_SQU1_1(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_1: A = 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        bi_squ(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

// Case 1_2: A = 1
void sub_test_SQU1_2(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_2: A = 1 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        bi_squ(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

// Case 1_3: A = -1
void sub_test_SQU1_3(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_3: A = -1 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        A->sign = NEGATIVE;
        bi_squ(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

// Case 2: Otherwise
void sub_test_SQU2(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### Case 2: Otherwise ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_squ(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

void test_SQU(IN int TEST)
{
    int Case = 4;
    printf("print(\"### SQU TEST ###\")\n");

    bigint *A = NULL;
    bigint *C = NULL;

    sub_test_SQU1_1(&C, A, TEST / Case);
    sub_test_SQU1_2(&C, A, TEST / Case);
    sub_test_SQU1_3(&C, A, TEST / Case);
    sub_test_SQU2(&C, A, TEST / Case);
}
