#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"

// MUL 껍데기함수 검증

// Case 1_1: A = 0 then C = 0 * B
void sub_test_KMUL1_1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_1: A = 0 then C = 0 * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 1_2: B = 0 then C = A * 0
void sub_test_KMUL1_2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_2: B = 0 then C = A * 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);

        bi_new(&B, 1);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 1_3: A = 0 and B = 0 then C = 0 * 0
void sub_test_KMUL1_3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_3: A = 0 and B = 0 then C = 0 * 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        bi_new(&A, 1);
        bi_new(&B, 1);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 2: A = 1 then C = 1 * B
void sub_test_KMUL2(bigint **C, bigint *A, bigint *B, IN int TEST)
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

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 3: A = -1 then C = -(1) * B
void sub_test_KMUL3(bigint **C, bigint *A, bigint *B, IN int TEST)
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

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 4: B = 1 then C = 1 * A
void sub_test_KMUL4(bigint **C, bigint *A, bigint *B, IN int TEST)
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

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 5: B = -1 then C = -(1) * A
void sub_test_KMUL5(bigint **C, bigint *A, bigint *B, IN int TEST)
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

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 6_1: Otherwise
void sub_test_KMUL6_1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_1: Otherwise\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;
        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);
        // bi_gen_rand(&A, sign1, num1);
        // bi_gen_rand(&B, sign2, num2);
        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        // bi_gen_rand(&A, NON_NEGATIVE, num1);
        // bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 6_2: wordlen(A) == wordlen(B)
void sub_test_KMUL6_2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_2: wordlen(A) == wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num1);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 6_3: wordlen(A) > wordlen(B) and sign(A) = sign(B) = NON_NEGATIVE
void sub_test_KMUL6_3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_3: wordlen(A) > wordlen(B) and sign(A) = sign(B) = NON_NEGATIVE\\n\")\n");
    printf("cnt = 0\n");

    int num1 = 0;
    int num2 = 0;

    for (int j = 0; j < TEST; j++)
    {
        do
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;
        } while (num1 >= num2);

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 6_4: wordlen(A) < wordlen(B)
void sub_test_KMUL6_4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_4: wordlen(A) < wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    int num1 = 0;
    int num2 = 0;

    for (int j = 0; j < TEST; j++)
    {
        do
        {
            num1 = rand() % 0x0f + 2;
            num2 = rand() % 0x0f + 1;
        } while (num1 <= num2);

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_MULC_karatsuba(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

// Case 6_5:  A < B < 0
void sub_test_KMUL6_5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_5: 0 < A < B \\n\")\n");
    printf("cnt = 0\n");

    int num1 = 0;
    int num2 = 0;

    for (int j = 0; j < TEST; j++)
    {
        do
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;
        } while (num1 < num2);

        bi_gen_rand(&A, NEGATIVE, num1);
        bi_gen_rand(&B, NEGATIVE, num2);

        bi_KMUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
}

void test_KMUL(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int Case = 6;

    printf("print(\"### KMUL TEST ###\")\n");

    sub_test_KMUL1_1(&C, A, B, TEST / Case);
    sub_test_KMUL1_2(&C, A, B, TEST / Case);
    sub_test_KMUL1_3(&C, A, B, TEST / Case);
    sub_test_KMUL2(&C, A, B, TEST / Case);
    sub_test_KMUL3(&C, A, B, TEST / Case);
    sub_test_KMUL4(&C, A, B, TEST / Case);
    sub_test_KMUL5(&C, A, B, TEST / Case);
    sub_test_KMUL6_1(&C, A, B, TEST / Case);
    sub_test_KMUL6_2(&C, A, B, TEST / Case);
    sub_test_KMUL6_3(&C, A, B, TEST / Case);
    sub_test_KMUL6_4(&C, A, B, TEST / Case);
    sub_test_KMUL6_5(&C, A, B, TEST / Case);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
//
//
//
////

// Case 6_1: sign(A) == NEGATIVE
void sub_test_KSQU6_1(int TEST)
{
    printf("print(\"### Case 6_1: sign(A) == NEGATIVE \\n\")\n");
    printf("cnt = 0\n");
    bigint *A = NULL;
    bigint *C = NULL;

    int num1 = 0;

    for (int j = 0; j < TEST; j++)
    {

        num1 = rand() % 0x0f + 2;

        bi_gen_rand(&A, NEGATIVE, num1);

        printf("a = ");
        bi_print(A);

        bi_SQUC_karatsuba(&C, A);
        printf("A = ");
        bi_print(A);

        printf("C = ");
        bi_print(C);
        printf("if (C != A ** 2):\n");
        printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");

    bi_delete(&A);
    bi_delete(&C);
}

// Case 6_2: wordlen(A) < wordlen(B)
void sub_test_KSQU6_2(int TEST)
{
    printf("print(\"### Case 6_2: sign(A) == NON-NEGATIVE \\n\")\n");
    printf("cnt = 0\n");
    bigint *A = NULL;
    bigint *C = NULL;

    int num1 = 0;

    for (int j = 0; j < TEST; j++)
    {

        num1 = rand() % 0x0f + 2;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        printf("a = ");
        bi_print(A);

        bi_SQUC_karatsuba(&C, A);
        printf("A = ");
        bi_print(A);

        printf("C = ");
        bi_print(C);
        printf("if (C != A ** 2):\n");
        printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");

    bi_delete(&A);
    bi_delete(&C);
}

void test_KSQU(IN int TEST)
{
    // int Case = 6;
    int Case = 10;
    printf("\n\n\n\n\n### SQU TEST ###\n");

    // sub_test_KSQU1_1((TEST / Case) % 5);
    // sub_test_KSQU1_2((TEST / Case) % 5);
    // sub_test_KSQU1_3((TEST / Case) % 5);
    // sub_test_KSQU2((TEST / Case) % 5);
    // sub_test_KSQU3((TEST / Case) % 5);
    // sub_test_KSQU4((TEST / Case) % 5);
    // sub_test_KSQU5((TEST / Case) % 5);
    // sub_test_KSQU6(TEST / Case);
    sub_test_KSQU6_1(TEST / Case);
    sub_test_KSQU6_2(TEST / Case);
}
