#include "bi_local.h"
#include "bi_op.h"

// #define bitlen(a)        \
//     {                    \
//         int cnt = 0;     \
//         do               \
//         {                \
//             a = a >> 1;  \
//             cnt++        \
//         } while (a > 0); \
//     }

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

// // bi_MULC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
// void bi_MULC(OUT bigint **C, IN bigint *A, IN word B)
// {
//     bi_new(C, A->wordlen + 1);
//     bigint *T = NULL;

//     for (int j = 0; j < A->wordlen; j++)
//         for (int i = 0; i < B->wordlen; i++)
//         {
//             // bi_resize 함수 안쓰고 ADD 함수로 대체하는 방법도 있음 어느것을 쓸지 고민 중
//             bi_resize(C, A->wordlen + 1);
//             bi_new(&T, 2);

//             bi_MUL_AB(&T, A->a[j], B);
//             bi_MUL_AB(&T, A->a[j], B->a[i]);
//             // printf("1. T = ");
//             // bi_print(T);

//             bi_word_lshift(&T, j);
//             bi_word_lshift(&T, i + j);
//             // printf("2. T = ");
//             // bi_print(T);

//             bi_ADDC(C, *C, T);
//             bi_ADDC(C, *C, T);
//             // printf("3. C = ");
//             // bi_print(*C);
//             printf("j = %d i = %d\n", j, i);
//             printf("wordlen(B) = %d\n", B->wordlen);
//         }

//     bi_delete(&T);
// }

// void bi_bigintA_mul_wordB(bigint **C, bigint *A, word B)
// {
//     A->a[0] = A->a[0] * B;
//     bigint *T = NULL;
//     bi_MUL_AB(&T, A->a[0], B);
//     (*C)->a[0] = T->a[0];
//     bi_ADD_ABc()
//         bi_ADDC(C, A, )(*C)
//             ->a[1] = T->a[1];
// }
// 음수 = 1, 음이 아닌 정수 = 0

int bi_is_negative(bigint *A)
{
    if (A->sign == NEGATIVE)
        return 1;
    else
        return 0;
}

word bi_long_div_2word(IN bigint *A, IN word B)
{
    printf("\n# bi_long_div_2word\n");
    newline;
    if (A->a[1] >= B)
    {
        printf("error\n");
        return 0;
    }
    printf("AA = ");
    bi_print(A);
    newline;
    word Q = 0;
    word R = A->a[1];
    for (int j = w - 1; j >= 0; j--)
    {
        if (R >= pow(w - 1))
        {
            Q = Q + pow(j);
            // printf("#%d-th Q = %#x\n", j, Q);
            R = (R << 1) + get_j_bit(A->a[0], j) - B;
            // printf("#%d-th R = %#x\n", j, R);
        }
        else
        {

            R = (R << 1) + get_j_bit(A->a[0], j);
            if (R >= B)
            {
                Q = Q + pow(j);
                // printf("#%d-th Q = %#x\n", j, Q);
                R = R - B;
                // printf("#%d-th R = %#x\n", j, R);
            }
        }
    }
    return Q;
}

void bi_DIVCC(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    printf("\n# bi_DIVCC\n");
    newline;
    printf("if B_(m-1) ≥ 2^(w-1)?\n");
    printf("%x >= %x?\n", B->a[B->wordlen - 1], pow(w - 1));
    printf("%d\n", B->a[B->wordlen - 1] >= pow(w - 1));

    int n = A->wordlen;
    int m = B->wordlen;
    printf("# wordlen(A) = %d, wordlen(B) = %d\n", n, m);

    printf("A = ");
    bi_print(A);

    printf("B = ");
    bi_print(B);

    word q;

    if (n == m)
        q = A->a[m - 1] / B->a[m - 1];

    if (n == m + 1)
    {
        if (A->a[m] == B->a[m - 1])
        {
            q = W;
            // printf("1. q = %x\n", q);
        }

        else
        {
            bigint *T = NULL;
            bi_new(&T, 2);

            T->a[1] = A->a[m];
            T->a[0] = A->a[m - 1];
            // bi_print(T);
            // printf("%#x\n", B->a[m - 1]);

            q = bi_long_div_2word(T, B->a[m - 1]);
            // printf("2. q = %x\n", q);
            bi_delete(&T);
        }
    }

    bi_new(Q, 1);
    (*Q)->a[0] = q;
    bigint *T = NULL;

    bi_MULC(&T, B, *Q);
    bi_SUB(R, A, T);

    while (bi_is_negative(*R))
    {
        (*Q)->a[0]--;
        bi_ADDC(R, *R, B);
        printf("# R' = ");
        bi_print(*R);
        // check;
    }

    bi_delete(&T);
}

// void bi_DIVC(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     printf("\n# bi_DIVC\n");
//     newline;

//     if (bi_cmp(A, B) == -1)
//     {
//         bi_set_zero(Q);
//         bi_assign(R, A);
//         return;
//     }

//     bigint *QQ = NULL;
//     bigint *RR = NULL;
//     bigint *AA = NULL;
//     bigint *BB = NULL;
//     int k = 0;

//     // word t = B->a[B->wordlen - 1];
//     int bitlen_b = bitlen(B->a[B->wordlen - 1]);
//     printf("#B_(m-1) = %#x\n", B->a[B->wordlen - 1]);
//     printf("#bitlen_b = %d\n", bitlen_b);

//     k = w - bitlen_b;

//     printf("#k = %d\n", k);
//     bi_assign(&AA, A);
//     bi_assign(&BB, B);
//     bi_lshift(&AA, pow(k));
//     bi_lshift(&BB, pow(k));

//     bi_DIVCC(&QQ, &RR, AA, BB);

//     bi_assign(Q, QQ);
//     bi_rshift(&RR, pow(k));
//     bi_assign(R, RR);

//     bi_delete(&QQ);
//     bi_delete(&RR);
//     bi_delete(&AA);
//     bi_delete(&BB);
// }

void bi_DIVC(OUT word *word_Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    printf("\n# bi_DIVC\n");
    newline;

    if (bi_cmp(A, B) == -1)
    {
        printf("# bi_DIVC if 문\n");
        *word_Q = 0;
        bi_assign(R, A);
        return;
    }

    bigint *QQ = NULL;
    bigint *RR = NULL;
    bigint *AA = NULL;
    bigint *BB = NULL;

    int k = 0;

    int bitlen_b = bitlen(B->a[B->wordlen - 1]);

    // printf("#B_(m-1) = %#x\n", B->a[B->wordlen - 1]);
    // printf("#bitlen_b = %d\n", bitlen_b);

    k = w - bitlen_b;
    printf("k = %d\n", k);

    // printf("#k = %d\n", k);

    bi_assign(&AA, A);
    bi_assign(&BB, B);
    bi_lshift(&AA, pow(k));
    bi_lshift(&BB, pow(k));

    printf("AA = ");
    bi_print(AA);
    printf("BB = ");
    bi_print(BB);

    bi_DIVCC(&QQ, &RR, AA, BB);

    // bi_assign(Q, QQ);
    *word_Q = QQ->a[0];
    bi_rshift(&RR, pow(k));
    bi_assign(R, RR);

    bi_delete(&QQ);
    bi_delete(&RR);
    bi_delete(&AA);
    bi_delete(&BB);
}

void bi_DIV(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
{
    word word_Q = 0;
    int n = A->wordlen;

    if (bi_cmp(A, B) == -1)
    {
        bi_set_zero(Q);
        bi_assign(R, A);
        return;
    }

    bigint *T = NULL;
    bi_set_zero(&T);

    bi_set_zero(R);
    bi_new(Q, n);

    for (int j = n - 1; j >= 0; j--)
    {
        printf("bi_DIV for-loop\n");
        bi_word_lshift(&T, 1);
        T->a[0] = A->a[j];

        printf("R = ");
        bi_print(T);

        bi_DIVC(&word_Q, R, T, B);

        printf("R = ");
        bi_print(T);

        if (j == n - 3)
            return;
        (*Q)->a[j] = word_Q;
        word_Q = 0;
    }

    bi_delete(&T);
}
