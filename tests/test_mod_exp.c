#include "../includes/bi.h"
#include "../includes/bi_op.h"

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
