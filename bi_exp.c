#include "bi.h"
#include "bi_op.h"

void bi_l2r(OUT bigint **C, IN bigint *A, IN bigint *n)
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

void bi_r2l(OUT bigint **C, IN bigint *A, IN bigint *n)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);
    bi_assign(&T1, A);

    for (int j = 0; j < bi_bit_cnt(n); j++)
    {
        if (bi_get_j_bit(n, j) == 1)
            bi_kmul_asg(&T0, T1); /* n의 j번째 비트가 1일 때만 곱셈 연산 수행 */

        bi_ksqu_asg(&T1); /* n의 비트 길이만큼 제곱 연산 수행  */
    }

    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}

void bi_mns(OUT bigint **C, IN bigint *A, IN bigint *n)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);   /* T0 = 0 */
    bi_assign(&T1, A); /* T1 ← A */

    for (int j = bi_bit_cnt(n) - 1; j >= 0; j--)
    {

        if (bi_get_j_bit(n, j) == 1)
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

void bi_mod_exp_l2r(OUT bigint **C, IN bigint *A, IN bigint *n, IN bigint *M)
{
    bigint *T = NULL;
    bi_set_one(&T);

    for (int j = bi_bit_cnt(n) - 1; j >= 0; j--)
    {
        bi_ksqu_asg(&T);
        // printf("#  T = ");
        // bi_print(T);
        bi_mod_asg(&T, M);

        // printf("# (squ) T = ");
        // bi_print(T);

        if (bi_get_j_bit(n, j) == 1)
        {
            bi_kmul_asg(&T, A);
            bi_mod_asg(&T, M);

            // printf("# (mul) T = ");
            // bi_print(T);
        }
    }
    bi_assign(C, T);
    bi_delete(&T);
}

void bi_mod_exp_l2r_asg(OUT bigint **C, IN bigint *n, IN bigint *M)
{
    bigint *T = NULL;
    bi_assign(&T, *C);
    bi_mod_exp_l2r(C, T, n, M);
    bi_delete(&T);
}

void bi_mod_exp_r2l(OUT bigint **C, IN bigint *A, IN bigint *n, IN bigint *M)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);
    bi_assign(&T1, A);

    for (int j = 0; j < bi_bit_cnt(n); j++)
    {
        if (bi_get_j_bit(n, j) == 1)
        {
            bi_kmul_asg(&T0, T1); /* n의 j번째 비트가 1일 때만 곱셈 연산 수행 */
            bi_mod_asg(&T0, M);
        }

        bi_ksqu_asg(&T1); /* n의 비트 길이만큼 제곱 연산 수행  */
        bi_mod_asg(&T1, M);
    }

    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}

void bi_mod_exp_mns(OUT bigint **C, IN bigint *A, IN bigint *n, IN bigint *M)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_set_one(&T0);   /* T0 = 0 */
    bi_assign(&T1, A); /* T1 ← A */

    for (int j = bi_bit_cnt(n) - 1; j >= 0; j--)
    {
        if (bi_get_j_bit(n, j) == 1)
        {
            bi_kmul_asg(&T0, T1);
            bi_mod_asg(&T0, M);

            bi_ksqu_asg(&T1);
            bi_mod_asg(&T1, M);
        }
        else
        {
            bi_kmul_asg(&T1, T0);
            bi_mod_asg(&T1, M);

            bi_ksqu_asg(&T0);
            bi_mod_asg(&T0, M);
        }
    }
    bi_assign(C, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}

void bi_mont_red(OUT bigint **C, IN bigint *x, IN bigint *R,
                 IN bigint *n, IN bigint *nn)
{

    /* step 1. N의 역원구하기  (사전계산 가능)*/
    bigint *m = NULL;
    bigint *t = NULL;

    // bigint *nn = NULL; /* nn = -(inv_N) */
    // bi_eea_itr(&nn, n, R);

    /* m = ((x mod R) * nn) mod R */
    bi_word_reduction(&x, R->wordlen - 1);

    bi_print("x", x);

    bi_kmul(&m, x, nn);

    bi_print("m", m);
    bi_word_reduction(&m, R->wordlen - 1);

    bi_print("m", m);

    bi_mul_asg(&m, n);
    bi_add(&t, x, m);
    bi_word_rshift(&t, R->wordlen - 1);

    bi_print("t", t);

    if (bi_cmp(t, n) == 1 or bi_cmp(t, n) == 0)
        bi_sub_asg(&t, n);

    bi_assign(C, t);

    bi_delete(&m);
    bi_delete(&t);
}

// void bi_mod_exp_mont_l2r(bigint **x, bigint *e, bigint *n,
//                          bigint *nn, bigint *r, bigint *phi_1)
// {
//     bigint *phi_x = NULL;
//     bigint *t = NULL;

//     bi_assign(&phi_x, *x);

//     bi_lshift(phi_x, bi_bit_cnt(r) - 1);

//     bi_mod_asg(&phi_x, n);

//     int l = bi_bit_cnt(r) - 1; /* l is bitlen(r). */

//     bi_assign(&t, phi_1);

//     for (int j = l - 1; j >= 0; j--) /* for j = bitlen(t)-1 to 0 do */
//     {

//         // SQU t
//         bi_rshift(&e, 1);
//         if (== 1)
//             // t ← t * phi(x)
//             return;
//     }

//     // t ← mont_red(t)

//     bi_assign(x, t);

//     bi_delete(&phi_x);
//     bi_delete(&t);
// }