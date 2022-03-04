#include "../includes/bi.h"
#include "../includes/bi_op.h"

void sage_show_sub(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);
    printf("if (C != A - B):\n");
    printf("    print(\"{} : {}\".format(%d, A - B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

// Case 1: A = B ,C = 0
void sub_test_SUB1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1: A = B ,C = 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        bi_new(&B, 1);

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 2: A = 0, C = -B
void sub_test_SUB2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 2: A = 0, C = -B ###\\n\")\n");
    printf("cnt = 0\n");
    for (int j = 0; j < TEST; j++)
    {
        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_new(&A, 1);
        bi_gen_rand(&B, sign2, num2);

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 3: B = 0, C = -A
void sub_test_SUB3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 3: B = 0, C = -A ###\\n\")\n");
    printf("cnt = 0\n");
    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_new(&B, 1);

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 4: 0 < B ≤ A,  C = A - B
void sub_test_SUB4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 4: 0 < B ≤ A,  C = A - B ###\\n\")\n");
    printf("cnt = 0\n");
    for (int j = 0; j < TEST; j++)
    {
        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, NON_NEGATIVE, num1);
            bi_gen_rand(&B, NON_NEGATIVE, num2);

            if (bi_cmp(A, B) == 1)
                break;
        }

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 5: 0 < A < B,  -C = B - A
void sub_test_SUB5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 5: 0 < A < B,  -C = B - A ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, NON_NEGATIVE, num1);
            bi_gen_rand(&B, NON_NEGATIVE, num2);

            if (bi_cmp(A, B) == -1)
                break;
        }

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 6: 0 > A ≥ B,  C = |B| - |A|
void sub_test_SUB6(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6: 0 > A ≥ B,  C = |B| - |A| ###\\n\")\n");
    printf("cnt = 0\n");
    for (int j = 0; j < TEST; j++)
    {
        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, NEGATIVE, num1);
            bi_gen_rand(&B, NEGATIVE, num2);

            if (bi_cmp(A, B) == 1)
                break;
        }

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 7: 0 > B > A,  C = |B| - |A|
void sub_test_SUB7(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 7: 0 > B > A,  C = |B| - |A| ###\\n\")\n");
    printf("cnt = 0\n");
    for (int j = 0; j < TEST; j++)
    {
        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, NEGATIVE, num1);
            bi_gen_rand(&B, NEGATIVE, num2);

            if (bi_cmp(A, B) == -1)
                break;
        }

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}
// Case 8: A > 0 and B < 0
void sub_test_SUB8(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 8: A > 0 and B < 0 ###\\n\")\n");
    printf("cnt = 0\n");
    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NEGATIVE, num2);

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 9: A < 0 and B > 0
void sub_test_SUB9(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 9: A < 0 and B > 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_sub(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

void test_SUB(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int Case = 9;

    printf("print(\"### SUB TEST ###\")\n");

    sub_test_SUB1(&C, A, B, TEST / Case);
    sub_test_SUB2(&C, A, B, TEST / Case);
    sub_test_SUB3(&C, A, B, TEST / Case);
    sub_test_SUB4(&C, A, B, TEST / Case);
    sub_test_SUB5(&C, A, B, TEST / Case);
    sub_test_SUB6(&C, A, B, TEST / Case);
    sub_test_SUB7(&C, A, B, TEST / Case);
    sub_test_SUB8(&C, A, B, TEST / Case);
    sub_test_SUB9(&C, A, B, TEST / Case);
}

/////////// END SUB TEST /////////////
