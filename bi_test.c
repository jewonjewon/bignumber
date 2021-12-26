#include "bi_local.h"
#include "bi_op.h"
#include "bi_test.h"

// Case 1: A = 0, C = B
void sub_test_ADD1(IN int TEST)
{
    printf("\n### Case 1: A = 0, C = B ###\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_new(&A, 1);
        bi_gen_rand(&B, sign2, num2);

        bi_ADD(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 2: B = 0, C = A
void sub_test_ADD2(IN int TEST)
{
    printf("\n### Case 2: B = 0, C = A ###\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_new(&B, 1);

        bi_ADD(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 3: A > 0 and B < 0, C = A - |B|
void sub_test_ADD3(IN int TEST)
{
    printf("\n### Case 3: A > 0 and B < 0, C = A - |B| ###\n");

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

        bi_ADD(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
// Case 4: A < 0 and B > 0, C = B - |A|
void sub_test_ADD4(IN int TEST)
{
    printf("\n### Case 4: A < 0 and B > 0, C = B - |A| ###\n");

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

        bi_ADD(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
// Case 5: wordlen(A) ≥ wordlen(B)
void sub_test_ADD5(IN int TEST)
{
    printf("\n### Case 5: wordlen(A) ≥ wordlen(B) ###\n");

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

        //
        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        //

        bi_ADD(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

// Case 6: wordlen(A) < wordlen(B)
void sub_test_ADD6(IN int TEST)
{
    printf("\n### Case 6: wordlen(A) < wordlen(B) ###\n");

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

        bi_ADD(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("print(A + B == C) #%d\n", j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_ADD(IN int TEST)
{
    int Case = 6;

    printf("\n\n\n\n\n### ADD TEST ###\n");

    sub_test_ADD1(TEST / Case);
    sub_test_ADD2(TEST / Case);
    sub_test_ADD3(TEST / Case);
    sub_test_ADD4(TEST / Case);
    sub_test_ADD5(TEST / Case);
    sub_test_ADD6(TEST / Case);
}

// Case 1: A = B ,C = 0
void sub_test_SUB1(IN int TEST)
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
void sub_test_SUB2(IN int TEST)
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
void sub_test_SUB3(IN int TEST)
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
void sub_test_SUB4(IN int TEST)
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
void sub_test_SUB5(IN int TEST)
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
void sub_test_SUB6(IN int TEST)
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
void sub_test_SUB7(IN int TEST)
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
void sub_test_SUB8(IN int TEST)
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
void sub_test_SUB9(IN int TEST)
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

void test_SUB(IN int TEST)
{
    int Case = 9;

    printf("\n\n\n\n\n### SUB TEST ###\n");

    sub_test_SUB1(TEST / Case);
    sub_test_SUB2(TEST / Case);
    sub_test_SUB3(TEST / Case);
    sub_test_SUB4(TEST / Case);
    sub_test_SUB5(TEST / Case);
    sub_test_SUB6(TEST / Case);
    sub_test_SUB7(TEST / Case);
    sub_test_SUB8(TEST / Case);
    sub_test_SUB9(TEST / Case);
}

/////////// SUB /////////////

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

        bi_MULC(&C, A, B);

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

// Case 1_1: A = 0 then C = 0 * B
void sub_test_MUL1_1(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_MUL(&C, A, B);

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

// Case 1_2: B = 0 then C = A * 0
void sub_test_MUL1_2(IN int TEST)
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

        bi_MUL(&C, A, B);

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

// Case 1_3: A = 0 and B = 0 then C = 0 * 0
void sub_test_MUL1_3(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        bi_new(&A, 1);
        bi_new(&B, 1);

        bi_MUL(&C, A, B);

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

// Case 2: A = 1 then C = 1 * B
void sub_test_MUL2(IN int TEST)
{
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

        bi_MUL(&C, A, B);

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

// Case 3: A = -1 then C = -(1) * B
void sub_test_MUL3(IN int TEST)
{
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

        bi_MUL(&C, A, B);

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

// Case 4: B = 1 then C = 1 * A
void sub_test_MUL4(IN int TEST)
{
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

        bi_MUL(&C, A, B);

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

// Case 5: B = -1 then C = -(1) * A
void sub_test_MUL5(IN int TEST)
{
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

        bi_MUL(&C, A, B);

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

// Case 6: Otherwise
void sub_test_MUL6(int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_MUL(&C, A, B);

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

void test_MUL(IN int TEST)
{
    int Case = 6;

    printf("\n\n\n\n\n### MUL TEST ###\n");

    sub_test_MUL1_1(TEST / Case);
    sub_test_MUL1_2(TEST / Case);
    sub_test_MUL1_3(TEST / Case);
    sub_test_MUL2(TEST / Case);
    sub_test_MUL3(TEST / Case);
    sub_test_MUL4(TEST / Case);
    sub_test_MUL5(TEST / Case);
    sub_test_MUL6(TEST / Case);
}

void test_SQU_A(int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 1);

        bi_SQU_A(&C, A->a[0]);

        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }

    bi_delete(&A);
    bi_delete(&C);
}

void test_SQUC(int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    // bi_SQUC TEST
    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        bi_SQUC(&C, A);

        printf("A = ");
        bi_print(A);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }
    bi_delete(&A);
    bi_delete(&C);
}

// Case 1_1: A = 0
void sub_test_SQU1_1(IN int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        bi_SQU(&C, A);

        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }

    bi_delete(&A);
    bi_delete(&C);
}

// Case 1_1: A = 1
void sub_test_SQU1_2(IN int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        bi_SQU(&C, A);

        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }

    bi_delete(&A);
    bi_delete(&C);
}
// Case 1_1: A = -1
void sub_test_SQU1_3(IN int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        A->sign = NEGATIVE;
        bi_SQU(&C, A);

        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }

    bi_delete(&A);
    bi_delete(&C);
}

void sub_test_SQU2(IN int TEST)
{
    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);

        bi_SQU(&C, A);

        printf("A = ");
        bi_print(A);

        printf("C = ");
        bi_print(C);

        printf("print(\"{} : {}\".format(%d, A ** %d == C)) #%d\n", j, 2, j);
    }
    bi_delete(&A);
    bi_delete(&C);
}

void test_SQU(IN int TEST)
{
    int Case = 4;
    printf("\n\n\n\n\n### SQU TEST ###\n");

    sub_test_SQU1_1(TEST / Case);
    sub_test_SQU1_2(TEST / Case);
    sub_test_SQU1_3(TEST / Case);
    sub_test_SQU2(TEST / Case);
}

void test_bi_word_lshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
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
void test_bi_lshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xff;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_lshift(&A, x);
        printf("C = ");
        bi_print(A);
        printf("print(\"{} : {}\".format(%d, A << %d == C)) #%d\n", j, x, j);
    }

    bi_delete(&A);
}