// #include "bi.h"
// #include "bi_op.h"

// int bitlen(word a)
// {
//     word cnt = 0;

//     do
//     {
//         a = a >> 1;
//         cnt++;
//     } while (a > 0);

//     return cnt;
// }

// word bi_long_div_2word(IN bigint *A, IN word B)
// {
//     printf("#long_div A = ");
//     bi_print(A);
//     printf("#long_div B = %#llx\n", B);

//     if (A->a[1] >= B)
//     {
//         printf("#띠용\n");
//         printf("#띠용\n");
//         printf("#띠용\n");
//         printf("#띠용\n");
//         printf("#띠용\n");
//     }
//     // printf("# long_div_2word A1 ≥ B, 조건 성립 x\n");

//     word Q = 0;
//     word R = A->a[1];
//     for (int j = w - 1; j >= 0; j--)
//     {
//         if (R >= pow2(w - 1))
//         {
//             Q = Q + pow2(j);
//             R = (R << 1) + get_j_bit(A->a[0], j) - B;
//         }
//         else
//         {

//             R = (R << 1) + get_j_bit(A->a[0], j);
//             if (R >= B)
//             {
//                 Q = Q + pow2(j);
//                 R = R - B;
//             }
//         }
//     }

//     printf("#bi_long_div_2word Q = %llx\n", Q);
//     printf("#이거왜안뜨냐?%#llx\n", Q);
//     return Q;
// }

// void bi_DIVCC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     int n = A->wordlen;
//     int m = B->wordlen;

//     printf("#wordlen(A) = %d, wordlen(B) = %d\n", A->wordlen, B->wordlen);
//     word q;

//     if (n == m)
//     {
//         q = A->a[m - 1] / B->a[m - 1];
//     }
//     if (n == m + 1)
//     {
//         if (A->a[m] == B->a[m - 1])
//         {
//             q = W;
//         }
//         else
//         {
//             // printf("### A1 < B? 1이면 참 0이면 거짓: %d\n", A->a[m] < B->a[m - 1]);

//             bigint *T = NULL;
//             bi_new(&T, 2);

//             T->a[1] = A->a[m];
//             T->a[0] = A->a[m - 1];

//             printf("#A' = ");
//             bi_print(T);
//             printf("#B' = ");
//             bi_print(B);

//             q = bi_long_div_2word(T, B->a[m - 1]);
//             // printf("1. 1-word q = %llx\n", q);
//             bi_delete(&T);
//         }
//     }
//     bigint *QQ = NULL;
//     bi_new(&QQ, 1);
//     QQ->a[0] = q;
//     bigint *T = NULL;
//     bi_MULC(&T, B, QQ);
//     // printf("2. BQ = ");
//     // bi_print(T);

//     bi_SUB(R, A, T);

//     // printf("3. A - BQ = ");
//     // bi_print(*R);

//     // *Q = QQ->a[0];
//     q = QQ->a[0];
//     int cnt = 0;
//     // 여기가 문제

//     while ((*R)->sign == NEGATIVE)
//     {
//         check;
//         q--;

//         bi_ADD(R, *R, B);
//         cnt++;
//     }
//     printf("#bi_DIVCC Q = %#llx\n", q);
//     *Q = q;

//     // printf("while문 반복 횟수:%d\n", cnt);
//     bi_delete(&T);
// }

// void bi_DIVC(OUT word *Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     // printf("\n# bi_DIVC\n");
//     // newline;

//     if (bi_cmp(A, B) == -1)
//     {
//         *Q = 0;
//         bi_assign(R, A);
//         return;
//     }
//     // int k = 0;
//     int bitlen_b = bitlen(B->a[B->wordlen - 1]);
//     printf("# B_{m-1} = %#llx\n", B->a[B->wordlen - 1]);
//     if (pow2(w - 1) <= B->a[B->wordlen - 1] and B->a[B->wordlen - 1] <= W)
//         printf("# DIVC k 조건 성립!\n");
//     printf("# bitlen(B_{m-1}) = %d\n", bitlen_b);
//     int k = w - bitlen_b;
//     printf("#k = %d\n", k);

//     bigint *RR = NULL;

//     bigint *AA = NULL;
//     bi_assign(&AA, A);

//     bigint *BB = NULL;
//     bi_assign(&BB, B);

//     printf("#DIVC A = ");
//     bi_print(AA);
//     printf("#DIVC B = ");
//     bi_print(BB);

//     if (k >= 1)
//     {
//         bi_lshift(&AA, k);
//         bi_lshift(&BB, k);
//     }
//     newline;
//     printf("#shift DIVC A = ");
//     bi_print(AA);
//     printf("#shift DIVC B = ");
//     bi_print(BB);
//     newline;

//     bi_DIVCC(Q, &RR, AA, BB);

//     printf("#너?%llx\n", *Q);

//     printf("#bi_DIVC Q = %llx\n", *Q);

//     if (k >= 1)
//         bi_rshift(&RR, k);

//     bi_assign(R, RR);

//     bi_delete(&RR);
//     bi_delete(&AA);
//     bi_delete(&BB);
// }

// void bi_DIV(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     printf("#시작!!!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//     if (bi_cmp(A, B) == -1)
//     {
//         bi_set_zero(Q);
//         bi_assign(R, A);
//         return;
//     }

//     int n = A->wordlen;
//     bi_new(Q, n);
//     bi_set_zero(R);

//     word q = 0;

//     bigint *T = NULL;
//     bigint *TT = NULL;
//     for (int j = n - 1; j >= 0; j--)
//     {
//         bi_assign(&T, *R);
//         bi_word_lshift(&T, 1);

//         bi_new(&TT, 1);
//         TT->a[0] = A->a[j];

//         bi_ADD(&T, T, TT);
//         printf("#DIV 진입 전: ");
//         bi_print(T);

//         printf("#DIV: wordlen(T) = %d, wordlen(B) = %d\n", T->wordlen, B->wordlen);

//         bi_DIVC(&q, R, T, B);
//         // bi_assign(&T, *R);
//         printf("#bi_DIV Q[%d] = %#llx\n", j, q);
//         (*Q)->a[j] = q;
//         q = 0;
//     }
//     bi_refine(*Q);

//     bi_delete(&T);
//     bi_delete(&TT);
// }

// // void bi_long_div_bin(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN word B)
// // {
// //     int n = A->wordlen;

// //     bi_set_zero(Q);
// //     bi_set_zero(R);

// //     for (int j = n - 1; j >= 0; j--)
// //     {
// //         bi_lshift(R, 1);
// //         (*R)->a[0] = (*R)->a[0] ^ get_j_bit(A->a[j], j);
// //         if (bi_cmp(*R, B) == 1 and bi_cmp(*R, B) == 0)
// //         {
// //             (*Q)->a[j] = (*Q)->a[j] ^ pow2(j);
// //             bi_SUB(R, *R, B);
// //         }
// //     }
// // }
