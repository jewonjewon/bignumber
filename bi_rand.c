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
/* 0 ~ (i-1) 사이의 수를 랜덤하게 선택하는 함수 */
// int bi_SPDM(int i)
// {

//     // k: i 의 비트 길이
//     int k = bitlen(i - 1);

//     int c;
//     uint16_t K = 0;
//     uint16_t D = 0;
//     K = rand() % (1 << k); // 수정됨

//     // 랜덤 k비트 생성
//     // for (int j = 0; j < k; j++)
//     // {
//     //     K = K + (bit[check_bit2] * (1 << j));
//     //     check_bit2++;
//     // }
//     while (1)
//     {
//         c = K;

//         /* 난수 선택 범위 내 */
//         if (c < i)
//             return c;

//         /* 난수 선택 범위 벗어남 */
//         int d = k - bitlen(c ^ (i - 1)) - 1;

//         // 숫자로 난수 뽑기
//         D = rand() % (1 << (d + 1));

//         // 비트로 난수 뽑기,  D = 랜덤 d+1 비트열
//         // for (int j = 0; j < d; j++)
//         // {
//         //     D = D + (bit[check_bit2] * (1 << j));
//         //     check_bit2++;
//         // }

//         K = (K << (d + 1)) % (1 << (k - d));
//         K = K | D;
//     }
// }

// void bi_gen_rand_bit(bigint **C, bigint *A, int *bitlen_A)
// {
//     int k = bi_bit_cnt(A); /* k: A의 비트길이 */
//     *bitlen_A = k;

//     int q = k / w;
//     int r = k % w;
//     printf("q , r = %d, %d\n", q, r);

//     bigint *K = NULL;
//     bi_new(&K, A->wordlen);

//     bi_gen_rand(&K, NON_NEGATIVE, K->wordlen);

//     // if (r == 0)
//     // else
//     // {
//     //     for (int j = 0; j < q; j++)
//     //         for (int i = 0; i < (w / 8); i++)
//     //         { /*  */
//     //             K->a[j] = K->a[j] | ((rand() & (pow2(8) - 1)) << (8 * i));
//     //             // bi_print(K);
//     //             // check;
//     //         }
//     //     K->a[q] = rand() & (pow2(r) - 1);
//     // }

//     if (r != 0)
//         K->a[K->wordlen - 1] &= (pow2(r) - 1);

//     bi_assign(C, K);

//     bi_delete(&K);
// }

// /* 0 ~ (A-1) 사이의 수를 랜덤하게 선택하는 함수 */
// void bi_SPDM(bigint **C, bigint *A)
// {
//     bigint *K = NULL;
//     bigint *D = NULL;
//     bigint *T = NULL;
//     bigint *TT = NULL;

//     bi_assign(&T, A);
//     bi_sub_minus_one(&T);

//     // printf("A - 1 = ");
//     // bi_print(T);

//     int k = 0;

//     bi_gen_rand_bit(&K, T, &k);

//     // printf("K = ");
//     // bi_print(K);

//     printf("bitlen(A) = %d\n", bi_bit_cnt(A));
//     printf("bitlen(K) = %d\n", bi_bit_cnt(K));

//     while (1)
//     {
//         /* 난수 선택 범위 내 */
//         if (bi_cmp(K, A) == -1)
//         {

//             bi_assign(C, K);
//             bi_refine(*C);
//             bi_delete(&D);
//             bi_delete(&K);
//             bi_delete(&T);
//             bi_delete(&TT);
//             return;
//         }

//         /* 난수 선택 범위 벗어남 */
//         bigint *G = NULL;

//         bi_set_one(&G);
//         bi_sub_asg(&T, G); /* i-1 */

//         bi_XOR(&G, K, T); /* c ^ (i-1) */

//         // int d = k - bitlen(c ^ (i - 1)) - 1;
//         // int d = k - bi_bit_cnt(G) - 1;

//         int d = k - bi_bit_cnt(G);

//         printf("d + 1 = %d\n", d);

//         int qq = d / w;
//         int rr = d % w;

//         bigint *D = NULL;

//         bi_new(&D, qq + 1);

//         bi_gen_rand(&D, NON_NEGATIVE, D->wordlen);

//         if (rr != 0)
//             D->a[D->wordlen - 1] &= (pow2(rr) - 1);

//         // printf("D = ");
//         // bi_print(D);

//         // if (rr != 0)
//         //     D->a[D->wordlen - 1] &= (pow2(rr) - 1);

//         // for (int j = 0; j < D->wordlen; j++)
//         //     for (int i = 0; i < w / 8; i++)
//         //         D->a[j] = D->a[j] | ((rand() & (pow2(8) - 1)) << (8 * i));

//         // 숫자로 난수 뽑기
//         // D = rand() % (1 << (d + 1));
//         // bi_rshift(&K, d);
//         bi_lshift(&K, d);
//         bi_red(&K, k - d);
//         // printf("K = ");
//         // bi_print(K);

//         bi_or_asg(&K, D);
//     }
// }

void bi_gen_rand_bit(bigint **C, bigint *A, int *bitlen_A)
{
    int k = bi_bit_cnt(A); /* k: A의 비트길이 */
    *bitlen_A = k;

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
    bi_sub_minus_one(&T);

    int k = 0;

    bi_gen_rand_bit(&K, T, &k);

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

        bi_XOR(&G, K, T); /* c ^ (i-1) */

        int d = k - bi_bit_cnt(G);

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
