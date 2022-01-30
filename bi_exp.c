#include "bi.h"
#include "bi_op.h"

void bi_mod_asg(OUT bigint **R, IN bigint *N)
{
    bigint *q = NULL;
    bigint *T = NULL;

    bi_assign(&T, *R);

    bi_DIV(&q, R, T, N);

    bi_delete(&q);
    bi_delete(&T);
}
/* Q /= A */
void bi_div_asg(OUT bigint **Q, IN bigint *A)
{
    bigint *r = NULL;
    bigint *T = NULL;

    bi_assign(&T, *Q);

    bi_DIV(Q, &r, T, A);

    bi_delete(&r);
    bi_delete(&T);
}

int bi_get_j_bit(bigint *A, int n)
{
    int q = n % w;
    int r = n / w;

    int j_th_bit = get_j_bit(A->a[r], r);

    return j_th_bit;
}

void bi_l2r(bigint **C, bigint *A, bigint *n)
{
    bigint *T = NULL;
    bi_set_one(&T);

    for (int j = bi_bit_cnt(n) - 1; j >= 0; j--)
    {
        bi_ksqu_asg(&T); /* n의 비트 길이만큼 제곱 연산 수행  */

        if (bi_get_j_bit(n, j) == 1) /* n의 j번째 비트가 1일 때만 곱셈 연산 수행 */
            bi_kmul_asg(&T, A);
    }
    bi_assign(C, T);
    bi_delete(&T);
}

void bi_mod_l2r(OUT bigint **C, IN bigint *A, IN int n, IN bigint *M)
{
    bigint *T = NULL;

    bi_set_one(&T);

    for (int j = bitlen(n) - 1; j >= 0; j--)
    {
        bi_ksqu_asg(&T);
        bi_mod_asg(&T, M);

        if (get_j_bit(n, j) == 1)
        {
            bi_kmul_asg(&T, A);
            bi_mod_asg(&T, M);
        }
    }
    bi_assign(C, T);
    bi_delete(&T);
}

void bi_r2l(bigint **C, bigint *A, int n)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);
    bi_assign(&T1, A);

    for (int j = 0; j < bitlen(n); j++)
    {
        if (get_j_bit(n, j) == 1)
            bi_kmul_asg(&T0, T1);

        bi_ksqu_asg(&T1);
    }
    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}

void bi_mns(bigint **C, bigint *A, int n)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);   /* T0 = 0 */
    bi_assign(&T1, A); /* T1 ← A */

    for (int j = bitlen(n) - 1; j >= 0; j--)
    {

        if (get_j_bit(n, j) == 1)
        {
            bi_kmul_asg(&T0, T1);
            bi_ksqu_asg(&T1);
        }
        else
        {
            bi_kmul_asg(&T1, T0);
            bi_ksqu_asg(&T0);
        }
    }
    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}

void bi_mont_red(OUT bigint **C, IN bigint *x, IN bigint *R, IN bigint *N)
{

    /* step 1. N의 역원구하기  (사전계산 가능)*/
    bigint *NN = NULL; /* NN = -(inv_N) */
    bigint *m = NULL;
    bigint *t = NULL;

    bi_eea_itr(&NN, N, R);
    bi_flip_sign(NN);

    printf("NN = ");
    bi_print(NN);

    /* m = ((x mod R) * NN) mod R */
    bi_mod_asg(&x, R);
    bi_KMUL(&m, x, NN);
    bi_mod_asg(&m, R);

    printf("m = ");
    bi_print(m);

    bi_mul_asg(&m, N);
    bi_ADD(&t, x, m);
    bi_word_rshift(&t, R->wordlen);

    printf("t = ");
    bi_print(t);

    if (bi_cmp(t, N) == 1 or bi_cmp(t, N) == 0)
        bi_sub_asg(&t, N);

    bi_assign(C, t);

    bi_delete(&NN);
    bi_delete(&m);
    bi_delete(&t);
}
