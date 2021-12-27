#include "bi_local.h"
#include "bi_op.h"

void bi_word_lshift(OUT bigint **A, IN int x)
{
    bi_resize(A, (*A)->wordlen + x);

    // 기존 값 왼쪽으로 워드 시프트
    for (int j = (*A)->wordlen - 1; j >= x; j--)
        (*A)->a[j] = (*A)->a[j - x];

    // 남은 배열 0으로 초기화
    for (int j = x - 1; j >= 0; j--)
        (*A)->a[j] = 0;
}

void bi_word_lshift2(OUT bigint **C, IN bigint *A, IN int r)
{
    bi_new(C, A->wordlen + r);

    // 기존 값 왼쪽으로 워드 시프트
    for (int j = 0; j < A->wordlen; j++)
        (*C)->a[j + r] = A->a[j];
}

void bi_lshift(bigint **A, int x)
{

    int n = (*A)->wordlen;
    int q = x / w;
    int r = x % w;

    if (x % w == 0)
    {
        bi_word_lshift(A, q);
        return;
    }

    bigint *T = NULL;
    bi_new(&T, n + q + 1);

    T->a[q] = (*A)->a[0] << r;

    for (int j = 1; j < n; j++)
        T->a[j + q] = ((*A)->a[j] << r) | ((*A)->a[j - 1] >> (w - r));

    T->a[n + q] = (*A)->a[n - 1] >> (w - r);

    bi_refine(T);
    bi_assign(A, T);
    bi_delete(&T);
}

void bi_word_rshift(OUT bigint **A, IN int x)
{
    if ((*A)->wordlen < x)
    {
        bi_set_zero(A);
        return;
    }

    for (int j = 0; j < (*A)->wordlen - x; j++)
        (*A)->a[j] = (*A)->a[j + x];

    for (int j = (*A)->wordlen - x; j < (*A)->wordlen; j++)
        (*A)->a[j] = 0;

    if ((*A)->sign == NEGATIVE)
        (*A)->a[0]++;

    bi_refine(*A);
}

void bi_rshift(bigint **A, int x)
{
    return;
}

void bi_word_reduction(OUT bigint **A, IN int r)
{
    for (int j = r; j < (*A)->wordlen; j++)
        (*A)->a[j] = 0;

    bi_refine(*A);
    printf("너?\n");
    bi_print(*A);
    if ((*A)->sign == NEGATIVE)
    {
        bigint *T = NULL;
        bi_new(&T, (*A)->wordlen + 1);

        T->a[(*A)->wordlen] = 1;
        // Case 4: A < 0 and B > 0, C = B - |A|

        bi_abs(*A);
        bi_SUB(A, T, *A);
        bi_flip_sign(*A);

        // bi_ADD(A, *A, T);
        // printf("너냐?\n");
        bi_print(*A);
    }
}