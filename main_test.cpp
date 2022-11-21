#include <stdio.h>
#include <iostream>

#include "includes/bi_util.h"
#include "includes/bi.h"
#include "includes/bi_op.h"
// #include "includes/bi_rand.h"

int main()
{
    const char *str1 = "143232234234234232434242342424";
    const char *str2 = "4123423423432424234134343143124324234";

    bigint *A, *B, *C;

    bi_new(&A, 5);
    bi_new(&B, 5);
    bi_new(&C, 5);

    // bi_gen_rand(&A, NON_NEGATIVE, 3);
    // bi_gen_rand(&B, NON_NEGATIVE, 3);

    hexstrToBigint(A->a, str1, strlen(str1));
    hexstrToBigint(B->a, str2, strlen(str2));

    bi_print("A", A);
    bi_print("B", B);

    // bi_add(&C, A, B);
    // bi_print("C", C);

    return 0;
}