#include <stdio.h>

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"
#include "RSA.h"

void bench_RSA()
{
    int n = 1024;
    printf("# RSA %d \n", n);
    int cnt = 20; /* cnt: 시행 횟수 */
    printf("# %.0d번 수행 기준\n\n", cnt);

    double start1, start2, start3, start4;
    double end1, end2, end3, end4;

    RSA_key pk;
    RSA_key sk;

    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;
    bi_new(&m, 1);
    m->a[0] = 0x2000000;

    start1 = (double)clock() / CLOCKS_PER_SEC;
    RSA_keygen(&pk, &sk, n);
    end1 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("# textbook RSA-%d KeyGen 함수 1회 수행 시간 :%lf\n", n, (end1 - start1));

    start2 = (double)clock() / CLOCKS_PER_SEC;
    RSA_crt_keygen(&pk, &sk, n);
    end2 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("# RSA-CRT-%d KeyGen 함수 1회 수행 시간 :%lf\n", n, (end2 - start2));

    start3 = (double)clock() / CLOCKS_PER_SEC;

    for (int j = 0; j < cnt; j++)
    {
        RSA_enc(&c, m, &pk);
        RSA_dec(&recoverd_msg, c, &sk);
    }
    end3 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("%lf \n", (end3 - start3));
    printf("# textbook RSA-%d 1회 수행 시간 :%lf\n", n, (end3 - start3) / cnt);

    start4 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        RSA_enc(&c, m, &pk);
        RSA_crt_dec(&recoverd_msg, c, &sk);
    }
    end4 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("%lf, \n", (end4 - start4));
    printf("# RSA-CRT-%d 1회 수행 시간 :%lf\n", n, (end4 - start4) / cnt);

    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}