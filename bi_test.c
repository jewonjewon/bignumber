#include "bi_local.h"
#include "bi_operation.h"
#include "bi_test.h"

// Case: A = 0, C = B
void py_test_ADD1(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_new(&A, 1);
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

// Case: B = 0, C = A
void py_test_ADD2(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_new(&B, 1);

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

// Case: A > 0 and B < 0, C = A - |B|
void py_test_ADD3(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NON_NEGATIVE;
        int sign2 = NEGATIVE;
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
// Case: A < 0 and B > 0, C = B - |A|
void py_test_ADD4(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NEGATIVE;
        int sign2 = NON_NEGATIVE;
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
// Case: wordlen(A) ≥ wordlen(B)
void py_test_ADD5(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int num1 = 0;
    int num2 = 0;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
                break;
        }

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign1, num2);

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

// Case: wordlen(A) < wordlen(B)
void py_test_ADD6(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int num1 = 0;
    int num2 = 0;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 < num2)
                break;
        }

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign1, num2);

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

void py_test_ADD(IN int TEST)
{
    int Case = 6;

    printf("\n\n\n\n\n### ADD TEST ###\n");

    py_test_ADD1(TEST / Case);
    py_test_ADD2(TEST / Case);
    py_test_ADD3(TEST / Case);
    py_test_ADD4(TEST / Case);
    py_test_ADD5(TEST / Case);
    py_test_ADD6(TEST / Case);
}

// Case 1: A = B ,C = 0
void py_test_SUB1(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        bi_new(&B, 1);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 2: A = 0, C = -B
void py_test_SUB2(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_new(&A, 1);
        bi_gen_rand(&B, sign2, num2);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);

        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 3: B = 0, C = -A
void py_test_SUB3(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_new(&B, 1);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 4: 0 < B ≤ A,  C = A - B
void py_test_SUB4(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NON_NEGATIVE;
        int sign2 = NON_NEGATIVE;

        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, sign1, num1);
            bi_gen_rand(&B, sign2, num2);

            if (bi_cmp(A, B) == 1)
                break;
        }

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 5: 0 < A < B,  -C = B - A
void py_test_SUB5(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NON_NEGATIVE;
        int sign2 = NON_NEGATIVE;

        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, sign1, num1);
            bi_gen_rand(&B, sign2, num2);

            if (bi_cmp(A, B) == -1)
                break;
        }

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 6: 0 > A ≥ B,  C = |B| - |A|
void py_test_SUB6(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NEGATIVE;
        int sign2 = NEGATIVE;

        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, sign1, num1);
            bi_gen_rand(&B, sign2, num2);

            if (bi_cmp(A, B) == 1)
                break;
        }

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
// Case 7: 0 > B > A,  C = |B| - |A|
void py_test_SUB7(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NEGATIVE;
        int sign2 = NEGATIVE;

        int num1 = 0;
        int num2 = 0;

        while (1)
        {
            int num1 = rand() % 0x0f + 1;
            int num2 = rand() % 0x0f + 1;

            bi_gen_rand(&A, sign1, num1);
            bi_gen_rand(&B, sign2, num2);

            if (bi_cmp(A, B) == -1)
                break;
        }

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
// Case 8: A > 0 and B < 0
void py_test_SUB8(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NON_NEGATIVE;
        int sign2 = NEGATIVE;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 9: A < 0 and B > 0
void py_test_SUB9(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NEGATIVE;
        int sign2 = NON_NEGATIVE;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);

        bi_SUB(&C, A, B);
        printf("C = ");
        bi_print(C);
        printf("print(A - B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void py_test_SUB(IN int TEST)
{
    int Case = 9;

    printf("\n\n\n\n\n### SUB TEST ###\n");

    py_test_SUB1(TEST / Case);
    py_test_SUB2(TEST / Case);
    py_test_SUB3(TEST / Case);
    py_test_SUB4(TEST / Case);
    py_test_SUB5(TEST / Case);
    py_test_SUB6(TEST / Case);
    py_test_SUB7(TEST / Case);
    py_test_SUB8(TEST / Case);
    py_test_SUB9(TEST / Case);
}
