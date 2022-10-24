#include <stdio.h>

#include "includes/benchmark.h"
#include "includes/bi_rand.h"
#include "includes/bi.h"
#include "includes/bi_op.h"
#include "includes/bi_test.h"
#include "includes/bi_prime.h"
#include "includes/RSA.h"

void bench_bi_ADD(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0xf + 1;
        int num2 = rand() % 0xf + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_add(&C, A, B);
    }

    bi_delete_3(&C, &A, &B);
}

void bench_ADD()
{
    printf("# ADD \n");
    int cnt = 10000000; /* cnt: 시행 횟수 */

    double start1;
    // double start1, start2;
    double end1;
    // double end1, end2;

    start1 = (double)clock() / CLOCKS_PER_SEC;
    bench_bi_ADD(cnt);
    end1 = (((double)clock()) / CLOCKS_PER_SEC);
    // start2 = (double)clock() / CLOCKS_PER_SEC;
    // bench_bi_KMUL(cnt, j);
    // end2 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("# ===== ===== 측정 결과 ===== =====\n");
    printf("# %.0d번 수행 기준\n\n", cnt);

    printf("%lf \n", (end1 - start1));
    printf("# 1번 함수 1회 수행 시간 :%lf\n", (end1 - start1) / cnt);
    // printf("%lf, ", (end2 - start2));
    // printf("# 2번 함수 1회 수행 시간 :%lf\n", (end2 - start2) / cnt);
}