#include "../includes/rsa.h"
#define DEMO 1

/// @brief RSA 키 초기화
/// @param pk RSA 공개키
/// @param sk RSA 개인키
void init_rsa_key(rsa_pub_key *pk, rsa_pri_key *sk)
{
    pk->e = NULL;
    pk->N = NULL;

    sk->N = NULL;
    sk->d = NULL;
    sk->p = NULL;
    sk->q = NULL;
}
/// @brief RSA 키 메모리 해제
/// @param pk RSA 공개키
/// @param sk RSA 개인키
void delete_rsa_key(rsa_pub_key *pk, rsa_pri_key *sk)
{
    bi_delete(&sk->p);
    bi_delete(&sk->q);
    bi_delete(&sk->d);
    bi_delete(&sk->N);
    bi_delete(&pk->N);
    bi_delete(&pk->e);
}

/// @brief 오일러 파이 연산 함수(bigint Ver.)
/// @param phi_N phi(N) <- (p-1)(q-1)
/// @param p 임의의 소수
/// @param q 임의의 소수
void bi_euler_phi(bigint **phi_N, bigint *p, bigint *q)
{
    bigint *t0 = NULL;
    bigint *t1 = NULL;

    bi_assign(&t0, p);
    bi_assign(&t1, q);

    bi_subi(&t0, 1); /* p -= 1 */
    bi_subi(&t1, 1); /* q -= 1 */

    /* p와 q는 소수이므로 phi_N = (p-1)(q-1) */
    bi_kmul(phi_N, t0, t1); /* N = (p-1)*(q-1) */

    bi_delete(&t0);
    bi_delete(&t1);
}

/// @brief Textbook-RSA 키 생성 함수
/// @param pk (output) 공개키
/// @param sk (output)개인키
/// @param n (input)규격 설정 파라미터
void rsa_keygen(rsa_pub_key *pk, rsa_pri_key *sk, int n)
{
    bigint *T = NULL;
    bigint *phi_N = NULL; /* phi_N = (p-1)*(q-1) */

    n >>= 1;

/* 1. Generate n/2-bit distinct prime p and q */
#if DEMO
    printf("# finding prime...\n");
#endif
    bi_gen_prime(&sk->p, n); /* Choose random prime p */
    bi_gen_prime(&sk->q, n); /* Choose random prime q */
    /* 2. Calculate N <- p*q */
    bi_kmul(&pk->N, sk->p, sk->q); /* N = pq */
    bi_assign(&sk->N, pk->N);

    /* 3. Calculate phi(N) = (p-1)*(q-1) */
    bi_euler_phi(&phi_N, sk->p, sk->q);

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
            /* 5. Calculate d s.t. ed = 1 (mod phi(N)) */
            bi_eea_itr(&sk->d, pk->e, phi_N);

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

/// @brief Textbook-RSA 암호 연산
/// @param c (output) 암호문
/// @param m (input) 메시지
/// @param pk (input)공개키
void rsa_enc(OUT bigint **c, bigint *m, rsa_pub_key *pk)
{
    bi_mod_exp_l2r(c, m, pk->e, pk->N); /* c = m^e (mod N) */
}

/// @brief Textbook-RSA 복호 연산
/// @param m (output) 복원된 평문
/// @param c (input) 암호문
/// @param sk (input) 개인키
void rsa_dec(OUT bigint **m, bigint *c, rsa_pri_key *sk)
{
    bi_mod_exp_mns(m, c, sk->d, sk->N); /* m = c^d (mod N) */
}
