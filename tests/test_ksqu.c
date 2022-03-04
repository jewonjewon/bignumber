#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/bi_test.h"

// Case 1_1: A = 0
void sub_test_KSQU1_1(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_1: A = 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        bi_ksqu(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

// Case 1_2: A = 1
void sub_test_KSQU1_2(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_2: A = 1 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        bi_ksqu(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

// Case 1_3: A = -1
void sub_test_KSQU1_3(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_3: A = -1 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        A->sign = NEGATIVE;
        bi_ksqu(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

// Case 2: Otherwise
void sub_test_KSQU2(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### Case 2: Otherwise ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_ksqu(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
}

void test_KSQU(IN int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    // int Case = 6;
    int Case = 4;
    printf("\n\n\n\n\n### KSQU TEST ###\n");

    sub_test_KSQU1_1(&C, A, TEST / Case);
    sub_test_KSQU1_2(&C, A, TEST / Case);
    sub_test_KSQU1_3(&C, A, TEST / Case);
    sub_test_KSQU2(&C, A, TEST / Case);
}
