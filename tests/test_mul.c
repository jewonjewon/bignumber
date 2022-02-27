#include "../includes/bi.h"
#include "../includes/bi_op.h"

void sage_show_add(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);

    printf("if (C != A + B):\n");
    printf("    print(\"Error: A + B, %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"A + B = {}\".format(hex(A+B)))\n");
}

void sage_show_sub(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);
    printf("if (C != A - B):\n");
    printf("    print(\"{} : {}\".format(%d, A - B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_mul(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);
    printf("if (C != A * B):\n");
    printf("    print(\"{} : {}\".format(%d, A * B == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_squ(bigint **C, bigint *A, int j)
{
    bi_print("A", A);
    bi_print("C", *C);
    printf("if (C != A ** 2):\n");
    printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_div(bigint **Q, bigint **R, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("Q", *Q);
    bi_print("R", *R);

    printf("if ((Q != A // B) and (Q != A %% B)):\n");
    printf("    print(\"{} : {}\".format(%d, A // B == Q)) #%d\n", j, j);
    printf("    print(\"{} : {}\".format(%d, A %% B == R)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_exp(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("C", *C);
    printf("if (C != A ** 2):\n");
    printf("    print(\"{} : {}\".format(%d, A ** 2 == C)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

void sage_show_mod_exp(bigint **C, bigint *A, bigint *n, bigint *M, int j)
{
    bi_print("A", A);
    bi_print("n", n);
    bi_print("M", M);
    bi_print("C", *C);

    printf("if (C != power_mod(A, n, M)):\n");
    printf("    print(\"Error: (A ^ n) mod M, %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"n = {}\".format(hex(n)))\n");
    printf("    print(\"M = {}\".format(hex(M)))\n");
    printf("    print()\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"(A ^ n) mod M = {}\".format(hex(power_mod(A, n, M))))\n");
}

void sage_show_gcd(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);

    printf("if (C != gcd(A, B)):\n");
    printf("    print(\"Error: gcd(A, B), %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    newline;
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"gcd(A, B) = {}\".format(hex(gcd(A, B))))\n");
}

void sage_show_xgcd(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);

    printf("if (C != A.xgcd(B)[1]):\n");
    printf("    print(\"Error: A.xgcd(B)[1], %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    newline;
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"A.xgcd(B)[1] = {}\".format(hex(A.xgcd(B)[1])))\n");
}

void sage_show_is_prime(bigint *n, int k, int v, int j)
{
    bi_print("n", n);

    printf("if (n.is_prime() != %d):\n", v);
    printf("    print(\"ERROR\")\n");
    printf("    if (n.is_prime() != True):\n");
    printf("        print (\"n is composite number!\")\n");
    printf("    else:\n");
    printf("        print (\"n is prime!\")\n");
}

void sage_show_prime_gen(bigint *n, int j)
{
    bi_print("n", n);

    printf("if (n.is_prime() == False):\n");
    printf("    print(\"n is not prime, %d-th\")\n", j);
    printf("    print(\"n = {}\".format(hex(n)))\n");
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

// Case 1: A = 0, C = B
void sub_test_ADD1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    // printf("print(\"### Case 1: A = 0, C = B ###\\n\")\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_new(&A, 1);
        bi_gen_rand(&B, sign2, num2);

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 2: B = 0, C = A
void sub_test_ADD2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    // printf("print(\"### Case 2: B = 0, C = A ###\\n\")\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_new(&B, 1);

        bi_add(C, A, B);

        sage_show_add(C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 3: A > 0 and B < 0, C = A - |B|
void sub_test_ADD3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    // printf("print(\"### Case 3: A > 0 and B < 0, C = A - |B| ###\\n\")\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = NON_NEGATIVE;
        int sign2 = NEGATIVE;
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_add(C, A, B);

        sage_show_add(C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 4: A < 0 and B > 0, C = B - |A|
void sub_test_ADD4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    // printf("print(\"### Case 4: A < 0 and B > 0, C = B - |A| ###\\n\")\n");

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        do
        {
            bi_gen_rand(&A, NEGATIVE, num1);
            bi_gen_rand(&B, NON_NEGATIVE, num2);
        } while (bi_is_zero(B) == true);

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}
// Case 5: wordlen(A) ≥ wordlen(B)
void sub_test_ADD5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    // printf("print(\"### Case 5: wordlen(A) ≥ wordlen(B) ###\\n\")\n");

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

        bi_add(C, A, B);
        //
        // B->sign = NEGATIVE;
        sage_show_add(C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete_3(C, &A, &B);
}

// Case 6: wordlen(A) < wordlen(B)
void sub_test_ADD6(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    // printf("print(\"### Case 6: wordlen(A) < wordlen(B) ###\\n\")\n");

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

        bi_add(C, A, B);

        sage_show_add(C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_sub(C, A, B);
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

        bi_print("A", A);

        bi_print("B", B);

        bi_MUL_AB(&C, A->a[0], B->a[0]);
        bi_print("C", C);

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

        bi_mul(C, A, B);
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

        bi_mul(C, A, B);
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

        bi_mul(C, A, B);
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

        bi_mul(C, A, B);
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

        bi_mul(C, A, B);
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

        bi_mul(C, A, B);
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

        bi_mul(C, A, B);
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
        bi_squ(C, A);
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
        bi_squ(C, A);
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
        bi_squ(C, A);
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

        bi_print("A", A);

        bi_word_lshift(&A, x);
        bi_print("A", A);

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

        bi_print("A", A);
        bi_lshift(&A, x);
        bi_print("A", A);
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

        bi_print("A", A);

        bi_rshift(&A, x);
        bi_print("A", A);
        printf("print(\"{} : {}\".format(%d, A >> %d == C)) #%d\n", j, x, j);
    }

    bi_delete(&A);
}

void test_bi_word_rshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
        int num1 = rand() % 0x0f + 1;
        // int x = 2;
        bi_gen_rand(&A, NON_NEGATIVE, num1);

        bi_print("A", A);

        bi_word_rshift(&A, x);

        bi_print("A", A);

        printf("print(A >> (%d * %d) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

void test_MULC_karastuba(int TEST)
{
    printf("\n\n\n\n\n### 카라츄바 테스트\n\n");
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    // bi_MULC_karastuba TEST
    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, 20);
        bi_gen_rand(&B, NON_NEGATIVE, 20);
        bi_kmul_core(&C, A, B);
        bi_print("A", A);
        bi_print("B", B);
        bi_print("C", C);

        printf("print(A * B == C) #%d\n", j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_bi_word_reduction(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NEGATIVE, num1);

        bi_print("A", A);

        bi_word_reduction(&A, x);
        bi_print("A", A);
        printf("print(A %% (2 ** (%d * %d)) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

// void test_bi_long_div_2word(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;

//     for (int j = 0; j < TEST; j++)
//     {
//         bi_gen_rand(&A, NON_NEGATIVE, 2);
//         bi_gen_rand(&B, NON_NEGATIVE, 1);

//         if (A->a[1] < B->a[0])
//             printf("A1 ≥ B\n");

//         Q = bi_long_div_2word(A, B->a[0]);

//     //         bi_print("A", A);
//     //         bi_print("B", B);
//         printf("Q = %#llx\n", Q);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(hex(A//B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
// }

// void test_DIVCC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {
//         // int num1 = rand() % 0x0f + 2;
//         // int num2 = rand() % 0x0f + 1;
//         // while (1)
//         // {
//         //     bi_gen_rand(&A, NON_NEGATIVE, num1);
//         //     bi_gen_rand(&B, NON_NEGATIVE, num2);
//         //     if (bi_cmp(B, A) == -1 and bi_cmp(B, A) == 0)
//         //     {
//         //         bigint *T = NULL;
//         //         bi_new(&T, 1);
//         //         bi_assign(&T, B);
//         //         bi_word_lshift(&T, 1);
//         //         if (bi_cmp(A, T) == -1)
//         //             if (B->a[B->wordlen - 1] >= pow2(w - 1))
//         //             {
//         //                 printf("DIVCC 입력 조건 0 < B ≤ A < BW, B_{m-1} ≥ 2^{w-1} 성립!\n");
//         //                 bi_delete(&T);
//         //                 break;
//         //             }
//         //         bi_delete(&T);
//         //     }
//         //     check;
//         // }

//         int num1 = rand() % 0x0f + 1;
//         // int num2 = rand() % 0x0f + 1;
//         // while (num1 < num2)
//         // {

//         num1 = rand() % 0x0f + 1;
//         // num2 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num1 - 1);
//         // }

//         if (bi_cmp(B, A) == -1 and bi_cmp(B, A) == 0)
//         {
//             bigint *T = NULL;
//             bi_new(&T, 1);
//             bi_assign(&T, B);
//             bi_word_lshift(&T, 1);
//             if (bi_cmp(A, T) == -1)
//                 if (B->a[B->wordlen - 1] >= pow2(w - 1))
//                 {
//                     printf("DIVCC 입력 조건 0 < B ≤ A < BW, B_{m-1} ≥ 2^{w-1} 성립!\n");
//                     bi_delete(&T);
//                     break;
//                 }
//             bi_delete(&T);
//         }

//         bi_DIVCC(&Q, &R, A, B);

//     //         bi_print("A", A);
//
//         printf("Q = %#llx\n", "x", Q);
//
//         bi_print("R", R);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(A %% B == R) #%d\n", j);

//         printf("print(hex(A//B))\n");
//         printf("print(hex(A%%B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&R);
// }

// void test_DIVC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {

//         int num1 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num1 - 1);

//         // bi_gen_rand(&A, NON_NEGATIVE, 5);
//         // bi_gen_rand(&B, NON_NEGATIVE, 3);

//         ///
//         bigint *T = NULL;

//         bi_assign(&T, B);
//         bi_word_lshift(&T, 1);

//         if (bi_cmp(A, T) == -1)
//         {
//             if (B->a[B->wordlen - 1] >= pow2(w - 1))
//             {
//                 printf("DIVC 입력 조건 0 ≤ A < BW 성립!\n");
//             }
//         }
//         bi_delete(&T);
//         ///

//         bi_DIVC(&Q, &R, A, B);

//     //         bi_print("A", A);
//
//         printf("Q = %#llx\n", "x", Q);
//
//         bi_print("R", R);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(A %% B == R) #%d\n", j);

//         printf("print(hex(A//B))\n");
//         printf("print(hex(A%%B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&R);
// }

void test_DIV(int TEST)
{
    printf("print(\"### DIV TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
            {
                bi_gen_rand(&A, NON_NEGATIVE, num1);
                bi_gen_rand(&B, NON_NEGATIVE, num2);
                if (bi_is_zero(B) == true)
                    continue;
                break;
            }
        }

        bi_div(&Q, &R, A, B);
        sage_show_div(&Q, &R, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);
}

void test_long_div_bin(int TEST)
{
    printf("print(\"### BINARY LONG DIVISION TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
            {
                bi_gen_rand(&A, NON_NEGATIVE, num1);
                bi_gen_rand(&B, NON_NEGATIVE, num2);
                if (bi_is_zero(B) == true)
                    continue;
                break;
            }
        }

        bi_long_div_bin(&Q, &R, A, B);
        sage_show_div(&Q, &R, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);
}

void test_exp(int TEST, void (*func)(bigint **, bigint *, bigint *))
{
    printf("print(\"### exponentiation ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *N = NULL;
    bigint *C = NULL;

    bi_new(&N, 1);

    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;

        int n = rand() % 0xf;
        N->a[0] = n;

        bi_gen_rand(&A, NON_NEGATIVE, num1);

        bi_print("N", N);

        bi_print("A", A);

        func(&C, A, N);
        bi_l2r(&C, A, N);

        bi_print("C", C);
        printf("print((A ** n) == C)\n");
        // printf("print(hex(A**n))\n");
    }

    bi_delete(&A);
    bi_delete(&C);
    bi_delete(&N);
}

void test_mod_exp(int TEST, void (*func)(bigint **, bigint *, bigint *, bigint *))
{
    printf("print(\"### mod_l2r ###\\n\")\n");

    bigint *A = NULL; /* 밑수 */
    bigint *n = NULL; /* 지수 */
    bigint *M = NULL; /* Modulra value */
    bigint *C = NULL; /* 결과값 */

    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&M, NON_NEGATIVE, num2);
        bi_gen_rand(&n, NON_NEGATIVE, 1);

        func(&C, A, n, M);
        sage_show_mod_exp(&C, A, n, M, j);
    }

    bi_delete(&A);
    bi_delete(&n);
    bi_delete(&M);
    bi_delete(&C);
}

void test_gcd(int TEST, void (*func)(bigint **, bigint *, bigint *))
{
    printf("print(\"### GCD TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;
        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        func(&C, A, B);
        sage_show_gcd(&C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_xgcd(int TEST, void (*func)(bigint **, bigint *, bigint *))
{
    printf("print(\"### EEA TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        func(&C, A, B);
        sage_show_xgcd(&C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_mont_red(int TEST)
{
    printf("print(\"### Montgomery Reduction TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *x = NULL;
    bigint *R = NULL; /* 워드 블록 형태 */
    bigint *N = NULL;
    bigint *C = NULL;  /* OUTPUT */
    bigint *nn = NULL; /* nn = -(inv_N) */

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;
        int num3 = rand() % 0x0f + 1;
        int t = 0;
        bi_gen_rand(&x, NON_NEGATIVE, num1);
        bi_gen_rand(&N, NON_NEGATIVE, num2);

        do
        {
            num3 = rand() % 0x0f + 1;
            t = num3 % 0xf + 1;

        } while (N->wordlen > t);

        bi_new(&R, 2);
        R->a[1] = 1;

        bi_word_lshift(&R, t);

        bi_lshift(&N, 1);

        bi_addi(&N, 1);

        bi_eea_itr(&nn, N, R);

        bi_mont_red(&C, x, R, N, nn);

        bi_print("x", x);
        bi_print("R", R);
        bi_print("N", N);
        bi_print("C", C);
        // printf("if (C != xgcd(A,B)[1]):\n");
        // printf("    print(\"{} : {}\".format(%d, xgcd(A,B)[1] == C)) #%d\n", j, j);
        // printf("    print(hex(xgcd(A,B)[1]))\n");
        // printf("    cnt = cnt + 1\n");
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&x);
    bi_delete(&R);
    bi_delete(&N);
    bi_delete(&C);
    bi_delete(&nn);
}

void test_is_prime(int TEST, int (*func)(bigint *, int k))
{
    printf("print(\"### is_prime? TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *n = NULL;
    int k = 40;

    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&n, NON_NEGATIVE, num1);

        int v = func(n, k);
        sage_show_is_prime(n, k, v, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");

    bi_delete(&n);
}

void test_prime_gen(int TEST, void (*func)(bigint **, int))
{
    printf("print(\"### prime generation TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *n = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1; /* num1 is random bit length */

        func(&n, 512); /* Choose random num1-bit prime n */
        sage_show_prime_gen(n, j);
    }

    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&n);
}

// void test_textbook_RSA(int TEST, void (*keygen)(RSA_key *, RSA_key *, int),
//                        void (*enc)(bigint **, bigint *, RSA_key *),
//                        void (*dec)(bigint **, bigint *, RSA_key *))
// {
//     RSA_key pk;
//     RSA_key sk;

//     bigint *m = NULL;
//     bigint *c = NULL;
//     bigint *recoverd_msg = NULL;

//     // bi_new(&m, 1);
//     // m->a[0] = 0x200;

//     bi_gen_rand(&m, NON_NEGATIVE, 5);

//     RSA_keygen(&pk, &sk, n);

//     printf("#   RSA-1024 Key list\n");
//     printf("p = ");
//     bi_print(sk.p);
//     newline;
//     printf("q = ");
//     bi_print(sk.q);
//     newline;
//     printf("N = ");
//     bi_print(pk.N);
//     newline;

//     printf("e = ");
//     bi_print(pk.e);
//     newline;
//     printf("d = ");
//     bi_print(sk.d);

//     newline;

//     RSA_enc(&c, m, &pk);
//     printf("Cipher text(RSA-1024)\n");
//     bi_print(c);

//     newline;

//     RSA_dec(&recoverd_msg, c, &sk);
//     printf("Recovered message(RSA-1024)\n");
//     bi_print(recoverd_msg);

//     newline;

//     if (bi_cmp(m, recoverd_msg) == 0)
//         printf("Success!\n");
//     else
//         printf("Fali..\n");

//     bi_delete(&m);
//     bi_delete(&c);
//     bi_delete(&recoverd_msg);
// }
