#include <stdio.h>

#include "includes/bi.h"
#include "includes/bi_op.h"
#include "includes/bi_prime.h"
#include "includes/bi_rand.h"
#include "includes/RSA.h"
#include "includes/bi_test.h"

int main()
{
    srand((unsigned)time(NULL));

#if 1 // 정확성 검증
    test_ADD(100);
    // test_SUB(100);
    // test_MUL(100);
    // test_SQU(100);
    // test_KMUL(100);
    // test_KSQU(100);
    // test_DIV(100);
    // test_long_div_bin(100);
    // test_exp(10, bi_l2r);
    // test_mod_exp(100, bi_mod_exp_l2r);

    // test_gcd(2, bi_ea_rcs);
    // test_gcd(2, bi_ea_bin_itr);
    // test_gcd(2, bi_ea_itr);
    // test_xgcd(2, bi_eea_itr);

    // test_is_prime(1, bi_is_prime);
    // test_prime_gen(1, bi_gen_prime);

#endif
    // test_xgcd(100, bi_eea_bin_itr);
    // test_gcd(10000, lehmer_gcd);
    // test_mont_red(1);

    // test_bi_long_div_2word(1000);
    // test_DIVCC(1000);
    // test_DIVC(1000);

    // test_bi_lshift(1000);
    // test_bi_rshift(1000);
    // test_bi_word_rshift(10);
    // test_bi_word_reduction(1);
    // test_MUL_AB(10);
    // test_MULC(1);
    // test_SQU_A(100);
    // test_SQUC(1);
    // test_MULC_karastuba(100);

#if 0 // 벤치마킹
    // bench_MUL();
    // bench_ADD();
    // bench_DIV();

    // bench_lshift();
    // bench_gcd();
    // bench_prime();
    // bench_SPDM();
    bench_RSA();

#endif

#if 0 // 부검
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;
    bigint *n = NULL;
    bigint *M = NULL;

    // for (int j = 0; j < 10000; j++)
    // {
    //     bi_gen_rand(&A, NON_NEGATIVE, 10);
    //     bi_gen_rand(&B, NON_NEGATIVE, 10);
    //     printf("%d-th = %d\n", j, bi_cmp(A, B));
    // }

    // bi_gen_rand(&A, NON_NEGATIVE, 10);
    // for (int j = 0; j < 100000; j++)
    // {
    //     bi_subi(&A, 1);
    //     // bi_gen_rand(&B, NON_NEGATIVE, 10);
    //     bi_print(A);
    // }

#if 0 // RSA

    // textbook_RSA(1024);
    RSA_crt(512);

    // bi_gen_random_element(&C, NON_NEGATIVE, 3);
    // printf("C = ");
    // bi_print(C);
    // printf("bitlen(C) = %d\n", bi_bit_cnt(C));

    // do
    // {
    //     bi_SPDM(C, A);
    // } while (/* condition */);

    // bi_gen_rand_range(&C, NON_NEGATIVE, 0, 30);

    // bi_gen_rand_bit(C, A, 500);

    // printf("#   RSA-1024 Key list\n");
    // printf("p = ");
    // bi_print(p);
    // printf("q = ");
    // bi_print(q);
    // printf("N = ");
    // bi_print(N);
    // printf("phi(N) = ");
    // bi_print(phi_N);
    // printf("e = ");
    // bi_print(e);
    // printf("d = ");
    // bi_print(d);

#endif

    // bi_gen_rand(&A, NON_NEGATIVE, 32);

    // printf("A = ");
    // bi_print(A);

    // bi_SPDM(&C, A);

    // printf("C = ");
    // bi_print(C);
    // bi_SPDM(&C, A);
    // if (bi_cmp(C, A) == -1)
    //     printf("C < A \n");
    // else
    //     printf("Error!\n");
    // printf("print(\"### EEA TEST ###\\n\")\n");
    // // printf("cnt = 0\n");
    // newline;
    // int TEST = 1;
    // for (int j = 0; j < TEST; j++)
    // {

    //     int num1 = rand() % 0x0f + 1;
    //     int num2 = rand() % 0x0f + 1;

    //     bi_gen_rand(&A, NON_NEGATIVE, num1);
    //     bi_gen_rand(&B, NON_NEGATIVE, num2);

    //     bi_eea_bin_itr(&Q, &C, &R, A, B);
    //     sage_show_xgcd(&C, A, B, j);
    // }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");

    // printf("C = ");
    // bi_print(C);

    // bi_new(&A, 1);
    // A->a[0] = 0xa3;
    // int ret = bi_is_prime(A, 40);

    // if (ret == true)
    //     printf("A is prime\n");
    // else
    //     printf("ERROR!\n");

    bi_delete_3(&Q, &R, &n);
    bi_delete_3(&A, &B, &C);
    bi_delete(&M);

#endif
    return 0;
}