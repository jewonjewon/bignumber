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
