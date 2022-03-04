#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/bi_test.h"

void sage_show_add(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);

    printf("if (C != A + B):\n");
    printf("    print(\"add Error: A + B, %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"A + B = {}\".format(hex(A+B)))\n");
}

// Case 1: A = 0, C = B
void sub_test_add1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    for (int j = 0; j < TEST; j++)
    {
        bi_set_zero(&A);
        bi_gen_rand(&B, rand_sign(), rand_num(0xf));

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 2: B = 0, C = A
void sub_test_add2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    for (int j = 0; j < TEST; j++)
    {
        bi_set_zero(&B);
        bi_gen_rand(&A, rand_sign(), rand_num(0xf));

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 3: A > 0 and B < 0, C = A - |B|
void sub_test_add3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, rand_num(0xf));
        bi_gen_rand(&B, NEGATIVE, rand_num(0xf));

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 4: A < 0 and B > 0, C = B - |A|
void sub_test_add4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    for (int j = 0; j < TEST; j++)
    {
        do
        {
            bi_gen_rand(&A, NEGATIVE, rand_num(0xf));
            bi_gen_rand(&B, NON_NEGATIVE, rand_num(0xf));
        } while (bi_is_zero(B) == true);

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}
// Case 5: wordlen(A) ≥ wordlen(B)
void sub_test_add5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    int num1 = 0;
    int num2 = 0;

    for (int j = 0; j < TEST; j++)
    {
        int s = rand_sign();

        do
        {
            bi_gen_rand(&A, s, rand_num(0xf));
            bi_gen_rand(&B, s, rand_num(0xf));
        } while (bi_cmp(A, B) == -1);

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 6: wordlen(A) < wordlen(B)
void sub_test_add6(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    for (int j = 0; j < TEST; j++)
    {
        int s = rand_sign();

        do
        {
            bi_gen_rand(&A, s, rand_num(0xf));
            bi_gen_rand(&B, s, rand_num(0xf));
        } while (bi_cmp(A, B) == 1 or bi_cmp(A, B) == 0);

        bi_add(C, A, B);
        sage_show_add(C, A, B, j);
    }

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

void test_add(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, rand_num(0xf));
        bi_gen_rand(&B, NEGATIVE, rand_num(0xf));

        bi_add(&C, A, B);
        sage_show_add(&C, A, B, j);
    }

    bi_delete(&C);
    bi_delete(&A);
    bi_delete(&B);

#if 0 /*case별 테스트*/
    int Case = 6;
    
    sub_test_add1(&C, A, B, TEST / Case);
    sub_test_add2(&C, A, B, TEST / Case);
    sub_test_add3(&C, A, B, TEST / Case);
    sub_test_add4(&C, A, B, TEST / Case);
    sub_test_add5(&C, A, B, TEST / Case);
    sub_test_add6(&C, A, B, TEST / Case);
#endif
}
