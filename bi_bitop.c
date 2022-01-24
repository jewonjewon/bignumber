#include "bi.h"
#include "bi_op.h"

word pow2(int a)
{
    word x = 1;
    return (x << a);
}

int bitlen(word a)
{
    word cnt = 0;

    do
    {
        a = a >> 1;
        cnt++;
    } while (a > 0);

    return cnt;
}
void bi_word_lshift(OUT bigint **A, IN int x)
{
    if (bi_is_zero(*A) == true)
        bi_set_zero(A);

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

// void bi_rshift(bigint **A, int x)
// {
//     int n = (*A)->wordlen;
//     int q = x / w;
//     int r = x % w;

//     if (x % w == 0)
//     {
//         bi_word_lshift(A, q);
//         return;
//     }

//     bigint *T = NULL;
//     bi_new(&T, n + q + 1);

//     T->a[q] = (*A)->a[0] << r;

//     for (int j = 1; j < n; j++)
//         T->a[j + q] = ((*A)->a[j] << r) | ((*A)->a[j - 1] >> (w - r));

//     T->a[n + q] = (*A)->a[n - 1] >> (w - r);

//     bi_refine(T);
//     bi_assign(A, T);
//     bi_delete(&T);
// }

void bi_rshift(bigint **A, int x)
{
    int n = (*A)->wordlen;
    int q = x / w;
    int r = x % w;

    if (x >= (w * n))
    {
        bi_set_zero(A);
        return;
    }

    if (x % w == 0)
    {
        bi_word_rshift(A, q);
        return;
    }

    bigint *T = NULL;
    bi_new(&T, n - q);

    for (int j = q; j < n; j++)
        T->a[j - q] = ((*A)->a[j + 1] << (w - r)) | ((*A)->a[j] >> r);

    T->a[T->wordlen - 1] = (*A)->a[n - 1] >> r;

    bi_refine(T);
    bi_assign(A, T);
    bi_delete(&T);
}

void bi_word_reduction(OUT bigint **A, IN int r)
{
    for (int j = r; j < (*A)->wordlen; j++)
        (*A)->a[j] = 0;

    bi_refine(*A);
}

// void bi_word_reduction(OUT bigint **A, IN int r)
// {
//     if (r > (*A)->wordlen)
//     {
//         goto minus;
//         return;
//     }

//     for (int j = r; j < (*A)->wordlen; j++)
//         (*A)->a[j] = 0;

//     bi_refine(*A);

// minus:
//     if ((*A)->sign == NEGATIVE)
//     {
//         bigint *T = NULL;
//         bi_new(&T, (*A)->wordlen + 1);

//         T->a[(*A)->wordlen] = 1;
//         // Case 4: A < 0 and B > 0, C = B - |A|

//         // printf("1. A = ");
//         // bi_print(*A);

//         // printf("1. T = ");
//         // bi_print(T);
//         // printf("\n");

//         bi_abs(*A);
//         bi_SUB(A, *A, T);
//         bi_flip_sign(*A);
//         // bi_ADD(A, T, *A);

//         // printf("2. A = ");
//         // bi_print(*A);

//         // printf("2. T = ");
//         // bi_print(T);

//         // printf("mod A = ");
//         // bi_print(*A);
//         // bi_delete(&T);
//     }
// }