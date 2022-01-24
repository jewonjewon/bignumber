#include "bi.h"
#include "bi_op.h"

void bi_gcd_bin(bigint **C, bigint *A, bigint *B)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bigint *T2 = NULL;

    bi_assign(&T0, A);
    bi_assign(&T1, B);
    bi_set_one(&T2);

    while (((T0->a[0] & 0x1) == 0) and ((T1->a[0] & 0x1) == 0))
    {
        bi_rshift(&T0, 1);
        bi_rshift(&T1, 1);
        bi_lshift(&T2, 1);
    }

    while (bi_is_zero(T1) != 0)
    {
        while ((T0->a[0] & 0x1) == 0)
            bi_rshift(&T0, 1);

        while ((T1->a[0] & 0x1) == 0)
            bi_rshift(&T1, 1);

        if ((bi_cmp(T1, T0) == 1) or (bi_cmp(T1, T0) == 0))
            bi_SUB(&T1, T1, T0);
        else
            bi_SUB(&T0, T0, T1);
    }

    // bi_MUL(C, T0, T2);
    bi_assign(C, T2);

    printf("T0 = ");
    bi_print(T0);
    printf("T1 = ");
    bi_print(T1);
    printf("T2 = ");
    bi_print(T2);

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&T2);
}