#include "../includes/bi.h"
#include "../includes/bi_op.h"

void sage_show_xgcd(bigint **C, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("C", *C);

    printf("if (C != A.xgcd(B)[1]):\n");
    printf("    print(\"Error: A.xgcd(B)[1], %d-th\")\n", j);
    printf("    print(\"A = {}\".format(hex(A)))\n");
    printf("    print(\"B = {}\".format(hex(B)))\n");
    printf("    print(\"C = {}\".format(hex(C)))\n");
    printf("    print(\"A.xgcd(B)[1] = {}\".format(hex(A.xgcd(B)[1])))\n");
    printf("    print(hex(C-B))\n");
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
