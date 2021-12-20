#include "bi_local.h"
#include "bi_operation.h"

void bi_SUB_AbB(OUT word *C, IN word A, IN word B, IN OUT int *b)
{
    int bb = 0;
    *C = A - *b;

    if (A < *b)
        bb = 1;

    if (*C < B)
        bb = bb + 1;
    *C = *C - B;

    *b = bb;
}

void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *T = NULL;
    bi_new(&T, A->wordlen);

    bi_resize(&B, A->wordlen);
    int b = 0;

    for (int j = 0; j < A->wordlen; j++)
        bi_SUB_AbB(&T->a[j], A->a[j], B->a[j], &b);

    bi_assign(C, T);
    bi_refine(*C);
    bi_delete(&T);
}

void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    // Case 1: A = B ,C = 0
    if (bi_cmp(A, B) == 0)
    {
        bi_set_zero(C);
        return;
    }
    // Case 2: A = 0, C = -B
    if (bi_is_zero(A) == true)
    {
        bi_assign(C, B);
        bi_flip_sign(*C);
        return;
    }
    // Case 3: B = 0, C = -A
    if (bi_is_zero(B) == true)
    {
        bi_assign(C, A);
        return;
    }

    // Case 4: 0 < B ≤ A,  C = A - B
    if (A->sign == NON_NEGATIVE and B->sign == NON_NEGATIVE and bi_cmp(A, B) == 1)
    {
        bi_SUBC(C, A, B);
        return;
    }

    // Case 5: 0 < A < B,  -C = B - A
    else if (A->sign == NON_NEGATIVE and B->sign == NON_NEGATIVE and bi_cmp(A, B) == -1)
    {
        bi_SUBC(C, B, A);
        (*C)->sign = NEGATIVE;
        return;
    }
    // Case 6: 0 > A ≥ B,  C = |B| - |A|
    if (A->sign == NEGATIVE and B->sign == NEGATIVE and bi_cmp(A, B) == 1)
    {
        bi_abs(A);
        bi_abs(B);
        bi_SUBC(C, B, A);
        bi_flip_sign(A);
        bi_flip_sign(B);
        return;
    }

    // Case 7: 0 > B > A,  C = |B| - |A|
    else if (A->sign == NEGATIVE and B->sign == NEGATIVE and bi_cmp(A, B) == -1)
    {
        bi_abs(A);
        bi_abs(B);
        bi_SUBC(C, A, B);
        (*C)->sign = NEGATIVE;
        bi_flip_sign(A);
        bi_flip_sign(B);
        return;
    }

    // Case 8: A > 0 and B < 0
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        bi_abs(B);
        bi_ADD(C, A, B);
        bi_flip_sign(B);
        return;
    }
    else
    {
        bi_abs(A);
        bi_ADD(C, A, B);
        (*C)->sign = NEGATIVE;
        bi_flip_sign(A);
        return;
    }
}