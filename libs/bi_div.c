#include "../includes/bi.h"
#include "../includes/bi_op.h"

word bi_long_div_2word(IN bigint *A, IN word B)
{
    word Q = 0;
    word R = A->a[1];
    for (int j = w - 1; j >= 0; j--)
    {
        if (R >= pow2(w - 1))
        {
            Q += pow2(j);
            R = (R << 1) + get_j_bit(A->a[0], j) - B;
        }
        else
        {

            R = (R << 1) + get_j_bit(A->a[0], j);
            if (R >= B)
            {
                Q += pow2(j);
                R -= B;
            }
        }
    }

    return Q;
}

void bi_div_core2(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    int n = A->wordlen; /* n is wordlen(A) */
    int m = B->wordlen; /* n is wordlen(B) */

    word q;

    if (n == m) /* wordlen(A) == wordlen(B) */
    {
        q = A->a[m - 1] / B->a[m - 1];
    }
    if (n == m + 1)
    {
        if (A->a[m] == B->a[m - 1])
        {
            q = W; /*q = (2^w) - 1 */
        }
        else
        {
            bigint *T = NULL;
            bi_new(&T, 2);

            T->a[1] = A->a[m];
            T->a[0] = A->a[m - 1];

            q = bi_long_div_2word(T, B->a[m - 1]);

            bi_delete(&T);
        }
    }
    bigint *QQ = NULL;
    bi_new(&QQ, 1);
    QQ->a[0] = q;

    bigint *T = NULL;
    bi_mul_core(&T, B, QQ);

    bi_sub(R, A, T);

    q = QQ->a[0];

    while ((*R)->sign == NEGATIVE) /* At most 2 computations */
    {
        q--;
        bi_add_asg(R, B);
    }

    *Q = q;

    bi_delete(&QQ);
    bi_delete(&T);
}

void bi_div_core(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    if (bi_cmp(A, B) == -1)
    {
        *Q = 0;
        bi_assign(R, A);
        return;
    }

    int bitlen_b = bitlen(B->a[B->wordlen - 1]);
    int k = w - bitlen_b;

    bigint *RR = NULL;

    bigint *AA = NULL;
    bi_assign(&AA, A);

    bigint *BB = NULL;
    bi_assign(&BB, B);

    bi_lshift(&AA, k);
    bi_lshift(&BB, k);

    bi_div_core2(Q, &RR, AA, BB);

    bi_rshift(&RR, k);

    bi_assign(R, RR);

    bi_delete(&RR);
    bi_delete(&AA);
    bi_delete(&BB);
}

void bi_div(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    if (bi_is_zero(B) == true)
    {
        printf("# bi_div Error: B = 0, 정의 불가능(분수가 0임)\n");
        return;
    }
    if (bi_is_zero(A) == true)
    {
        bi_set_one(Q);
        bi_set_one(R);
        return;
    }
    if (bi_cmp(A, B) == -1)
    {
        bi_set_zero(Q);
        bi_assign(R, A);
        return;
    }

    int n = A->wordlen;
    bi_new(Q, n);
    bi_set_zero(R);

    // word q = 0;

    bigint *T = NULL;

    for (int j = n - 1; j >= 0; j--)
    {
        bi_assign(&T, *R);
        bi_word_lshift(&T, 1);

        bi_addi(&T, A->a[j]);
        bi_div_core(&(*Q)->a[j], R, T, B);
    }

    bi_refine(*Q);
    bi_delete(&T);
}

void bi_long_div_bin(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    bi_set_zero(Q);
    bi_set_zero(R);

    bigint *T = NULL;
    bi_set_one(&T);

    int n = A->wordlen; /* n is wordlen(A) */
    int bitlen_A = 0;

    if (n == 1)
        bitlen_A = bitlen(A->a[0]); /* bitlen_A is bitlen(A) */
    else
        bitlen_A = (n - 1) * w + bitlen(A->a[n - 1]);

    for (int j = bitlen_A - 1; j >= 0; j--)
    {
        bi_lshift(R, 1);
        (*R)->a[0] ^= bi_get_j_bit(A, j);

        if (bi_cmp(*R, B) == 1 || bi_cmp(*R, B) == 0)
        {
            bi_lshift(&T, j);
            bi_xor_asg(Q, T);

            bi_sub_asg(R, B); /* R -= B*/
            bi_set_one(&T);
        }
    }
    bi_delete(&T);
}

/* A와 B를 나누었을 때의 몫 Q를 반환하는 함수 */
void bi_div_q(OUT bigint **Q, IN bigint *A, IN bigint *B)
{
    bigint *T = NULL;
    bi_div(Q, &T, A, B);

    bi_delete(&T);
}

/* A와 B를 나누었을 때의 나머지 R을 반환하는 함수 */
void bi_div_r(OUT bigint **R, IN bigint *A, IN bigint *B)
{
    bigint *T = NULL;
    bi_div(&T, R, A, B);

    bi_delete(&T);
}

/* R %= N */
void bi_mod_asg(OUT bigint **R, IN bigint *N)
{
    if (bi_cmp(*R, N) == -1)
        return;

    if (bi_is_zero(N) == true)
    {
        printf("# Error: R = R mod N. but, N is zero");
        return;
    }
    bigint *q = NULL;
    bigint *T = NULL;

    bi_assign(&T, *R);

    bi_div(&q, R, T, N);

    bi_delete(&q);
    bi_delete(&T);
}

/* Q /= A */
void bi_div_asg(OUT bigint **Q, IN bigint *A)
{
    bigint *r = NULL;
    bigint *T = NULL;
    if (bi_is_zero(A) == true)
        return;
    bi_assign(&T, *Q);

    bi_div(Q, &r, T, A);

    bi_delete(&r);
    bi_delete(&T);
}
