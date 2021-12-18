#include <stdio.h>
#include "bi_local.h"

int main()
{
    bigint *A = NULL;

    bi_new(&A, 4);

    A->a[0] = 0x1234;
    A->a[1] = 0x5678;
    A->a[2] = 0x9abc;
    A->a[3] = 0xdef1;

    for (int j = 0; j < A->wordlen; j++)
        printf("%llx\n", A->a[j]);

    test();
    bi_delete(&A);
    return 0;
}