#include "bi.h"
#include "bi_op.h"
#include "bi_prime.h"
#include "bi_rand.h"

// #define ADD(c, a, b) ((c), (a), (b))
// #define euler_phi(p, q) ((p - 1) * (q - 1))
typedef struct
{
    bigint *p; /* large prime(p != q) */
    bigint *q; /* large prime(q != p) */
    bigint *N; /* N = p*q */
    bigint *d; /* secret key k */
    bigint *e; /* public key */
} RSA_key;

void bi_euler_phi(bigint **phi_N, bigint *p, bigint *q)
{
    bigint *t0 = NULL;
    bigint *t1 = NULL;
    bi_assign(&t0, p);
    bi_assign(&t1, q);

    bi_sub_minus_a(&t0, 1); /* p -= 1 */
    bi_sub_minus_a(&t1, 1); /* q -= 1 */

    bi_KMUL(phi_N, t0, t1); /* N = (p-1)*(q-1) */

    bi_delete(&t0);
    bi_delete(&t1);
}

// void RSA_keygen(RSA_key **pk, RSA_key **sk)
void RSA_keygen(bigint **p, bigint **q, bigint **N,
                bigint **phi_N, bigint **e, bigint **d)
{
    bigint *T = NULL;

    /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
    bi_gen_prime(p, 512); /* Choose random prime p */
    bi_gen_prime(q, 512); /* Choose random prime q */

    bi_KMUL(N, *p, *q); /* N = pq */

    bi_euler_phi(phi_N, *p, *q); /* Calculate phi(N) = (p-1)*(q-1) */

    /* 4. Calculate e s.t. gcd(e, phi(N)) = 1 */
    while (1)
    {
        do
        {
            bi_SPDM(e, *phi_N);

        } while (bi_is_zero(*e) == true or bi_is_one(*e) == true);

        bi_ea_bin_itr(&T, *e, *phi_N);

        if (bi_is_one(T) == true)
        {
            bi_eea_itr(d, *e, *phi_N); /* Calculate d s.t. ed = 1 (mod phi(N)) */

            if (bi_cmp(*e, *d) != 0)
            {
                bi_delete(&T);
                return;
            }
        }
    }
}

void RSA_crt_keygen(bigint **p, bigint **q, bigint **N, bigint **phi_N,
                    bigint **e, bigint **d, bigint **dp, bigint **dq, bigint **inv_qp)
{
    bigint *T = NULL;

    /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
    bi_gen_prime(p, 512); /* Choose random prime p */
    bi_gen_prime(q, 512); /* Choose random prime q */

    bi_KMUL(N, *p, *q); /* N = pq */

    bi_euler_phi(phi_N, *p, *q); /* Calculate phi(N) = (p-1)*(q-1) */

    /* 4. Calculate e s.t. gcd(e, phi(N)) = 1 */
    while (1)
    {
        do
        {
            bi_SPDM(e, *phi_N);

        } while (bi_is_zero(*e) == true or bi_is_one(*e) == true);

        bi_ea_bin_itr(&T, *e, *phi_N);

        if (bi_is_one(T) == true)
        {
            bi_eea_itr(d, *e, *phi_N); /* Calculate d s.t. ed = 1 (mod phi(N)) */

            if (bi_cmp(*e, *d) != 0)
            {
                bi_delete(&T);
            }
        }
    }

    bigint *pp = NULL; /* pp = p - 1 */
    bigint *qq = NULL; /* qq = q - 1 */

    bi_assign(&pp, *p);
    bi_sub_minus_a(&pp, 1);

    bi_assign(&qq, *q);
    bi_sub_minus_a(&qq, 1);

    bi_div_r(dp, *d, pp); /* dp = d (mod p - 1) */
    bi_div_r(dq, *d, qq); /* dq = d (mod q - 1) */

    bi_eea_itr(inv_qp, *q, *p); /* q*q_p^(-1) = 1 (mod q) */

    bi_delete(&pp);
    bi_delete(&qq);
}

void RSA_crt_dec(OUT bigint **m, bigint *c, bigint *d, bigint *N,
                 bigint *p, bigint *q, bigint *dp, bigint *dq, bigint *inv_qp)
{
    bigint *mp = NULL;
    bigint *mq = NULL;
    bigint *t = NULL;

    bi_mod_mns(&mp, c, dp, p);
    bi_mod_mns(&mp, c, dp, p);

    bi_SUB(&t, mp, mq);
    bi_kmul_asg(&t, q);
    bi_kmul_asg(&t, inv_qp);
    bi_add_asg(&t, mq);
    bi_div_r(m, t, N);

    bi_delete(&t);
    bi_delete(&mp);
    bi_delete(&mq);
}

// void RSA_keygen(RSA_key **pk, RSA_key **sk)
// {
//     bigint *phi_N = NULL; /* phi(N) = (p-1)*(q-1) */
//     bigint *T = NULL;
//     bigint *pp = NULL;
//     // bi_assign(&(*pk)->p, pp);
//     check;
//     // (*pk)->q = NULL;
//     /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
//     bi_gen_prime(&(*pk)->p);
//     bi_gen_prime(&(*pk)->q);
//     /* 2. N = pq */
//     (*pk)->N = NULL;
//     bi_KMUL(&(*pk)->N, (*pk)->p, (*pk)->q);

//     /* 3. Calculate phi(N) = (p-1)*(q-1) */
//     bi_euler_phi(&phi_N, (*pk)->p, (*pk)->q);

//     /* 4. Calculate e s.t. gcd(e, phi(N)) = 1 */
//     while (1)
//     {
//         do
//         {
//             bi_SPDM(&(*pk)->e, phi_N);

//         } while (bi_is_zero((*pk)->e) == true or bi_is_one((*pk)->e) == true);

//         bi_ea_bin_itr(&T, (*pk)->e, phi_N);

//         if (bi_is_one(T) == true)
//         {
//             /* 5. Calculate d s.t. ed = 1 (mod phi(N)) */
//             bi_eea_itr(&(*pk)->d, (*pk)->e, phi_N);

//             if (bi_cmp((*pk)->e, (*pk)->d) != 0)
//             {
//                 bi_delete(&T);
//                 bi_delete(&phi_N);
//                 return;
//             }
//         }
//     }
// }
// void RSA_enc(bigint **c, bigint *m, RSA_key *pk)
void RSA_enc(OUT bigint **c, bigint *m, bigint *e, bigint *N)
{
    bi_mod_l2r(c, m, e, N); /* c = m^e (mod N) */
}

// void RSA_dec(bigint **m, bigint *c, RSA_key *sk)
void RSA_dec(OUT bigint **m, bigint *c, bigint *d, bigint *N)
{
    bi_mod_mns(m, c, d, N); /* m = c^d (mod N) */
}

void textbook_RSA(IN int n)
{
#if n == 1024

#endif
#if n == 2048
#endif
}

void RSA_1024()
{
    bigint *p = NULL; /* large prime(p != q) */
    bigint *q = NULL; /* large prime(q != p) */
    bigint *N = NULL; /* N = p*q */
    bigint *d = NULL; /* secret key k */
    bigint *e = NULL; /* public key */
    bigint *phi_N = NULL;
    bigint *m = NULL;
    bigint *c = NULL;
    bigint *recoverd_msg = NULL;

    RSA_keygen(&p, &q, &N, &phi_N, &e, &d);
    bi_new(&m, 1);
    m->a[0] = 0x200;

    printf("#   RSA-1024 Key list\n");
    printf("p = ");
    bi_print(p);
    printf("q = ");
    bi_print(q);
    printf("N = ");
    bi_print(N);
    printf("phi(N) = ");
    bi_print(phi_N);
    printf("e = ");
    bi_print(e);
    printf("d = ");
    bi_print(d);

    newline;

    RSA_enc(&c, m, e, N);
    printf("Cipher text(RSA-1024)\n");
    bi_print(c);

    newline;

    RSA_dec(&recoverd_msg, c, d, N);
    printf("Recovered message(RSA-1024)\n");
    bi_print(m);

    newline;

    if (bi_cmp(m, recoverd_msg) == 0)
        printf("Success!\n");
    else
        printf("Fali..\n");

    bi_delete(&p);
    bi_delete(&q);
    bi_delete(&N);
    bi_delete(&phi_N);
    bi_delete(&e);
    bi_delete(&d);
    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&recoverd_msg);
}

void RSA_crt_1024()
{
    bigint *p = NULL; /* large prime(p != q) */
    bigint *q = NULL; /* large prime(q != p) */
    bigint *N = NULL; /* N = p*q */
    bigint *d = NULL; /* secret key k */
    bigint *e = NULL; /* public key */
    bigint *phi_N = NULL;
    bigint *m = NULL;
    bigint *c = NULL;
    bigint *dp = NULL;
    bigint *dq = NULL;
    bigint *inv_qp = NULL;
    bigint *recoverd_msg = NULL;

    // RSA_keygen(&p, &q, &N, &phi_N, &e, &d);
    RSA_crt_keygen(&p, &q, &N, &phi_N, &e, &d, &dp, &dq, &inv_qp);
    bi_new(&m, 1);
    m->a[0] = 0x200;

    printf("#   RSA-1024 Key list\n");
    printf("p = ");
    bi_print(p);
    printf("q = ");
    bi_print(q);
    printf("N = ");
    bi_print(N);
    printf("phi(N) = ");
    bi_print(phi_N);
    printf("e = ");
    bi_print(e);
    printf("d = ");
    bi_print(d);

    newline;

    RSA_enc(&c, m, e, N);
    printf("Cipher text(RSA-1024)\n");
    bi_print(c);

    newline;

    RSA_crt_dec(&recoverd_msg, c, d, N, p, q, dp, dq, inv_qp);
    printf("Recovered message(RSA-1024)\n");
    bi_print(m);

    newline;

    if (bi_cmp(m, recoverd_msg) == 0)
        printf("Success!\n");
    else
        printf("Fali..\n");

    bi_delete(&p);
    bi_delete(&q);
    bi_delete(&N);
    bi_delete(&phi_N);
    bi_delete(&e);
    bi_delete(&d);
    bi_delete(&m);
    bi_delete(&c);
    bi_delete(&dp);
    bi_delete(&dq);
    bi_delete(&inv_qp);
    bi_delete(&recoverd_msg);
}