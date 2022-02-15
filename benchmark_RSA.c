// #include <stdio.h>

// #include "bi.h"
// #include "bi_op.h"
// #include "bi_test.h"

// void bench_RSA(IN int TEST, void (*func)(bigint **, bigint *, bigint *))
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     bigint *C = NULL;

//     for (int j = 0; j < TEST; j++)
//     {
//         int num1 = rand() % 0xf + 1;
//         int num2 = rand() % 0xf + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num2);
//         func(&C, A, B);
//         // bi_ADD(&C, A, B);
//     }

//     bi_delete_3(&C, &A, &B);
// }

// void bench_gcd()
// {
//     printf("# GCD \n");
//     int cnt = 10000; /* cnt: 시행 횟수 */

//     double start1, start2, start3, start4;
//     double end1, end2, end3, end4;

//     start1 = (double)clock() / CLOCKS_PER_SEC;
//     bench_bi_gcd(cnt, bi_ea_itr);
//     end1 = (((double)clock()) / CLOCKS_PER_SEC);

//     start2 = (double)clock() / CLOCKS_PER_SEC;
//     bench_bi_gcd(cnt, bi_ea_rcs);
//     end2 = (((double)clock()) / CLOCKS_PER_SEC);

//     start3 = (double)clock() / CLOCKS_PER_SEC;
//     bench_bi_gcd(cnt, bi_ea_bin_itr);
//     end3 = (((double)clock()) / CLOCKS_PER_SEC);

//     start4 = (double)clock() / CLOCKS_PER_SEC;
//     bench_bi_gcd(cnt, lehmer_gcd);
//     end4 = (((double)clock()) / CLOCKS_PER_SEC);

//     printf("# ===== ===== 측정 결과 ===== =====\n");
//     printf("# %.0d번 수행 기준\n\n", cnt);

//     printf("%lf \n", (end1 - start1));
//     printf("# 1번 함수 1회 수행 시간 :%lf\n", (end1 - start1) / cnt);
//     printf("%lf, \n", (end2 - start2));
//     printf("# 2번 함수 1회 수행 시간 :%lf\n", (end2 - start2) / cnt);
//     printf("%lf, \n", (end3 - start3));
//     printf("# 3번 함수 1회 수행 시간 :%lf\n", (end3 - start3) / cnt);
//     printf("%lf, \n", (end4 - start4));
//     printf("# 4번 함수 1회 수행 시간 :%lf\n", (end4 - start4) / cnt);
// }