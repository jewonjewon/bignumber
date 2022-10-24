#include <stdio.h>
#include <time.h>
#include "../includes/rsa.h"

#define CHECK_TIME(t) (((double)clock()) / (CLOCKS_PER_SEC))

/// @brief Textbook RSA 테스트 코드
/// @param n 키 길이 입력 e.g. RSA-1024 or RSA-2048 ...
void textbook_rsa(int n)
{
    rsa_pub_key pk;
    rsa_pri_key sk;

    init_rsa_key(&pk, &sk);

    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;

    bi_gen_rand(&m, NON_NEGATIVE, 5);

    double start, end;

    start = CHECK_TIME();
    rsa_keygen(&pk, &sk, n);
    end = CHECK_TIME();

    printf("# keygen time: %lf\n", end - start);

    printf("#   rsa-%d Key list\n", n);
    bi_print("p", sk.p);
    bi_print("q", sk.q);
    bi_print("N", pk.N);
    bi_print("e", pk.e);
    bi_print("d", sk.d);

    newline;

    start = CHECK_TIME();
    rsa_enc(&c, m, &pk);
    end = CHECK_TIME();
    printf("# Ciphertext(rsa-%d)\n", n);
    printf("# enc time: %lf\n", end - start);

    bi_print("c", c);

    newline;

    printf("# Ciphertext(rsa-%d)\n", n);

    start = CHECK_TIME();
    rsa_dec(&recoverd_msg, c, &sk);
    end = CHECK_TIME();

    printf("# dec time: %lf\n", end - start);
    printf("# Recovered message(rsa-1024)\n");
    bi_print("# recoverd_msg", recoverd_msg);

    newline;

    if (bi_cmp(m, recoverd_msg) == 0)
        printf("# Success!\n");
    else
        printf("# Fali..\n");

    delete_rsa_key(&pk, &sk);

    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}

/// @brief RSA-CRT 테스트 코드
/// @param n 키 길이 입력 e.g. RSA-CRT-1024 or RSA-CRT-2048 ...
void rsa_crt(IN int n)
{
    rsa_pub_key pk;
    rsa_pri_key sk;

    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;

    init_rsa_crt_key(&pk, &sk);

    rsa_crt_keygen(&pk, &sk, n);

    bi_gen_rand(&m, NON_NEGATIVE, 5);

    printf("#   rsa-crt Key list\n");
    bi_print("p", sk.p);
    newline;
    bi_print("q", sk.q);
    newline;
    bi_print("N", pk.N);
    newline;

    bi_print("e", pk.e);
    newline;
    bi_print("d", sk.d);

    newline;

    rsa_enc(&c, m, &pk);
    printf("# Cipher text(rsa-1024)\n");
    bi_print("c", c);

    newline;

    rsa_crt_dec(&recoverd_msg, c, &sk);
    printf("# Recovered message(rsa-1024)\n");
    bi_print("# recoverd_msg", recoverd_msg);

    newline;

    if (bi_cmp(m, recoverd_msg) == 0)
        printf("# Success!\n");
    else
        printf("# Fali..\n");

    delete_rsa_crt_key(&pk, &sk);

    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}

int main()
{
    double start, end;
    int n = 2048;

    srand((unsigned)time(NULL));

    // start = CHECK_TIME();
    textbook_rsa(n);
    // end = CHECK_TIME();

    // printf("# RSA-%d time: %lf\n", n, (end - start));

    start = CHECK_TIME();
    rsa_crt(n);
    end = CHECK_TIME();

    printf("# RSA-%d time: %lf\n", n, (end - start));
#if 0
    bigint *a = NULL;
    bigint *t = NULL;
    bi_new(&a, 5);
    bi_new(&t, 5);
    int k = 1000000;

#if 1
    start = CHECK_TIME();
    while (k > 0) /* k번 시행 */
    {
        bi_gen_rand(&a, NON_NEGATIVE, t->wordlen);
        k--;
    }
    end = CHECK_TIME();
    printf("rand: %lf\n", end - start);
#endif
#if 1
    start = CHECK_TIME();
    while (k > 0) /* k번 시행 */
    {
        bi_SPDM(&a, t); /* Choose random bit a in [2, a - 2)*/
        k--;
    }
    end = CHECK_TIME();
    printf("SPDM: %lf\n", end - start);
#endif

    bi_delete_2(&a, &t);

#endif
    return 0;
}