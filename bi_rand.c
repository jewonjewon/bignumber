#include "bi_rand.h"

void arr_rand(word *dst, IN int wordlen)
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

void arr_rand_range(word *dst, IN int lbound, int ubound)
{
    unsigned char *p = (unsigned char *)dst;

    if (lbound > ubound)
    {
        printf("# bi_rand_range error, lbound 크기가 ubound를 초과합니다.\n");
        return;
    }

    ubound -= lbound;
    printf("ubound = %d\n", ubound);
    ubound = rand() % ubound;
    printf("ubound = %d\n", ubound);
    int cnt = ubound + lbound;
    printf("%d = %d + %d\n", cnt, lbound, ubound);
    int q = cnt / w;
    int r = cnt % w;

    while (q > 0)
    {
        *p = rand() & 0xff;
        p++;
        q--;
    }

    for (int j = 0; j < r - 1; j++)
        *p = *p + (pow2(j) * (rand() % 2));
    *p = *p + (pow2(r - 1));
}

void bi_gen_rand(OUT bigint **A, IN int sign, IN int wordlen)
{
    bi_new(A, wordlen);
    (*A)->sign = sign;
    arr_rand((*A)->a, wordlen);

    bi_refine(*A);
}

void bi_gen_rand_range(OUT bigint **A, IN int sign, IN int lbound, int ubound)
{
    int wordlen = (ubound / w) + 1;
    bi_new(A, wordlen);
    (*A)->sign = sign;

    arr_rand_range((*A)->a, lbound, ubound);

    bi_refine(*A);
}

void bi_gen_rand_bit(bigint **C, bigint *A)
{
    int k = bi_bit_cnt(A); /* k: A의 비트길이 */

    int q = k / w;
    int r = k % w;

    bigint *K = NULL;
    bi_new(&K, A->wordlen);

    bi_gen_rand(&K, NON_NEGATIVE, K->wordlen);

    if (r != 0)
        K->a[K->wordlen - 1] &= (pow2(r) - 1);

    bi_assign(C, K);

    bi_delete(&K);
}

/* 0 ~ (A-1) 사이의 수를 랜덤하게 선택하는 함수 */
void bi_SPDM(bigint **C, bigint *A)
{
    bigint *K = NULL;
    bigint *D = NULL;
    bigint *T = NULL;
    bigint *TT = NULL;

    bi_assign(&T, A);
    bi_subi(&T, 1);

    bi_gen_rand_bit(&K, T);

    int k = bi_bit_cnt(T);

    while (1)
    {
        /* 난수 선택 범위 내 */
        if (bi_cmp(K, A) == -1)
        {
            bi_assign(C, K);
            bi_refine(*C);

            bi_delete(&D);
            bi_delete(&K);
            bi_delete(&T);
            bi_delete(&TT);
            return;
        }

        /* 난수 선택 범위 벗어남 */
        bigint *G = NULL;

        bi_set_one(&G);
        bi_sub_asg(&T, G); /* i-1 */

        bi_xor(&G, K, T); /* c ^ (i-1) */

        int d = k - bi_bit_cnt(G);

        bi_delete(&G);

        int qq = d / w;
        int rr = d % w;

        bigint *D = NULL;

        bi_new(&D, qq + 1);

        bi_gen_rand(&D, NON_NEGATIVE, D->wordlen);

        if (rr != 0)
            D->a[D->wordlen - 1] &= (pow2(rr) - 1);

        bi_lshift(&K, d);
        bi_red(&K, k - d);

        bi_or_asg(&K, D);
    }
}
/* bitlen 비트의 랜덤한 정수 C를 출력하는 함수 ex) bitlen = 500, then bitlen(C) = 500 */
void bi_gen_random_element(OUT bigint **C, int sign, int bitlen)
{
    int q = bitlen / w + 1;
    int r = bitlen % w;

    do
    {
        bi_gen_rand(C, sign, q);
    } while (bi_is_zero(*C) == true);

    if (q == 0)
    {
        return;
    }

    (*C)->a[(*C)->wordlen - 1] &= (pow2(r) - 1);
    (*C)->a[(*C)->wordlen - 1] |= pow2(r - 1);

    bi_refine(*C);
}