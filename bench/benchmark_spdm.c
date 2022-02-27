#include <stdio.h>

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"
#include "bi_prime.h"
#include "bi_rand.h"

void bench_bi_SPDM(IN int TEST, void (*func)(bigint **, bigint *))
{
    bigint *C = NULL;
    bigint *A = NULL;

    int wordlen = 8;

    for (int j = 0; j < TEST; j++)
    {

        bi_gen_rand(&A, NON_NEGATIVE, 8);

        func(&C, A);

        // printf("C = ");
        // bi_print(C);

        // printf("A = ");
        // bi_print(A);

        // printf("if (C >= A):\n");
        // printf("    print(C<A)\n");
    }

    bi_delete(&C);
    bi_delete(&A);
}

void bench_SPDM()
{
    printf("# prime \n");
    int cnt = 1000000; /* cnt: 시행 횟수 */

    double start1, start2, start3, start4;
    double end1, end2, end3, end4;

    start1 = (double)clock() / CLOCKS_PER_SEC;
    bench_bi_SPDM(cnt, bi_SPDM);
    end1 = (((double)clock()) / CLOCKS_PER_SEC);

    // start2 = (double)clock() / CLOCKS_PER_SEC;
    // bench_bi_prime(cnt, bi_is_prime);
    // end2 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("# ===== ===== 측정 결과 ===== =====\n");
    printf("# %.0d번 수행 기준\n\n", cnt);

    printf("%lf \n", (end1 - start1));
    printf("# 1번 함수 1회 수행 시간 :%lf\n", (end1 - start1) / cnt);
    // printf("%lf, \n", (end2 - start2));
    // printf("# 2번 함수 1회 수행 시간 :%lf\n", (end2 - start2) / cnt);
}