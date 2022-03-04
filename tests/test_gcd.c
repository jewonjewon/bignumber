#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/bi_test.h"

void sage_show_gcd(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);

    printf("if (C != gcd(A, B)):\n");
    printf("    print(\"Error: gcd(A, B), %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"gcd(A, B) = {}\".format(hex(gcd(A, B))))\n");
}

void test_gcd(int TEST, void (*func)(bigint **, bigint *, bigint *))
{
    printf("print(\"### GCD TEST ###\\n\")\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        bi_gen_rand(&A, NON_NEGATIVE, rand_num(0xf));
        bi_gen_rand(&B, NON_NEGATIVE, rand_num(0xf));

        func(&C, A, B);
        sage_show_gcd(&C, A, B, j);
    }

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
