#include "bi.h"
#include "bi_op.h"

void bi_l2r(bigint **C, bigint *A, int n)
{
    bigint *T = NULL;

    bi_set_one(&T);

    for (int j = bitlen(n) - 1; j >= 0; j--)
    {
        bi_SQU_assign(&T);

        if (get_j_bit(n, j) == 1)
            bi_MUL_assign(&T, A);
    }
    bi_assign(C, T);
    bi_delete(&T);
}

void bi_r2l(bigint **C, bigint *A, int n)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);
    bi_assign(&T1, A);

    for (int j = 0; j < bitlen(n); j++)
    {
        if (get_j_bit(n, j) == 1)
            bi_MUL_assign(&T0, T1);

        bi_SQU_assign(&T1);
    }
    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}

void bi_mns(bigint **C, bigint *A, int n)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);
    bi_assign(&T1, A);

    for (int j = bitlen(n) - 1; j >= 0; j--)
    {

        if (get_j_bit(n, j) == 1)
        {
            bi_MUL_assign(&T0, T1);
            bi_SQU_assign(&T1);
        }
        else
        {
            bi_MUL_assign(&T1, T0);
            bi_SQU_assign(&T0);
        }
    }
    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}