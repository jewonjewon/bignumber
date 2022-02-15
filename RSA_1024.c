#include "bi.h"
#include "bi_op.h"
#include "bi_prime.h"
#include "bi_rand.h"
#include "RSA.h"

void bi_euler_phi(bigint **phi_N, bigint *p, bigint *q)
{
    bigint *t0 = NULL;
    bigint *t1 = NULL;

    bi_assign(&t0, p);
    bi_assign(&t1, q);

    bi_sub_minus_a(&t0, 1); /* p -= 1 */
    bi_sub_minus_a(&t1, 1); /* q -= 1 */

    /* p와 q는 소수이므로 phi_N = (p-1)(q-1) */
    bi_KMUL(phi_N, t0, t1); /* N = (p-1)*(q-1) */

    bi_delete(&t0);
    bi_delete(&t1);
}

// void RSA_keygen(RSA_key **pk, RSA_key **sk)
void RSA_keygen(RSA_key *pk, RSA_key *sk, int n)
{
    bigint *T = NULL;
    bigint *phi_N = NULL; /* phi_N = (p-1)*(q-1) */

    sk->p = NULL;
    sk->q = NULL;
    sk->d = NULL;
    sk->N = NULL;

    pk->N = NULL;
    pk->e = NULL;

    /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
    bi_gen_prime(&sk->p, n / 2); /* Choose random prime p */
    bi_gen_prime(&sk->q, n / 2); /* Choose random prime q */

    bi_KMUL(&pk->N, sk->p, sk->q); /* N = pq */
    bi_assign(&sk->N, pk->N);

    bi_euler_phi(&phi_N, sk->p, sk->q); /* Calculate phi(N) = (p-1)*(q-1) */

    /* 4. Calculate e s.t. gcd(e, phi(N)) = 1 */
    while (1)
    {
        do
        {
            bi_SPDM(&pk->e, phi_N);

        } while (bi_is_zero(pk->e) == true or bi_is_one(pk->e) == true);

        bi_ea_bin_itr(&T, pk->e, phi_N);

        if (bi_is_one(T) == true)
        {
            bi_eea_itr(&sk->d, pk->e, phi_N); /* Calculate d s.t. ed = 1 (mod phi(N)) */

            if (bi_cmp(pk->e, sk->d) != 0) /* e와 d가 같을 경우 재수행 */
            {
                if (sk->d->sign == NEGATIVE)
                    bi_add_asg(&sk->d, phi_N);

                bi_delete(&T);
                bi_delete(&phi_N);
                return;
            }
        }
    }
}

void RSA_crt_keygen(RSA_key *pk, RSA_key *sk, int n)
{

    bigint *T = NULL;
    bigint *phi_N = NULL; /* phi_N = (p-1)*(q-1) */

    sk->p = NULL;
    sk->q = NULL;
    sk->d = NULL;
    sk->N = NULL;
    sk->dp = NULL;
    sk->dq = NULL;
    sk->inv_qp = NULL;

    pk->N = NULL;
    pk->e = NULL;

    /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
    bi_gen_prime(&sk->p, n / 2);   /* Choose random prime p */
    bi_gen_prime(&sk->q, n / 2);   /* Choose random prime q */
    bi_KMUL(&pk->N, sk->p, sk->q); /* N = pq */
    bi_assign(&sk->N, pk->N);

    bi_euler_phi(&phi_N, sk->p, sk->q); /* Calculate phi(N) = (p-1)*(q-1) */

    /* 4. Calculate e s.t. gcd(e, phi(N)) = 1 */
    while (1)
    {
        do
        {
            bi_SPDM(&pk->e, phi_N);

        } while (bi_is_zero(pk->e) == true or bi_is_one(pk->e) == true);

        bi_ea_bin_itr(&T, pk->e, phi_N);

        if (bi_is_one(T) == true)
        {
            bi_eea_itr(&sk->d, pk->e, phi_N); /* Calculate d s.t. ed = 1 (mod phi(N)) */

            if (bi_cmp(pk->e, sk->d) != 0)
            {
                if (sk->d->sign == NEGATIVE)
                    bi_add_asg(&sk->d, phi_N);
                bi_delete(&T);
                bi_delete(&phi_N);
                break;
            }
        }
    }

    bigint *pp = NULL; /* pp = p - 1 */
    bigint *qq = NULL; /* qq = q - 1 */
    bi_assign(&pp, sk->p);
    bi_sub_minus_a(&pp, 1);

    bi_assign(&qq, sk->q);
    bi_sub_minus_a(&qq, 1);

    bi_div_r(&sk->dp, sk->d, pp); /* dp = d (mod p - 1) */
    bi_div_r(&sk->dq, sk->d, qq); /* dq = d (mod q - 1) */

    bi_eea_itr(&sk->inv_qp, sk->p, sk->q); /* q*q_p^(-1) = 1 (mod q) */

    bi_delete(&pp);
    bi_delete(&qq);
}

void RSA_crt_dec(OUT bigint **m, bigint *c, RSA_key *sk)
{
    bigint *mp = NULL;
    bigint *mq = NULL;
    bigint *t = NULL;

    bi_mod_exp_mns(&mp, c, sk->dp, sk->p);
    bi_mod_exp_mns(&mq, c, sk->dq, sk->q);

    bi_SUB(&t, mp, mq);
    bi_kmul_asg(&t, sk->q);
    bi_kmul_asg(&t, sk->inv_qp);
    bi_add_asg(&t, mq);
    bi_div_r(m, t, sk->N);

    bi_delete(&t);
    bi_delete(&mp);
    bi_delete(&mq);
}

// void RSA_enc(bigint **c, bigint *m, RSA_key *pk)
void RSA_enc(OUT bigint **c, bigint *m, RSA_key *pk)
{
    bi_mod_exp_l2r(c, m, pk->e, pk->N); /* c = m^e (mod N) */
}

// void RSA_dec(bigint **m, bigint *c, RSA_key *sk)
void RSA_dec(OUT bigint **m, bigint *c, RSA_key *sk)
{
    bi_mod_exp_mns(m, c, sk->d, sk->N); /* m = c^d (mod N) */
}

void textbook_RSA(int n)
{
    RSA_key pk;
    RSA_key sk;

    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;

    // bi_new(&m, 1);
    // m->a[0] = 0x200;

    bi_gen_rand(&m, NON_NEGATIVE, 5);

    RSA_keygen(&pk, &sk, n);

    printf("#   RSA-1024 Key list\n");
    printf("p = ");
    bi_print(sk.p);
    newline;
    printf("q = ");
    bi_print(sk.q);
    newline;
    printf("N = ");
    bi_print(pk.N);
    newline;

    printf("e = ");
    bi_print(pk.e);
    newline;
    printf("d = ");
    bi_print(sk.d);

    newline;

    RSA_enc(&c, m, &pk);
    printf("Cipher text(RSA-1024)\n");
    bi_print(c);

    newline;

    RSA_dec(&recoverd_msg, c, &sk);
    printf("Recovered message(RSA-1024)\n");
    bi_print(recoverd_msg);

    newline;

    if (bi_cmp(m, recoverd_msg) == 0)
        printf("Success!\n");
    else
        printf("Fali..\n");

    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}

void RSA_crt(int n)
{
    RSA_key pk;
    RSA_key sk;

    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;

    RSA_crt_keygen(&pk, &sk, n);
    bi_new(&m, 1);
    m->a[0] = 0x2000000;

    printf("#   RSA-crt Key list\n");
    printf("p = ");
    bi_print(sk.p);
    newline;
    printf("q = ");
    bi_print(sk.q);
    newline;
    printf("N = ");
    bi_print(pk.N);
    newline;
    // printf("phi(N) = ");
    // bi_print(sk.phi_N);
    printf("e = ");
    bi_print(pk.e);
    newline;
    printf("d = ");
    bi_print(sk.d);

    newline;

    RSA_enc(&c, m, &pk);
    printf("Cipher text(RSA-1024)\n");
    bi_print(c);

    newline;

    RSA_crt_dec(&recoverd_msg, c, &sk);
    printf("Recovered message(RSA-1024)\n");
    bi_print(recoverd_msg);

    newline;

    if (bi_cmp(m, recoverd_msg) == 0)
        printf("Success!\n");
    else
        printf("Fali..\n");

    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}