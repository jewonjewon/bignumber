#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/bi_test.h"

void sage_show_exp(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("n", B);
    bi_print("C", *C);
    printf("if (C != A ** n):\n");
    printf("    print(\"exp Error: A^n , %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"n = {}\".format(hex(n)))\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"A^n = {}\".format(hex(A**n)))\n");
}

void test_exp(int TEST, void (*func)(bigint **, bigint *, bigint *))
{
    printf("print(\"### exponentiation ###\\n\")\n");

    bigint *A = NULL;
    bigint *N = NULL;
    bigint *C = NULL;

    bi_set_one(&N);

    for (int j = 0; j < TEST; j++)
    {
        int n = rand() % 0xf;
        N->a[0] = n;

        bi_gen_rand(&A, NON_NEGATIVE, rand_num(0xf));
        func(&C, A, N);
        sage_show_exp(&C, A, N, j);
    }

    bi_delete(&A);
    bi_delete(&C);
    bi_delete(&N);
}
