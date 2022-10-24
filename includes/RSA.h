#ifndef __rsa_H__
#define __rsa_H__

#include "bi.h"
#include "bi_op.h"
#include "bi_rand.h"

typedef struct
{
    bigint *N; /* N = p*q */
    bigint *e; /* public key */
} rsa_pub_key;

typedef struct
{
    bigint *p; /* large prime(p != q) */
    bigint *q; /* large prime(q != p) */
    bigint *N; /* N = p*q */
    bigint *d; /* secret key k */

    bigint *dp;
    bigint *dq;
    bigint *inv_qp;
} rsa_pri_key;

void bi_euler_phi(bigint **phi_N, bigint *p, bigint *q);

/* Textbook RSA */
void init_rsa_key(rsa_pub_key *pk, rsa_pri_key *sk);
void delete_rsa_key(rsa_pub_key *pk, rsa_pri_key *sk);

void rsa_keygen(rsa_pub_key *pk, rsa_pri_key *sk, int n);
void rsa_enc(OUT bigint **c, bigint *m, rsa_pub_key *pk);
void rsa_dec(OUT bigint **m, bigint *c, rsa_pri_key *sk);

/* RSA-CRT */
void init_rsa_crt_key(rsa_pub_key *pk, rsa_pri_key *sk);
void delete_rsa_crt_key(rsa_pub_key *pk, rsa_pri_key *sk);
void rsa_crt_keygen(rsa_pub_key *pk, rsa_pri_key *sk, int n);
void rsa_crt_dec(OUT bigint **m, IN bigint *c, IN rsa_pri_key *sk);
void rsa_crt(int n);

#endif