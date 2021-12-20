#include "bi_local.h"
#include "bi_operation.h"
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c)
{
    int cc = 0;
    *C = A + B;

    if (*C < A)
        cc = 1;

    *C = *C + *c;

    if (*C < *c)
        cc += 1;

    *c = cc;
}

void bi_ADDC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *T = NULL;
    bi_new(&T, A->wordlen + 1);

    bi_resize(&B, A->wordlen);
    int c = 0;

    for (int j = 0; j < A->wordlen; j++)
        bi_ADD_ABc(&T->a[j], A->a[j], B->a[j], &c);

    T->a[A->wordlen] = c;

    bi_assign(C, T);
    bi_refine(*C);
    bi_delete(&T);
}

void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    // Case: A = 0, C = B
    if (bi_is_zero(A) == true)
    {
        bi_assign(C, B);
        return;
    }
    // Case: B = 0, C = A
    if (bi_is_zero(B) == true)
    {
        bi_assign(C, A);
        return;
    }
    // Case: A > 0 and B < 0, C = A - |B|
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        bi_abs(B);
        bi_SUB(C, A, B);
        bi_flip_sign(B);
        return;
    }

    // Case: A < 0 and B > 0, C = B - |A|
    if (A->sign == NEGATIVE and B->sign == NON_NEGATIVE)
    {
        bi_abs(A);
        bi_SUB(C, B, A);
        bi_flip_sign(A);
        return;
    }

    // Case: wordlen(A) ≥ wordlen(B)
    if (A->wordlen >= B->wordlen)
    {
        bi_ADDC(C, A, B);
        (*C)->sign = A->sign;
        return;
    }
    // Case: wordlen(A) < wordlen(B)
    else
    {
        bi_ADDC(C, B, A);
        (*C)->sign = A->sign;
        return;
    }
}