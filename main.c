#include <stdio.h>
#include "bi_local.h"

int main()
{
    bigint *A = NULL;
    bi_new(&A, 4);

    A->a[0] = 0x0123456789abcdef;
    A->a[1] = 0x5678;
    A->a[2] = 0x9abc;
    A->a[3] = 0xdef1;

    for (int j = A->wordlen; j < 0; j++)
    {
        check;
        printf("%llx\n", A->a[j]);
    }
    bi_print(A);
    test();
    bi_delete(&A);
    return 0;
}