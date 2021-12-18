#include <stdio.h>
#include "bi_local.h"

int main()
{
    bigint *A = NULL;
    // bi_new(&A, 4);

    // A->a[0] = 0x0123456789abcdef;
    // A->a[1] = 0x5678;
    // A->a[2] = 0x9abc;
    // A->a[3] = 0xdef1;

    bi_gen_rand(&A, NON_NEGATIVE, 5);
    bi_print(A);

    printf("%d\n", bi_is_zero(A));

    bi_delete(&A);
    return 0;
}