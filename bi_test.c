#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"

void sage_show_add(bigint **C, bigint *A, bigint *B, int j)
{
    printf("A = ");
    bi_print(A);
    printf("B = ");
    bi_print(B);
    printf("C = ");
    bi_print(*C);
    printf("if (C != A + B):\n");
    printf("    print(\"Error: A + B, %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"A + B = {}\".format(hex(A+B)))\n");
    // printf("    print(\"{} : {}\".format(%d, A + B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_sub(bigint **C, bigint *A, bigint *B, int j)
{
    printf("A = ");
    bi_print(A);
    printf("B = ");
    bi_print(B);
    printf("C = ");
    bi_print(*C);
    printf("if (C != A - B):\n");
    printf("    print(\"{} : {}\".format(%d, A - B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_mul(bigint **C, bigint *A, bigint *B, int j)
{
    printf("A = ");
    bi_print(A);
    printf("B = ");
    bi_print(B);
    printf("C = ");
    bi_print(*C);
    printf("if (C != A * B):\n");
    printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_squ(bigint **C, bigint *A, int j)
{
    printf("A = ");
    bi_print(A);
    printf("C = ");
    bi_print(*C);
    printf("if (C != A ** 2):\n");
    printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_div(bigint **Q, bigint **R, bigint *A, bigint *B, int j)
{
    printf("A = ");
    bi_print(A);
    printf("B = ");
    bi_print(B);
    printf("Q = ");
    bi_print(*Q);
    printf("R = ");
    bi_print(*R);
    printf("if ((Q != A // B) and (Q != A %% B)):\n");
    printf("    print(\"{} : {}\".format(%d, A // B == Q)) #%d\n", j, j);
    printf("    print(\"{} : {}\".format(%d, A %% B == R)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_exp(bigint **C, bigint *A, int j)
{
    printf("A = ");
    bi_print(A);
    printf("C = ");
    bi_print(*C);
    printf("if (C != A ** 2):\n");
    printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void bi_delete_3(bigint **C, bigint **A, bigint **B)
{
    bi_delete(C);
    bi_delete(A);
    bi_delete(B);
}

void bi_delete_2(bigint **C, bigint **A)
{
    bi_delete(C);
    bi_delete(A);
}

/////
/////
/////
/////
/////

// Case 1: A = 0, C = B
void sub_test_ADD1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1: A = 0, C = B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_new(&A, 1);
        bi_gen_rand(&B, sign2, num2);

        bi_ADD(C, A, B);
        sage_show_add(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 2: B = 0, C = A
void sub_test_ADD2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 2: B = 0, C = A ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_new(&B, 1);

        bi_ADD(C, A, B);

        sage_show_add(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 3: A > 0 and B < 0, C = A - |B|
void sub_test_ADD3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 3: A > 0 and B < 0, C = A - |B| ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NON_NEGATIVE;
        int sign2 = NEGATIVE;
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_ADD(C, A, B);

        sage_show_add(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 4: A < 0 and B > 0, C = B - |A|
void sub_test_ADD4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 4: A < 0 and B > 0, C = B - |A| ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        do
        {
            bi_gen_rand(&A, NEGATIVE, num1);
            bi_gen_rand(&B, NON_NEGATIVE, num2);
        } while (bi_is_zero(B) == true);

        bi_ADD(C, A, B);
        sage_show_add(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}
// Case 5: wordlen(A) ≥ wordlen(B)
void sub_test_ADD5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 5: wordlen(A) ≥ wordlen(B) ###\\n\")\n");
    printf("cnt = 0\n");

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

        bi_ADD(C, A, B);
        //
        B->sign = NEGATIVE;
        sage_show_add(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 6: wordlen(A) < wordlen(B)
void sub_test_ADD6(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6: wordlen(A) < wordlen(B) ###\\n\")\n");
    printf("cnt = 0\n");

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

        bi_ADD(C, A, B);

        sage_show_add(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

void test_ADD(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int Case = 6;

    printf("print(\"### ADD TEST ###\")\n");

    sub_test_ADD1(&C, A, B, TEST / Case);
    sub_test_ADD2(&C, A, B, TEST / Case);
    sub_test_ADD3(&C, A, B, TEST / Case);
    sub_test_ADD4(&C, A, B, TEST / Case);
    sub_test_ADD5(&C, A, B, TEST / Case);
    sub_test_ADD6(&C, A, B, TEST / Case);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_SUB(C, A, B);
        sage_show_sub(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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
        printf("print(hex(A*B))\n");
    }
    bi_delete_3(&C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);

    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
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

        bi_MUL(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

void test_MUL(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int Case = 6;

    printf("print(\"### MUL TEST ###\")\n");

    // sub_test_MUL1_1(&C, A, B, TEST / Case);
    // sub_test_MUL1_2(&C, A, B, TEST / Case);
    // sub_test_MUL1_3(&C, A, B, TEST / Case);
    // sub_test_MUL2(&C, A, B, TEST / Case);
    // sub_test_MUL3(&C, A, B, TEST / Case);
    // sub_test_MUL4(&C, A, B, TEST / Case);
    // sub_test_MUL5(&C, A, B, TEST / Case);
    sub_test_MUL6(&C, A, B, TEST / Case);
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
void sub_test_SQU1_1(bigint **C, bigint *A, IN int TEST)
{
    printf("print(\"### // Case 1_1: A = 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        bi_SQU(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_2(C, &A);
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
        bi_SQU(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_2(C, &A);
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
        bi_SQU(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_2(C, &A);
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
        bi_SQU(C, A);
        sage_show_squ(C, A, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete_2(C, &A);
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
// void test_bi_word_lshift2(int TEST)
// {
//     bigint *A = NULL;
//     bigint *C = NULL;

//     for (int j = 0; j < TEST; j++)
//     {
//         int x = rand() % 0xf + 1;
//         int num1 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);

//         printf("A = ");
//         bi_print(A);

//         bi_word_lshift2(&C, A, x);
//         printf("C = ");
//         bi_print(C);

//         printf("print(A << (%d * %d) == C) #%d\n", x, w, j);
//     }

//     bi_delete(&A);
//     bi_delete(&C);
// }

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

void test_bi_rshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xff;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_rshift(&A, x);
        printf("C = ");
        bi_print(A);
        printf("print(\"{} : {}\".format(%d, A >> %d == C)) #%d\n", j, x, j);
    }

    bi_delete(&A);
}