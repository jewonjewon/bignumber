#include "bi_local.h"
#include "bi_op.h"

void bi_SQU_A(OUT bigint **C, word A)
{
    bi_new(C, 2);

    word A1 = A >> (w / 2);
    word A0 = (A << (w / 2)) >> (w / 2);

    word C1 = A1 * A1;
    word C0 = A0 * A0;

    (*C)->a[1] = C1;
    (*C)->a[0] = C0;

    bigint *T = NULL;
    bi_new(&T, 2);

    bi_MUL_AB(&T, A0, A1);

    bi_lshift(&T, w / 2 + 1);

    bi_ADDC(C, *C, T);
}

void bi_SQUC(OUT bigint **C, IN bigint *A)
{
    // bi_new(C, 2 * A->wordlen);

    bigint *C1 = NULL;
    bigint *C2 = NULL;

    bi_new(&C1, 1);
    bi_new(&C2, 1);

    bigint *T1 = NULL;
    bigint *T2 = NULL;

    for (int j = 0; j < A->wordlen; j++)
    {
        bi_SQU_A(&T1, A->a[j]);
        bi_word_lshift(&T1, 2 * j);
        bi_ADDC(&C1, T1, C1);

        for (int i = j + 1; i < A->wordlen; i++)
        {
            bi_MUL_AB(&T2, A->a[j], A->a[i]);
            bi_word_lshift(&T2, i + j);
            bi_ADD(&C2, C2, T2);
        }
    }
    bi_lshift(&C2, 1);
    bi_ADD(C, C1, C2);

    bi_delete(&C1);
    bi_delete(&C2);
    bi_delete(&T1);
    bi_delete(&T2);
}

void bi_SQU(OUT bigint **C, IN bigint *A)
{
    // Case 1: A = 0 or A = 1 or A = -1
    if (bi_is_zero(A) == true or bi_is_one(A) == true or bi_is_minus_one(A) == true)
    {
        bi_assign(C, A);
        bi_abs(*C);
        return;
    }

    // Case 2: Otherwise
    bi_SQUC(C, A);
}