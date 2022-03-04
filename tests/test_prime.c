#include "../includes/bi.h"
#include "../includes/bi_op.h"

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
