#include "../includes/bi.h"
#include "../includes/bi_op.h"

void sage_show_mul(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);
    printf("if (C != A * B):\n");
    printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void test_MUL_AB(int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 1);
        bi_gen_rand(&B, NON_NEGATIVE, 1);

        bi_print("A", A);

        bi_print("B", B);

        bi_MUL_AB(&C, A->a[0], B->a[0]);
        bi_print("C", C);

        printf("print(A * B == C) #%d\n", j);
        printf("print(hex(A*B))\n");
    }
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

void test_MULC(int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    // bi_MULC TEST
    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_mul_core(&C, A, B);

        bi_print("A", A);

        bi_print("B", B);

        bi_print("C", C);

        printf("print(A * B == C) #%d\n", j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// MUL 껍데기함수 검증

// Case 1_1: A = 0 then C = 0 * B
void sub_test_MUL1_1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_1: A = 0 then C = 0 * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 1_2: B = 0 then C = A * 0
void sub_test_MUL1_2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_2: B = 0 then C = A * 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);

        bi_new(&B, 1);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 1_3: A = 0 and B = 0 then C = 0 * 0
void sub_test_MUL1_3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_3: A = 0 and B = 0 then C = 0 * 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        bi_new(&A, 1);
        bi_new(&B, 1);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 2: A = 1 then C = 1 * B
void sub_test_MUL2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 2: A = 1 then C = 1 * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 3: A = -1 then C = -(1) * B
void sub_test_MUL3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 3: A = -1 then C = -(1) * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        A->sign = NEGATIVE;

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 4: B = 1 then C = 1 * A
void sub_test_MUL4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 4: B = 1 then C = 1 * A ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_new(&B, 1);
        B->a[0] = 1;

        bi_gen_rand(&A, sign1, num1);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 5: B = -1 then C = -(1) * A
void sub_test_MUL5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 5: B = -1 then C = -(1) * A ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_new(&B, 1);
        B->a[0] = 1;
        B->sign = NEGATIVE;

        bi_gen_rand(&A, sign1, num1);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 6: Otherwise
void sub_test_MUL6(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6: Otherwise ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_mul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

void test_MUL(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int Case = 6;

    printf("print(\"### MUL TEST ###\")\n");

    sub_test_MUL1_1(&C, A, B, TEST / Case);
    sub_test_MUL1_2(&C, A, B, TEST / Case);
    sub_test_MUL1_3(&C, A, B, TEST / Case);
    sub_test_MUL2(&C, A, B, TEST / Case);
    sub_test_MUL3(&C, A, B, TEST / Case);
    sub_test_MUL4(&C, A, B, TEST / Case);
    sub_test_MUL5(&C, A, B, TEST / Case);
    sub_test_MUL6(&C, A, B, TEST / Case);
}
