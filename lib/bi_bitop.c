#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/basic.h"

/* 임의의 정수 A의 비트 길이를 측정하는 함수 */
int bi_bit_cnt(bigint *A)
{
    if (A->wordlen < 1)
        return -1; /* error */

    int t = bitlen(A->a[A->wordlen - 1]);    /* t =  A의 최상위워드의 비트 길이 */
    int bitlen_A = w * (A->wordlen - 1) + t; /* bitlen(A) = (w * wordlen(A)) + t */
    return bitlen_A;                         /* A의 비트길이 반환 */
}

/* 임의의 정수 A의 j번 째 비트를 반환하는 함수 */
int bi_get_j_bit(bigint *A, int n)
{
    int q = n / w;
    int r = n % w;

    int j_th_bit = get_j_bit(A->a[q], r); /* q번째 워드 블록의 r번 째 수가 찾고자 하는 비트 */

    return j_th_bit;
}

/* C = A \oplus B */
void bi_xor(bigint **C, bigint *A, bigint *B)
{
    if (A->wordlen <= B->wordlen) /* wordlen(A) ≤ wordlen(B) */
        bi_resize(&A, B->wordlen);
    else
        bi_resize(&B, A->wordlen);

    bi_new(C, A->wordlen);

    for (int j = 0; j < A->wordlen; j++)
        (*C)->a[j] = A->a[j] ^ B->a[j];

    bi_refine(*C);

    bi_refine(A);
    bi_refine(B);
}

void bi_xor_asg(IN OUT bigint **C, IN bigint *A)
{
    bigint *T = NULL;
    bi_assign(&T, *C);

    if (A->wordlen < T->wordlen)
        bi_resize(&A, T->wordlen);
    else
        bi_resize(&T, A->wordlen);

    bi_new(C, A->wordlen);

    for (int j = 0; j < A->wordlen; j++)
        (*C)->a[j] = A->a[j] ^ T->a[j];

    bi_refine(*C);
    bi_refine(A);

    bi_delete(&T);
}

void bi_or_asg(IN OUT bigint **C, IN bigint *A)
{
    bigint *T = NULL;
    bi_assign(&T, *C);

    if (A->wordlen < T->wordlen)
        bi_resize(&A, T->wordlen);
    else
        bi_resize(&T, A->wordlen);

    bi_new(C, A->wordlen);

    for (int j = 0; j < A->wordlen; j++)
    {
        // check;
        (*C)->a[j] = A->a[j] | T->a[j];
    }

    bi_refine(*C);
    bi_refine(A);

    bi_delete(&T);
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

    T->sign = (*A)->sign;

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
/* A >>= x */
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

    T->sign = (*A)->sign;

    bi_refine(T);
    bi_assign(A, T);
    bi_delete(&T);
}

void bi_word_reduction(OUT bigint **A, IN int r)
{
    for (int j = r; j < (*A)->wordlen; j++)
        (*A)->a[j] = 0;

    bi_refine(*A);

    /* if sign(A) = NEGATIVE */
    if ((*A)->sign == NEGATIVE)
    {
        bigint *T = NULL;

        bi_new(&T, r + 1);
        T->a[T->wordlen - 1] = 0x1;

        bi_add_asg(A, T);
        bi_delete(&T);
    }
}

void bi_red(OUT bigint **A, IN int x)
{
    int q = x / w;
    int r = x % w;

    bi_word_reduction(A, q + 1);

    (*A)->a[(*A)->wordlen - 1] &= (pow2(r) - 1);
}