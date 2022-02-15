#ifndef __RSA_H__
#define __RSA_H__

#include "bi.h"
#include "bi_op.h"
#include "bi_prime.h"
#include "bi_test.h"
#include "benchmark.h"
#include "bi_rand.h"

typedef struct
{
    bigint *p; /* large prime(p != q) */
    bigint *q; /* large prime(q != p) */
    bigint *N; /* N = p*q */
    bigint *d; /* secret key k */
    bigint *e; /* public key */

    bigint *dp;
    bigint *dq;
    bigint *inv_qp;
} RSA_key;

void bi_euler_phi(bigint **phi_N, bigint *p, bigint *q);

/* Naive RSA */
void RSA_keygen(RSA_key *pk, RSA_key *sk, int n);
void RSA_enc(OUT bigint **c, bigint *m, RSA_key *pk);
void RSA_dec(OUT bigint **m, bigint *c, RSA_key *sk);
void textbook_RSA(int n);

/* RSA-CRT */
void RSA_crt_keygen(RSA_key *pk, RSA_key *sk, int n);
void RSA_crt_dec(OUT bigint **m, bigint *c, RSA_key *sk);
void RSA_crt(int n);

#endif