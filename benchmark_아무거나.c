#include <stdio.h>

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"

// void bench_bi_DIV(IN int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     bigint *Q = NULL;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {

//         int num1 = rand() % 0x0f + 1;
//         int num2 = rand() % 0x0f + 1;

//         while (1)
//         {
//             num1 = rand() % 0x0f + 1;
//             num2 = rand() % 0x0f + 1;

//             if (num1 >= num2)
//             {
//                 bi_gen_rand(&A, NON_NEGATIVE, num1);
//                 bi_gen_rand(&B, NON_NEGATIVE, num2);
//                 if (bi_is_zero(B) == true)
//                     continue;
//                 break;
//             }
//         }

//         bi_DIV(&Q, &R, A, B);
//     }

//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&Q);
//     bi_delete(&R);
// }

// // 워드길이별 카라추바와 스쿨북 비교 (1워드 ~  64워드)
// void bench_bi_long_div_bin(IN int TEST)
// {

//     bigint *A = NULL;
//     bigint *B = NULL;
//     bigint *Q = NULL;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {

//         int num1 = rand() % 0x0f + 1;
//         int num2 = rand() % 0x0f + 1;

//         while (1)
//         {
//             num1 = rand() % 0x0f + 1;
//             num2 = rand() % 0x0f + 1;

//             if (num1 >= num2)
//             {
//                 bi_gen_rand(&A, NON_NEGATIVE, num1);
//                 bi_gen_rand(&B, NON_NEGATIVE, num2);
//                 if (bi_is_zero(B) == true)
//                     continue;
//                 break;
//             }
//         }

//         bi_long_div_bin(&Q, &R, A, B);
//     }

//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&Q);
//     bi_delete(&R);
// }

void bench_lshift()
{
    printf("# DIV v.s. Binary Long Division \n");
    // cnt = 시행 횟수
    int cnt = 100000000;
    bigint *A = NULL;

    int num1 = rand() % 0x0f + 1;
    bi_gen_rand(&A, NON_NEGATIVE, num1);

    double start1, start2;
    double end1, end2;
    int j = 0;
    bigint *T = NULL;

    start1 = (double)clock() / CLOCKS_PER_SEC;
    {
        bi_assign(&T, A);
        bi_lshift(&T, 1);
    }
    end1 = (((double)clock()) / CLOCKS_PER_SEC);
    // bi_set_zero(&T);
    // start2 = (double)clock() / CLOCKS_PER_SEC;
    // for (int j = 0; j < cnt; j++)
    // {
    //     bi_assign(&T, A);
    //     bi_lshift(&T, 1);
    // }
    // end2 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("# ===== ===== 측정 결과 ===== =====\n");
    // printf("# %.0d번 수행 기준\n\n", cnt);

    printf("%lf\n ", (end1 - start1));
    printf("# 1번 함수 1회 수행 시간 :%lf\n", (end1 - start1) / cnt);
    // printf("%lf\n ", (end2 - start2));
    // printf("# 2번 함수 1회 수행 시간 :%lf\n", (end2 - start2) / cnt);
    printf("A = ");
    bi_print(A);
    bi_delete(&A);
}