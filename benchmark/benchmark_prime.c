#include <stdio.h>

// #include "bi.h"
// #include "bi_op.h"
// #include "bi_test.h"
// #include "bi_prime.h"
// #include "bi_rand.h"

#include "includes/benchmark.h"
#include "includes/bi_rand.h"
#include "includes/bi.h"
#include "includes/bi_op.h"
#include "includes/bi_test.h"
#include "includes/bi_prime.h"
#include "includes/RSA.h"

void bench_bi_prime(IN int TEST, void (*func)(bigint **n, int k))
{
    // int k = 40; /* 시행횟수 */
    // int x = 0;

    bigint *n = NULL;

    for (int j = 0; j < TEST; j++)
    {
        func(&n, 512);
        bi_print("n", n);
    }

    bi_delete(&n);
}
// void bi_gen_prime(bigint **p, int bitlen)

void bench_prime()
{
    printf("# prime \n");
    int cnt = 100; /* cnt: 시행 횟수 */

    double start1;
    // double start1, start2, start3, start4;
    double end1;
    // double end1, end2, end3, end4;

    start1 = (double)clock() / CLOCKS_PER_SEC;
    bench_bi_prime(cnt, bi_gen_prime);
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