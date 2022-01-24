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

// int bi_is_negative(bigint *A)
// {
//     if (A->sign == NEGATIVE)
//         return 1;
//     else
//         return 0;
// }

// word bi_long_div_2word(IN bigint *A, IN word B)
// {
//     printf("\n# bi_long_div_2word\n");
//     newline;

//     if (A->a[1] >= B)
//         printf("# long_div_2word A1 ≥ B, 조건 성립 x\n");

//     word Q = 0;
//     word R = A->a[1];
//     for (int j = w - 1; j >= 0; j--)
//     {
//         if (R >= pow2(w - 1))
//         {
//             Q = Q + pow2(j);
//             // printf("#%d-th Q = %#x\n", j, Q);
//             R = (R << 1) + get_j_bit(A->a[0], j) - B;
//             // printf("#%d-th R = %#x\n", j, R);
//         }
//         else
//         {

//             R = (R << 1) + get_j_bit(A->a[0], j);
//             if (R >= B)
//             {
//                 Q = Q + pow2(j);
//                 // printf("#%d-th Q = %#x\n", j, Q);
//                 R = R - B;
//                 // printf("#%d-th R = %#x\n", j, R);
//             }
//         }
//     }
//     return Q;
// }

// void bi_DIVCC(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     printf("\n# bi_DIVCC\n");
//     newline;
//     // printf("if B_(m-1) ≥ 2^(w-1)?\n");
//     // printf("%x >= %x?\n", B->a[B->wordlen - 1], pow2(w - 1));
//     // if (B->a[B->wordlen - 1] >= pow2(w - 1))
//     //     printf("true!\n");
//     // else
//     //     printf("false\n");

//     int n = A->wordlen;
//     int m = B->wordlen;

//     // printf("# wordlen(A) = %d, wordlen(B) = %d\n", n, m);

//     // printf("A = ");
//     // bi_print(A);

//     // printf("B = ");
//     // bi_print(B);

//     word q;

//     if (n == m)
//         q = A->a[m - 1] / B->a[m - 1];

//     if (n == m + 1)
//     {
//         if (A->a[m] == B->a[m - 1])
//         {
//             q = W;
//             // printf("1. q = %x\n", q);
//         }
//         else
//         {
//             bigint *T = NULL;
//             bi_new(&T, 2);

//             T->a[1] = A->a[m];
//             T->a[0] = A->a[m - 1];
//             // bi_print(T);
//             // printf("%#x\n", B->a[m - 1]);

//             q = bi_long_div_2word(T, B->a[m - 1]);
//             // printf("2. q = %x\n", q);
//             bi_delete(&T);
//         }
//     }

//     bi_new(Q, 1);
//     (*Q)->a[0] = q;
//     bigint *T = NULL;

//     bi_MULC(&T, B, *Q);
//     bi_SUB(R, A, T);
//     int cnt = 0;

//     while ((*R)->sign == NEGATIVE)
//     {
//         (*Q)->a[0]--;
//         bi_ADDC(R, *R, B);
//         // printf("# R' = ");
//         // bi_print(*R);
//         // check;
//         cnt++;
//     }

//     printf("DIVCC while문 반복횟수: %d\n", cnt);

//     bi_delete(&T);
// }

// // void bi_DIVC(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// // {
// //     printf("\n# bi_DIVC\n");
// //     newline;

// //     if (bi_cmp(A, B) == -1)
// //     {
// //         bi_set_zero(Q);
// //         bi_assign(R, A);
// //         return;
// //     }

// //     bigint *QQ = NULL;
// //     bigint *RR = NULL;
// //     bigint *AA = NULL;
// //     bigint *BB = NULL;
// //     int k = 0;

// //     // word t = B->a[B->wordlen - 1];
// //     int bitlen_b = bitlen(B->a[B->wordlen - 1]);
// //     printf("#B_(m-1) = %#x\n", B->a[B->wordlen - 1]);
// //     printf("#bitlen_b = %d\n", bitlen_b);

// //     k = w - bitlen_b;

// //     printf("#k = %d\n", k);
// //     bi_assign(&AA, A);
// //     bi_assign(&BB, B);
// //     bi_lshift(&AA, pow2(k));
// //     bi_lshift(&BB, pow2(k));

// //     bi_DIVCC(&QQ, &RR, AA, BB);

// //     bi_assign(Q, QQ);
// //     bi_rshift(&RR, pow2(k));
// //     bi_assign(R, RR);

// //     bi_delete(&QQ);
// //     bi_delete(&RR);
// //     bi_delete(&AA);
// //     bi_delete(&BB);
// // }

// void bi_DIVC(OUT word *word_Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     printf("\n# bi_DIVC\n");
//     newline;

//     if (bi_cmp(A, B) == -1)
//     {
//         printf("# bi_DIVC if 문\n");
//         *word_Q = 0;
//         bi_assign(R, A);

//         printf("R = ");
//         bi_print(*R);
//         return;
//     }

//     bigint *QQ = NULL;
//     bigint *RR = NULL;
//     bigint *AA = NULL;
//     bigint *BB = NULL;

//     int k = 0;
//     // printf("!!!! B = ");
//     // bi_print(B);
//     int bitlen_b = bitlen(B->a[B->wordlen - 1]);

//     k = w - bitlen_b;
//     // printf("k = %d\n", k);

//     // printf("#k = %d\n", k);

//     bi_assign(&AA, A);
//     bi_assign(&BB, B);

//     // printf("AA = ");
//     // bi_print(AA);
//     // printf("BB = ");
//     // bi_print(BB);

//     if (k >= 1)
//     {
//         bi_lshift(&AA, pow2(k - 1));
//         bi_lshift(&BB, pow2(k - 1));
//     }

//     // printf("AA = ");
//     // bi_print(AA);
//     // printf("BB = ");
//     // bi_print(BB);

//     bi_DIVCC(&QQ, &RR, AA, BB);

//     // bi_assign(Q, QQ);
//     *word_Q = QQ->a[0];

//     if (k >= 1)
//         bi_rshift(&RR, pow2(k));

//     bi_rshift(&RR, pow2(k));
//     bi_assign(R, RR);

//     bi_delete(&QQ);
//     bi_delete(&RR);
//     bi_delete(&AA);
//     bi_delete(&BB);
// }

// void bi_DIV(OUT bigint **Q, OUT bigint **R, IN bigint *A, IN bigint *B)
// {
//     word word_Q = 0;
//     int n = A->wordlen;

//     if (bi_cmp(A, B) == -1)
//     {
//         bi_set_zero(Q);
//         bi_assign(R, A);
//         return;
//     }

//     bigint *T = NULL;
//     bi_set_zero(&T);

//     bi_set_zero(R);
//     bi_new(Q, n);

//     for (int j = n - 1; j >= 0; j--)
//     {
//         printf("bi_DIV for-loop\n");
//         bi_word_lshift(&T, 1);
//         T->a[0] = A->a[j];
//         bi_refine(T);

//         printf("1. R = ");
//         bi_print(T);

//         printf("wordlen(R) = %d\n", T->wordlen);

//         bi_DIVC(&word_Q, R, T, B);
//         if (bi_cmp(*R, B) == -1)
//             printf("R < B\n");
//         else
//             printf("R ≥ B\n");

//         printf("R = ");
//         bi_print(T);

//         (*Q)->a[j] = word_Q;
//         word_Q = 0;
//     }
//     bi_refine(*Q);
//     bi_delete(&T);
// }
