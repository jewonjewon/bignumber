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

void RSA_keygen(RSA_key **pk, RSA_key **sk)
{
    bigint *phi_N = NULL; /* phi(N) = (p-1)*(q-1) */

    bigint *T = NULL;
    bigint *pp = NULL;
    bigint *qq = NULL;
    bigint *NN = NULL;
    bigint *ee = NULL;
    bigint *dd = NULL;

    /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
    bi_gen_prime(&pp, 512); /* Choose random prime p */

    // printf("p = ");
    // bi_print(pp);

    bi_gen_prime(&qq, 512); /* Choose random prime q */

    // printf("q = ");
    // bi_print(qq);

    bi_KMUL(&NN, pp, qq); /* N = pq */

    // printf("N = ");
    // bi_print(NN);

    bi_euler_phi(&phi_N, pp, qq); /* Calculate phi(N) = (p-1)*(q-1) */

    // printf("phi(N) = ");
    // bi_print(phi_N);

    /* 4. Calculate e s.t. gcd(e, phi(N)) = 1 */
    while (1)
    {
        do
        {
            bi_SPDM(&ee, phi_N);
            printf("ee = ");
            bi_print(ee);
            if (ee->a[0] == 0 and ee->a[1] == 0 and ee->a[2] == 0)
                return;

        } while (bi_is_zero(ee) == true or bi_is_one(ee) == true);

        bi_ea_bin_itr(&T, ee, phi_N);

        if (bi_is_one(T) == true)
        {
            bi_eea_itr(&dd, ee, phi_N); /* Calculate d s.t. ed = 1 (mod phi(N)) */

            if (bi_cmp(ee, dd) != 0)
            {
                printf("#   RSA-1024 Key list\n");
                printf("p = ");
                bi_print(pp);
                printf("q = ");
                bi_print(qq);

                newline;

                printf("N = ");
                bi_print(NN);
                printf("phi(N) = ");
                bi_print(phi_N);

                newline;

                printf("e = ");
                bi_print(ee);
                printf("d = ");
                bi_print(dd);

                bi_delete(&T);
                bi_delete(&phi_N);

                return;
            }
        }
    }
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

void RSA_enc(bigint **c, bigint *m, RSA_key *pk)
{
    bi_mod_l2r(c, m, pk->e, pk->N); /* c = m^e (mod N) */
}

void RSA_dec(bigint **m, bigint *c, RSA_key *sk)
{
    bi_mod_mns(m, c, sk->d, sk->N); /* m = c^d (mod N) */
}

void RSA_1024()
{
}