#include "bi.h"

void bi_delete(IN OUT bigint **A)
{
    if (*A == NULL)
        return;

#ifdef ZEROLIZE
    // 입력 배열 초기화
    bi_init(A);
#endif

    free((*A)->a);
    free(*A);
    *A = NULL;
}
// bigint형 배열 생성(부호= NON_NEGATIVE, 워드길이= wordlen, 배열= 0)
void bi_new(IN OUT bigint **A, IN int wordlen)
{
    // 입력받은 배열에 어떠한 값이 저장되어있는 경우 free 후 새롭게 할당
    if (*A != NULL)
        bi_delete(A);

    *A = (bigint *)malloc(sizeof(bigint));
    (*A)->sign = NON_NEGATIVE;
    (*A)->wordlen = wordlen;
    (*A)->a = (word *)calloc(wordlen, sizeof(word));
}

void bi_refine(bigint *A)
{
    if (A == NULL)
        bi_delete(&A);

    int new_wordlen = A->wordlen;

    while (new_wordlen > 1)
    {
        if (A->a[new_wordlen - 1] != 0)
            break;
        new_wordlen--;
    }

    if (A->wordlen != new_wordlen)
    {
        A->wordlen = new_wordlen;
        A->a = (word *)realloc(A->a, sizeof(word) * new_wordlen);
    }

    if ((A->wordlen == 1) and (A->a[0] == 0))
        A->sign = NON_NEGATIVE;
}

// x배열을 y에 assign
void bi_assign(IN OUT bigint **y, IN bigint *x)
{
    if (*y != NULL)
        bi_delete(y);

    bi_new(y, x->wordlen);
    (*y)->sign = x->sign;

    memmove((*y)->a, x->a, sizeof(word) * x->wordlen);
}
// 입력 배열 A의 길이를 입력 wordlen만큼 길이를 늘려주는 함수
void bi_resize(IN OUT bigint **A, IN int wordlen)
{
    (*A)->a = (word *)realloc((*A)->a, sizeof(word) * wordlen);

    for (int j = (*A)->wordlen; j < wordlen; j++)
        (*A)->a[j] = 0;

    (*A)->wordlen = wordlen;
}

void bi_init(IN OUT bigint **A)
{
    for (int j = 0; j < (*A)->wordlen; j++)
        (*A)->a[j] = 0;
}

void bi_print(bigint *A)
{
    if (A->sign == NEGATIVE)
        printf("-");

#if (w == 64)
    // Case: 워드길이가 1인 경우
    if (A->wordlen == 1)
        printf("%#llx", A->a[A->wordlen - 1]);
    // Case: 그 외
    else
    {
        printf("%#llx", A->a[A->wordlen - 1]);
        for (int j = A->wordlen - 2; j >= 0; j--)
            printf("%016llx", A->a[j]);
    }
#elif (w == 32)
    // Case: 워드길이가 1인 경우
    if (A->wordlen == 1)
        printf("%#x", A->a[A->wordlen - 1]);
    // Case: 그 외
    else
    {
        printf("%#x", A->a[A->wordlen - 1]);
        for (int j = A->wordlen - 2; j >= 0; j--)
            printf("%08x", A->a[j]);
    }
#elif (w == 8)
    // Case: 워드길이가 1인 경우
    if (A->wordlen == 1)
        printf("%#x", A->a[A->wordlen - 1]);
    // Case: 그 외
    else
    {
        printf("%#x", A->a[A->wordlen - 1]);
        for (int j = A->wordlen - 2; j >= 0; j--)
            printf("%02x", A->a[j]);
    }
#endif
    // printf(", ");
    printf("\n");
}

// 입력 배열을 1로 만드는 함수
void bi_set_one(OUT bigint **A)
{
    bi_new(A, 1);
    (*A)->sign = NON_NEGATIVE;
    (*A)->a[0] = 1;
}

// 입력 배열을 0로 만드는 함수
void bi_set_zero(OUT bigint **A)
{
    bi_new(A, 1);
    (*A)->sign = NON_NEGATIVE;
    (*A)->a[0] = 0;
}

int bi_is_zero(IN bigint *A)
{
    // Case: A < 0 or A[0] != 0
    if (A->sign == NEGATIVE or A->a[0] != 0)
        return false;

    for (int j = A->wordlen - 1; j > 0; j--)
        if (A->a[j] != 0)
            return false;
    return true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_is_one(*A) → sign(A) = NON-NEGATIVE
 * bigint형 구조체 A와 B를 입력받아 A와 B의 대소 비교를 진행하는 함수
 *  - If A < 0 or A[0] ≠ 1, then return false (A is NOT 1)
 *  - Else If {A[wordlen(A)], ..., A[1]} ≠ 0, then return false (A is NOT 1)
 *  - Else, return true (A = 1)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_is_one(*A)
int bi_is_one(IN bigint *A)
{
    // Case: A < 0 or A[0] != 1
    if (A->sign == NEGATIVE or A->a[0] != 1)
        return false;

    for (int j = A->wordlen - 1; j > 0; j--)
        if (A->a[j] != 0)
            return false;
    return true;
}

int bi_is_two(IN bigint *A)
{
    // Case: A < 0 or A[0] != 2
    if (A->sign == NEGATIVE or A->a[0] != 2)
        return false;

    for (int j = A->wordlen - 1; j > 0; j--)
        if (A->a[j] != 0)
            return false;
    return true;
}

int bi_is_even(IN bigint *A)
{
    // Case: A < 0 or A[0] != 2
    if ((A->a[0] & 0x1) == 0)
        return true;
    return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_is_minus_one(*A) → sign(A) = NON-NEGATIVE
 * bigint형 구조체 A와 B를 입력받아 A와 B의 대소 비교를 진행하는 함수
 *  - If A > 0 or A[0] ≠ 1, then return false (A is NOT -1)
 *  - Else If {A[wordlen(A)], ..., A[1]} ≠ 0, then return false (A is NOT -1)
 *  - Else, return true (A = -1)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_is_minus_one(*A)
int bi_is_minus_one(IN bigint *A)
{
    // Case: A < 0 or A[0] != 1
    if (A->sign == NON_NEGATIVE or A->a[0] != 1)
        return false;

    for (int j = A->wordlen - 1; j > 0; j--)
        if (A->a[j] != 0)
            return false;
    return true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_compare_abs(*A) → sign(A) = NON-NEGATIVE
 * bigint형 구조체 A와 B를 입력받아 A와 B의 대소 비교를 진행하는 함수
 *  - If A > B, then return 1(true)
 *  - If A < B, then return -1
 *  - If A = B, then return 0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_cmp(*A, *B)
// A>B = 1, A<B = -1, A=B = 0
int bi_compare_abs(IN bigint *A, IN bigint *B)
{
    int n = A->wordlen;
    int m = B->wordlen;

    // Case: A>B
    if (n > m)
        return 1;

    // Case: A<B
    else if (n < m)
        return -1;

    // 워드길이 동일
    for (int j = n - 1; j >= 0; j--)
        // Case:  A>B, 워드길이 동일
        if (A->a[j] > B->a[j])
            return 1;
        // Case:  A<B, 워드길이 동일
        else if (A->a[j] < B->a[j])
            return -1;
    // A=B
    return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_cmp(*A) → sign(A) = NON-NEGATIVE
 * bigint형 구조체 A와 B를 입력받아 A와 B의 대소 비교를 진행하는 함수
 *  - If A > B, then return 1(true)
 *  - If A < B, then return -1
 *  - If A = B, then return 0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_cmp(*A, *B),A > B → 1, A < B → -1, A = B → 0
int bi_cmp(IN bigint *A, IN bigint *B)
{
    // Case: A > B
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
        return 1;
    // Case: A < B
    if (A->sign == NEGATIVE and B->sign == NON_NEGATIVE)
        return -1;

    int ret = bi_compare_abs(A, B);

    if (A->sign == NON_NEGATIVE)
        return ret;
    else
        return ret * (-1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_abs(*A) → sign(A) = NON-NEGATIVE
 * bigint형 구조체 A를 입력받아 A의 부호에 절댓값을 취해주는 함수
 *  - sign(A) = NON-NEGATIVE
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_abs(a, b) → abs(a, b)
void bi_abs(IN bigint *A)
{
    A->sign = NON_NEGATIVE;
}

void bi_flip_sign(IN bigint *A)
{
    // Case 1: A → -A
    if (A->sign == NON_NEGATIVE)
        A->sign = NEGATIVE;
    // Case 2: -A → A
    else
        A->sign = NON_NEGATIVE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_min(a, b) → min(a, b)
 * 정수 a와 b를 입력받아 최대값(min(a, b))을 출력하는 함수
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_min(a, b) → min(a, b)
int bi_min(IN int a, IN int b)
{
    // Case 1: a < b, then return a.
    if (a < b)
        return a;

    // Case 2: a ≥ b, then return b.
    return b;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_max(a, b) → max(a, b)
 * 정수 a와 b를 입력받아 최대값(max(a, b))을 출력하는 함수
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_max(a, b) → max(a, b)
int bi_max(IN int a, IN int b)
{
    // Case 1: a ≥ b, then return a.
    if (a >= b)
        return a;

    // Case 2: a < b, then return b.
    return b;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_concatenation(**C, *A, *B) → C = A || B
 * bigint 배열 A와 B를 입력받아 A와 B를 연접하는 함수
 *  - wordlen(C) ⬅ wordlen(A) + wordlen(B)
 *  - sign(C) ⬅ sign(A)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_concatenation(**C, *A, *B) → C = A || B
void bi_concatenation(bigint **C, bigint *A, bigint *B)
{

    // wordlen(C) ⬅ wordlen(A) + wordlen(B)
    bi_new(C, A->wordlen + B->wordlen);

    // sign(C) ⬅ sign(A)
    if (A->sign == NEGATIVE)
        (*C)->sign = A->sign;

    for (int j = 0; j < B->wordlen; j++)
        (*C)->a[j] = B->a[j];

    for (int j = 0; j < A->wordlen; j++)
        (*C)->a[B->wordlen + j] = A->a[j];
}