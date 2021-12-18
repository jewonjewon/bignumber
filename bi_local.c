#include "bi_local.h"

void bi_delete(IN OUT bigint **A)
{
    if (*A == NULL)
        return;

#ifdef ZEROLIZE
    // 입력 배열 초기화
    Aay_init((*A)->a, (*A)->wordlen);
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

void test()
{
    printf("hello World!\n");
    printf("출력 확인용");
}

void bi_print(bigint *A)
{
    if (A->sign == NEGATIVE)
        printf("-");

#if (w == 64)
    printf("%llx ", A->a[A->wordlen - 1]);
    for (int j = A->wordlen - 2; j >= 0; j--)
        printf("%016llx ", A->a[j]);

#elif (w == 32)
    printf("%llx ", A->a[A->wordlen - 1]);
    for (int j = A->wordlen - 2; j >= 0; j--)
        printf("%08llx ", A->a[j]);

#elif (w == 8)
    printf("%llx ", A->a[A->wordlen - 1]);
    for (int j = A->wordlen - 2; j >= 0; j--)
        printf("%016llx ", A->a[j]);
#endif
    printf("\n");
}

void Aay_rand(word *dst, IN int wordlen)
{
    unsigned char *p = (unsigned char *)dst;
    int cnt = wordlen * sizeof(word);
    while (cnt > 0)
    {
        *p = rand() & 0xff;
        p++;
        cnt--;
    }
}
// bi_gen_rand()
void bi_gen_rand(OUT bigint **A, IN int sign, IN int wordlen)
{
    bi_new(A, wordlen);
    (*A)->sign = sign;
    Aay_rand((*A)->a, wordlen);

    bi_refine(*A);
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

int bi_is_zero(bigint *A)
{
    // Case: A <0 or A[0] != 0
    if (A->sign == NEGATIVE or A->a[0] != 0)
        return false;

    for (int j = A->wordlen - 1; j > 0; j--)
        if (A->a[j] != 0)
            return false;
    return true;
}

int bi_is_one(bigint *A)
{
    if (A->sign == NEGATIVE or A->a[0] != 1)
        return false;

    for (int j = A->wordlen - 1; j > 0; j--)
        if (A->a[j] != 0)
            return false;
    return true;
}

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