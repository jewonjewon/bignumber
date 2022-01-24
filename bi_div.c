#include "bi.h"
#include "bi_op.h"

word bi_long_div_2word(IN bigint *A, IN word B)
{

    if (A->a[1] >= B)
    {
        printf("# 띠용?\n");
    }

    word Q = 0;
    word R = A->a[1];
    for (int j = w - 1; j >= 0; j--)
    {
        if (R >= pow2(w - 1))
        {
            Q = Q + pow2(j);
            R = (R << 1) + get_j_bit(A->a[0], j) - B;
        }
        else
        {

            R = (R << 1) + get_j_bit(A->a[0], j);
            if (R >= B)
            {
                Q = Q + pow2(j);
                R = R - B;
            }
        }
    }

    return Q;
}

void bi_DIVCC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    int n = A->wordlen;
    int m = B->wordlen;

    word q;

    if (n == m)
    {
        q = A->a[m - 1] / B->a[m - 1];
    }
    if (n == m + 1)
    {
        if (A->a[m] == B->a[m - 1])
        {
            q = W;
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
    bi_MULC(&T, B, QQ);

    bi_SUB(R, A, T);

    q = QQ->a[0];
    //
    int cnt = 0;

    // 여기가 문제
    // printf("# R = ");
    // bi_print(*R);
    // printf("# B = ");
    // bi_print(B);

    while ((*R)->sign == NEGATIVE)
    {
        check;
        q--;

        bi_ADD(R, *R, B);
        cnt++;
        // printf("# R = ");
        // bi_print(*R);
        // printf("# B = ");
        // bi_print(B);
        if (cnt == 10)
        {
            printf("# STOP!\n");
            return;
        }
    }

    *Q = q;

    bi_delete(&QQ);
    bi_delete(&T);
}

void bi_DIVC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B)
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

    bi_DIVCC(Q, &RR, AA, BB);

    bi_rshift(&RR, k);

    bi_assign(R, RR);

    bi_delete(&RR);
    bi_delete(&AA);
    bi_delete(&BB);
}

void bi_DIV(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{

    if (bi_cmp(A, B) == -1)
    {
        bi_set_zero(Q);
        bi_assign(R, A);
        return;
    }

    int n = A->wordlen;
    bi_new(Q, n);
    bi_set_zero(R);

    word q = 0;

    bigint *T = NULL;
    bigint *TT = NULL;
    bigint *TTT = NULL;

    for (int j = n - 1; j >= 0; j--)
    {
        bi_assign(&T, *R);
        bi_word_lshift(&T, 1);

        bi_new(&TT, 1);
        TT->a[0] = A->a[j];

        bi_ADD(&TTT, T, TT);

        bi_DIVC(&q, R, TTT, B);

        (*Q)->a[j] = q;
        q = 0;
    }

    bi_refine(*Q);
    bi_delete(&T);
    bi_delete(&TT);
    bi_delete(&TTT);
}
