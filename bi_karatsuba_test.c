#include "bi_local.h"
#include "bi_op.h"
#include "bi_test.h"

// Case 1_1: A = 0 then C = 0 * B
void sub_test_KMUL1_1(IN int TEST)
{
    printf("print(\"### Case 1_1\\n\")\n");
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 1_2: B = 0 then C = A * 0
void sub_test_KMUL1_2(IN int TEST)
{
    printf("print(\"### Case 1_2\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);

        bi_new(&B, 1);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 1_3: A = 0 and B = 0 then C = 0 * 0
void sub_test_KMUL1_3(IN int TEST)
{
    printf("print(\"### Case 1_3\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        bi_new(&A, 1);
        bi_new(&B, 1);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 2: A = 1 then C = 1 * B
void sub_test_KMUL2(IN int TEST)
{
    printf("print(\"### Case 2\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 3: A = -1 then C = -(1) * B
void sub_test_KMUL3(IN int TEST)
{
    printf("print(\"### Case 3\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        A->sign = NEGATIVE;

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 4: B = 1 then C = 1 * A
void sub_test_KMUL4(IN int TEST)
{
    printf("print(\"### Case 4\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_new(&B, 1);
        B->a[0] = 1;

        bi_gen_rand(&A, sign1, num1);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 5: B = -1 then C = -(1) * A
void sub_test_KMUL5(IN int TEST)
{
    printf("print(\"### Case 5\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_new(&B, 1);
        B->a[0] = 1;
        B->sign = NEGATIVE;

        bi_gen_rand(&A, sign1, num1);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 6: Otherwise
void sub_test_KMUL6(int TEST)
{
    printf("print(\"### Case 6\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        // bi_gen_rand(&A, sign1, num1);
        // bi_gen_rand(&B, sign2, num2);

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        printf("a = ");
        bi_print(A);

        printf("b = ");
        bi_print(B);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);
        printf("if (C != A * B):\n");
        printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 6_2: wordlen(A) == wordlen(B)
void sub_test_KMUL6_2(int TEST)
{
    printf("print(\"### Case 6_2: wordlen(A) == wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num1);

        printf("a = ");
        bi_print(A);

        printf("b = ");
        bi_print(B);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);
        printf("if (C != A * B):\n");
        printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 6_3: wordlen(A) > wordlen(B)
void sub_test_KMUL6_3(int TEST)
{
    printf("print(\"### Case 6_3: wordlen(A) > wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
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

        printf("a = ");
        bi_print(A);

        printf("b = ");
        bi_print(B);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);
        printf("if (C != A * B):\n");
        printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 6_4: wordlen(A) < wordlen(B)
void sub_test_KMUL6_4(int TEST)
{
    printf("print(\"### Case 6_4: wordlen(A) < wordlen(B)\\n\")\n");
    printf("cnt = 0\n");
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

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

        printf("%d, %d\n", num1, num2);

        printf("a = ");
        bi_print(A);

        printf("b = ");
        bi_print(B);

        bi_MULC_karatsuba(&C, A, B);

        printf("A = ");
        bi_print(A);

        printf("B = ");
        bi_print(B);

        printf("C = ");
        bi_print(C);
        printf("if (C != A * B):\n");
        printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_KMUL(IN int TEST)
{
    // int Case = 6;
    int Case = 10;
    printf("\n\n\n\n\n### MUL TEST ###\n");

    sub_test_KMUL1_1((TEST / Case) % 5);
    sub_test_KMUL1_2((TEST / Case) % 5);
    sub_test_KMUL1_3((TEST / Case) % 5);
    sub_test_KMUL2((TEST / Case) % 5);
    sub_test_KMUL3((TEST / Case) % 5);
    sub_test_KMUL4((TEST / Case) % 5);
    sub_test_KMUL5((TEST / Case) % 5);
    sub_test_KMUL6(TEST / Case);
    sub_test_KMUL6_2(TEST / Case);
    sub_test_KMUL6_3(TEST / Case);
    sub_test_KMUL6_4(TEST / Case);
}

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
