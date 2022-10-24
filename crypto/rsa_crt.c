#include "../includes/rsa.h"

/// @brief RSA-CRT 키 초기화
/// @param pk RSA 공개키
/// @param sk RSA 개인키
void init_rsa_crt_key(rsa_pub_key *pk, rsa_pri_key *sk)
{
    sk->p = NULL;
    sk->q = NULL;
    sk->d = NULL;
    sk->N = NULL;
    sk->dp = NULL;
    sk->dq = NULL;
    sk->inv_qp = NULL;

    pk->N = NULL;
    pk->e = NULL;
}

/// @brief RSA-CRT 키 메모리 해제
/// @param pk RSA 공개키
/// @param sk RSA 개인키
void delete_rsa_crt_key(rsa_pub_key *pk, rsa_pri_key *sk)
{
    bi_delete(&sk->p);
    bi_delete(&sk->q);
    bi_delete(&sk->N);
    bi_delete(&sk->d);
    bi_delete(&sk->dp);
    bi_delete(&sk->dq);
    bi_delete(&sk->inv_qp);

    bi_delete(&pk->N);
    bi_delete(&pk->e);
}

/// @brief RSA-CRT 키 생성 함수
/// @param pk (output) 공개키
/// @param sk (output) 개인키
/// @param n (input)규격 설정 파라미터
void rsa_crt_keygen(rsa_pub_key *pk, rsa_pri_key *sk, int n)
{
    bigint *T = NULL;
    bigint *phi_N = NULL; /* phi_N = (p-1)*(q-1) */

    n >>= 1;

    /* 1. 512비트 크기의 서로 다른 두 소수 생성 */
    bi_gen_prime(&sk->p, n); /* Choose random prime p */
    bi_gen_prime(&sk->q, n); /* Choose random prime q */

    /* 2. Calculate N <- p*q */
    bi_kmul(&pk->N, sk->p, sk->q); /* N = pq */
    bi_assign(&sk->N, pk->N);

    /* 3. Calculate phi(N) = (p-1)*(q-1) */
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
            /* 5. Calculate d s.t. ed = 1 (mod phi(N)) */
            bi_eea_itr(&sk->d, pk->e, phi_N);

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
    bi_subi(&pp, 1);

    bi_assign(&qq, sk->q);
    bi_subi(&qq, 1);

    bi_div_r(&sk->dp, sk->d, pp); /* dp = d (mod p - 1) */
    bi_div_r(&sk->dq, sk->d, qq); /* dq = d (mod q - 1) */

    bi_eea_itr(&sk->inv_qp, sk->p, sk->q); /* q*q_p^(-1) = 1 (mod q) */

    bi_delete(&pp);
    bi_delete(&qq);
}

void rsa_crt_dec(OUT bigint **m, IN bigint *c, IN rsa_pri_key *sk)
{
    bigint *mp = NULL;
    bigint *mq = NULL;
    bigint *t = NULL;

    bi_mod_exp_mns(&mp, c, sk->dp, sk->p);
    bi_mod_exp_mns(&mq, c, sk->dq, sk->q);

    bi_sub(&t, mp, mq);
    bi_kmul_asg(&t, sk->q);
    bi_kmul_asg(&t, sk->inv_qp);
    bi_add_asg(&t, mq);
    bi_div_r(m, t, sk->N);

    bi_delete(&t);
    bi_delete(&mp);
    bi_delete(&mq);
}
