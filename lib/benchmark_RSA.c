#include <stdio.h>

#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/bi_prime.h"
#include "../includes/bi_rand.h"
#include "../includes/RSA.h"
#include "../includes/bi_test.h"

// void TIME_MSRMN(void (*func)(RSA_key, RSA_key, int))
// {
//     double start, end;

//     start = (double)clock() / CLOCKS_PER_SEC;
//     func();
//     end = (((double)clock()) / CLOCKS_PER_SEC);

//     printf("# textbook RSA KeyGen 함수 1회 수행 시간 :%lf\n", (end - start));
// }

void bench_RSA()
{
    int n = 2048;
    printf("# RSA %d \n", n);
    int cnt = 10; /* cnt: 시행 횟수 */
    // printf("# %.0d번 수행 기준\n\n", cnt);

    double start1, start2, start3, start4;
    double end1, end2, end3, end4;

    double start5, start6;
    double end5, end6;

    RSA_key pk;
    RSA_key sk;

    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;

    bi_gen_rand(&m, NON_NEGATIVE, 10);

    // void (*func)(RSA_key, RSA_key, int);
    // func = RSA_keygen(&pk, &sk, n);

    start1 = (double)clock() / CLOCKS_PER_SEC;
    RSA_keygen(&pk, &sk, n);
    end1 = (((double)clock()) / CLOCKS_PER_SEC);

    // TIME_MSRMN(func);

    printf("# textbook RSA-%d KeyGen 함수 1회 수행 시간 :%lf\n", n, (end1 - start1));

    start2 = (double)clock() / CLOCKS_PER_SEC;
    RSA_crt_keygen(&pk, &sk, n);
    end2 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("# RSA-CRT-%d KeyGen 함수 1회 수행 시간 :%lf\n", n, (end2 - start2));
#if 1
    start3 = (double)clock() / CLOCKS_PER_SEC;

    for (int j = 0; j < cnt; j++)
    {
        RSA_enc(&c, m, &pk);
    }
    end3 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("%lf \n", (end3 - start3));
    printf("# textbook RSA-%d 1회 수행 시간(enc) :%lf\n", n, (end3 - start3) / cnt);

    start4 = (double)clock() / CLOCKS_PER_SEC;

    for (int j = 0; j < cnt; j++)
    {
        RSA_dec(&recoverd_msg, c, &sk);
    }
    end4 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("%lf \n", (end4 - start4));
    printf("# textbook RSA-%d 1회 수행 시간(dec) :%lf\n", n, (end4 - start4) / cnt);
#endif

    start5 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        RSA_enc(&c, m, &pk);
    }
    end5 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("%lf, \n", (end5 - start5));
    printf("# RSA-CRT-%d 1회 수행 시간(enc) :%lf\n", n, (end5 - start5) / cnt);

    start6 = (double)clock() / CLOCKS_PER_SEC;
    for (int j = 0; j < cnt; j++)
    {
        RSA_crt_dec(&recoverd_msg, c, &sk);
    }
    end6 = (((double)clock()) / CLOCKS_PER_SEC);

    printf("%lf, \n", (end6 - start6));
    printf("# RSA-CRT-%d 1회 수행 시간(dec) :%lf\n", n, (end6 - start6) / cnt);

    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}
