#include <stdio.h>

// #include "includes/benchmark.h"
#include "includes/bi_rand.h"
#include "includes/bi.h"
#include "includes/bi_op.h"
#include "includes/bi_test.h"
#include "includes/bi_prime.h"
#include "includes/rsa.h"

int main()
{
    srand((unsigned)time(NULL));

    // 정확성 검증
    // test_ADD(1);
    // test_SUB(1000);
    // test_MUL(1000);
    // test_SQU(1000);
    // test_KMUL(1);
    // test_KSQU(1000);
    // test_DIV(1000);
    // test_long_div_bin(1000);
    // test_exp(10, bi_l2r);
    // test_mod_exp(100, bi_mod_exp_l2r);

    // test_gcd(100, bi_ea_rcs);
    test_gcd(100, bi_ea_bin_itr);
    // test_gcd(100, bi_ea_itr);
    // test_xgcd(100, bi_eea_itr);

    // test_is_prime(1, bi_is_prime);
    // test_prime_gen(1, bi_gen_prime);

    // test_xgcd(100, bi_eea_bin_itr);
    // test_gcd(10000, lehmer_gcd);
    // test_mont_red(1);

    // test_bi_long_div_2word(1000);
    // test_DIVCC(1000);
    // test_DIVC(1000);

    // test_bi_lshift(1000);
    // test_bi_rshift(1000);
    // test_bi_word_rshift(10);
    // test_MUL_AB(1000);
    // test_MULC(1000);
    // test_SQU_A(100);
    // test_SQUC(100);
    // test_MULC_karastuba(100);
    // test_bi_word_reduction(10);

    return 0;
}