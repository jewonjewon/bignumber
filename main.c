#include <stdio.h>

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"
#include "benchmark.h"

void test_bi_word_rshift(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
        int num1 = rand() % 0x0f + 1;
        // int x = 2;
        bi_gen_rand(&A, NON_NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_word_rshift(&A, x);

        printf("C = ");
        bi_print(A);

        printf("print(A >> (%d * %d) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

void test_MULC_karastuba(int TEST)
{
    printf("\n\n\n\n\n### 카라츄바 테스트\n\n");
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    // bi_MULC_karastuba TEST
    for (int j = 0; j < TEST; j++)
    {
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, 20);
        bi_gen_rand(&B, NON_NEGATIVE, 20);
        bi_MULC_karatsuba(&C, A, B);
        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);

        printf("print(A * B == C) #%d\n", j);
    }
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_bi_word_reduction(int TEST)
{
    bigint *A = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int x = rand() % 0xf + 1;
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NEGATIVE, num1);

        printf("A = ");
        bi_print(A);

        bi_word_reduction(&A, x);
        printf("C = ");
        bi_print(A);
        printf("print(A %% (2 ** (%d * %d)) == C) #%d\n", x, w, j);
    }

    bi_delete(&A);
}

// void bi_single_add(OUT word *C, OUT word *c, IN word A, IN word B)
// {
//     *C = A + B;

//     if (*C < A)
//         *c = 1;
// }

// void bi_bigintA_add_wordB(bigint **C, bigint *A, word B)
// {
//     word c = 0;
//     word t = 0;
//     int j = 1;

//     bi_single_add(&(*C)->a[0], &c, A->a[0], B);
//     t = c;

//     printf("carry c = %d\n", t);
//     while (1)
//     {
//         if (t == 0)
//             return;

//         bi_single_add(&(*C)->a[j], &c, A->a[j], t);
//         printf("carry c = %d\n", c);
//         j++;
//     }
//     word G = 0;
//     if (A->a[j] == MASK)
//         C->a[j] = 0;

//     c = 1;
// }

// void bi_add_one(bigint **C, bigint *A, word B)
// {
//     int c = 0;

//     A->a[0] = A->a[0] + B;

//     if (A->a[0] < B)
//         c = 1;

//     if (c == 1)
//     {
//         for (int j = 1; j < A->wordlen; j++)
//         {
//             if (A->a[j] == MASK)
//                 A->a[j] = 0;
//             else
//             {
//                 A->a[j]++;
//                 break;
//             }
//         }
//     }
//     bi_assign(C, A);
// }

// void test_bi_long_div_2word(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;

//     for (int j = 0; j < TEST; j++)
//     {
//         bi_gen_rand(&A, NON_NEGATIVE, 2);
//         bi_gen_rand(&B, NON_NEGATIVE, 1);

//         if (A->a[1] < B->a[0])
//             printf("A1 ≥ B\n");

//         Q = bi_long_div_2word(A, B->a[0]);

//         printf("A = ");
//         bi_print(A);
//         printf("B = ");
//         bi_print(B);
//         printf("Q = %#llx\n", Q);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(hex(A//B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
// }

// void test_DIVCC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {
//         // int num1 = rand() % 0x0f + 2;
//         // int num2 = rand() % 0x0f + 1;
//         // while (1)
//         // {
//         //     bi_gen_rand(&A, NON_NEGATIVE, num1);
//         //     bi_gen_rand(&B, NON_NEGATIVE, num2);
//         //     if (bi_cmp(B, A) == -1 and bi_cmp(B, A) == 0)
//         //     {
//         //         bigint *T = NULL;
//         //         bi_new(&T, 1);
//         //         bi_assign(&T, B);
//         //         bi_word_lshift(&T, 1);
//         //         if (bi_cmp(A, T) == -1)
//         //             if (B->a[B->wordlen - 1] >= pow2(w - 1))
//         //             {
//         //                 printf("DIVCC 입력 조건 0 < B ≤ A < BW, B_{m-1} ≥ 2^{w-1} 성립!\n");
//         //                 bi_delete(&T);
//         //                 break;
//         //             }
//         //         bi_delete(&T);
//         //     }
//         //     check;
//         // }

//         int num1 = rand() % 0x0f + 1;
//         // int num2 = rand() % 0x0f + 1;
//         // while (num1 < num2)
//         // {

//         num1 = rand() % 0x0f + 1;
//         // num2 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num1 - 1);
//         // }

//         if (bi_cmp(B, A) == -1 and bi_cmp(B, A) == 0)
//         {
//             bigint *T = NULL;
//             bi_new(&T, 1);
//             bi_assign(&T, B);
//             bi_word_lshift(&T, 1);
//             if (bi_cmp(A, T) == -1)
//                 if (B->a[B->wordlen - 1] >= pow2(w - 1))
//                 {
//                     printf("DIVCC 입력 조건 0 < B ≤ A < BW, B_{m-1} ≥ 2^{w-1} 성립!\n");
//                     bi_delete(&T);
//                     break;
//                 }
//             bi_delete(&T);
//         }

//         bi_DIVCC(&Q, &R, A, B);

//         printf("A = ");
//         bi_print(A);
//         printf("B = ");
//         bi_print(B);
//         printf("Q = %#llx\n", Q);
//         printf("R = ");
//         bi_print(R);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(A %% B == R) #%d\n", j);

//         printf("print(hex(A//B))\n");
//         printf("print(hex(A%%B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&R);
// }

// void test_DIVC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {

//         int num1 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num1 - 1);

//         // bi_gen_rand(&A, NON_NEGATIVE, 5);
//         // bi_gen_rand(&B, NON_NEGATIVE, 3);

//         ///
//         bigint *T = NULL;

//         bi_assign(&T, B);
//         bi_word_lshift(&T, 1);

//         if (bi_cmp(A, T) == -1)
//         {
//             if (B->a[B->wordlen - 1] >= pow2(w - 1))
//             {
//                 printf("DIVC 입력 조건 0 ≤ A < BW 성립!\n");
//             }
//         }
//         bi_delete(&T);
//         ///

//         bi_DIVC(&Q, &R, A, B);

//         printf("A = ");
//         bi_print(A);
//         printf("B = ");
//         bi_print(B);
//         printf("Q = %#llx\n", Q);
//         printf("R = ");
//         bi_print(R);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(A %% B == R) #%d\n", j);

//         printf("print(hex(A//B))\n");
//         printf("print(hex(A%%B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&R);
// }

void test_DIV(int TEST)
{
    printf("print(\"### DIV TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
            {
                bi_gen_rand(&A, NON_NEGATIVE, num1);
                bi_gen_rand(&B, NON_NEGATIVE, num2);
                if (bi_is_zero(B) == true)
                    continue;
                break;
            }
        }

        bi_DIV(&Q, &R, A, B);
        sage_show_div(&Q, &R, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);
}

void test_long_div_bin(int TEST)
{
    printf("print(\"### BINARY LONG DIVISION TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
            {
                bi_gen_rand(&A, NON_NEGATIVE, num1);
                bi_gen_rand(&B, NON_NEGATIVE, num2);
                if (bi_is_zero(B) == true)
                    continue;
                break;
            }
        }

        bi_long_div_bin(&Q, &R, A, B);
        sage_show_div(&Q, &R, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);
}

void test_l2r(int TEST)
{
    printf("print(\"### l2r ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *C = NULL;
    bigint *N = NULL;

    bi_new(&N, 1);
    for (int j = 0; j < TEST; j++)
    {
        int n = rand() % 0xf;
        int num1 = rand() % 0x0f + 1;
        N->a[0] = n;
        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_l2r(&C, A, N);
        printf("n = %d\n", n);
        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print((A ** n) == C)\n");
        printf("print(hex(A**n))\n");
    }

    bi_delete_2(&C, &A);
}

void test_mod_l2r(int TEST)
{
    printf("print(\"### mod_l2r ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *C = NULL;
    bigint *N = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int n = rand() % 0xf;
        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&N, NON_NEGATIVE, num2);

        bi_mod_l2r(&C, A, n, N);
        printf("n = %d\n", n);
        printf("A = ");
        bi_print(A);
        printf("N = ");
        bi_print(N);
        printf("C = ");
        bi_print(C);
        printf("print((power_mod(A, n, N)) == C)\n");
        printf("print(hex(power_mod(A, n, N)))\n");
    }

    bi_delete_2(&C, &A);
}

void test_r2l(int TEST)
{
    printf("print(\"### r2l ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int n = rand() % 0xf;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_r2l(&C, A, n);
        printf("n = %d\n", n);
        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print((A ^ n) == C)\n");
        printf("print(hex(A^n))\n");
    }

    bi_delete_2(&C, &A);
}

void test_mns(int TEST)
{
    printf("print(\"### M&S ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int n = rand() % 0xf;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_mns(&C, A, n);
        printf("n = %d\n", n);
        printf("A = ");
        bi_print(A);
        printf("C = ");
        bi_print(C);
        printf("print((A ^ n) == C)\n");
        printf("print(hex(A^n))\n");
    }

    bi_delete_2(&C, &A);
}

void test_gcd_bin(int TEST)
{
    printf("print(\"### BINARY GCD TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_gcd_bin(&C, A, B);

        printf("A = ");
        bi_print(A);
        printf("B = ");
        bi_print(B);
        printf("C = ");
        bi_print(C);
        printf("if (C != gcd(A, B)):\n");
        printf("    print(\"{} : {}\".format(%d, gcd(A, B) == C)) #%d\n", j, j);
        printf("    print(hex(gcd(A, B)))\n");
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_xgcd_bin(int TEST)
{
    printf("print(\"### BINARY EEA TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_gen_rand(&B, NON_NEGATIVE, num2);

        bi_eea_itr(&C, A, B);
        // bi_xgcd_bin(&C, A, B);
        newline;
        printf("A = ");
        bi_print(A);
        newline;
        printf("B = ");
        bi_print(B);
        newline;
        printf("C = ");
        bi_print(C);
        newline;
        printf("if (C != xgcd(A,B)[1]):\n");
        printf("    print(\"{} : {}\".format(%d, xgcd(A,B)[1] == C)) #%d\n", j, j);
        printf("    print(hex(xgcd(A,B)[1]))\n");
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void test_mont_red(int TEST)
{
    printf("print(\"### Montgomery Reduction TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *x = NULL;
    bigint *R = NULL; /* 워드 블록 형태 */
    bigint *N = NULL;
    bigint *C = NULL; /* OUTPUT */

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;
        int num3 = rand() % 0x0f + 1;

        int t = 3;

        bi_gen_rand(&x, NON_NEGATIVE, num1);
        bi_gen_rand(&N, NON_NEGATIVE, num2);

        bi_new(&R, 2);
        R->a[1] = 1;

        bi_word_lshift(&R, t);

        bi_mont_red(&C, x, R, N);

        printf("x = ");
        bi_print(x);
        printf("R = ");
        bi_print(R);
        printf("N = ");
        bi_print(N);
        printf("C = ");
        bi_print(C);
        // printf("if (C != xgcd(A,B)[1]):\n");
        // printf("    print(\"{} : {}\".format(%d, xgcd(A,B)[1] == C)) #%d\n", j, j);
        // printf("    print(hex(xgcd(A,B)[1]))\n");
        // printf("    cnt = cnt + 1\n");
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&x);
    bi_delete(&R);
    bi_delete(&N);
    bi_delete(&C);
}

int main()
{
    srand((unsigned)time(NULL));

#if 1 // 정확성 검증

    test_ADD(1000);
    // test_SUB(1000);
    // test_MUL(1000);
    // test_SQU(1000);
    // test_KMUL(1000);
    // test_KSQU(1000);
    // test_DIV(1000);
    // test_long_div_bin(1000);
    // test_l2r(100);
    // test_r2l(1);
    // test_mns(1);
    // test_gcd_bin(100);
    // test_xgcd_bin(100);
    // test_mod_l2r(100);
    // test_mont_red(1);
#endif

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
      // for (int j = 0; j < 10; j++)
    // bench_MUL();
    // bench_ADD();
    // bench_DIV();
    bench_lshift();
#endif

#if 0 // 부검
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    bi_new(&A, 12);
    bi_new(&B, 3);

    A->a[11] = 0xd1b9a151213ff5db;
    A->a[10] = 0x2150aab2d44f1c1c;
    A->a[9] = 0x53e62a1504dd91a4;
    A->a[8] = 0xd48e08d749740ea2;
    A->a[7] = 0x8803bec06c7e6956;
    A->a[6] = 0x12d93345384dbc91;
    A->a[5] = 0x8857310c66266112;
    A->a[4] = 0x4b1492863c629fdf;
    A->a[3] = 0xb0f81fcbe1645c4d;
    A->a[2] = 0x644d29a50e2519f4;
    A->a[1] = 0x2b190c0f2a123df5;
    A->a[0] = 0x670c66d779d54441;

    B->a[2] = 0x61c90c012efdacfa;
    B->a[1] = 0x21dff116a6d8b230;
    B->a[0] = 0xea5031d8604c9cde;

    printf("%d\n", bi_bit_cnt(A));
    for (int j = 0; j < A->wordlen; j++)
        printf("%d\n", bitlen(A->a[j]));
    printf("A = ");
    bi_print(A);
    printf("B = ");
    bi_print(B);
    bi_bitlen

        bi_DIV(&Q, &R, A, B);
    // for (int j = 0; j < bi_)

    printf("Q = ");
    bi_print(Q);
    printf("R = ");
    bi_print(R);

    bi_delete_3(&Q, &A, &B);
    bi_delete(&R);
#endif
    return 0;
}

// void test_bi_j_bit(int TEST)
// {
//     printf("print(\"### get_j_bit test ###\\n\")\n");
//     printf("cnt = 0\n");

//     bigint *A = NULL;

//     for (int j = 0; j < TEST; j++)
//     {
//         int x = rand() % 0xff;
//         int num1 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);

//         printf("A = ");
//         bi_print(A);

//         bi_get_j_bit(A, x);

//         printf("if (C != gcd(A, B)):\n");
//         printf("    print(\"{} : {}\".format(%d, (A >> j) & 0x1 == A)) #%d\n", j, j);
//         printf("    print(hex(gcd(A, B)))\n");
//         printf("    cnt = cnt + 1\n");
//     }
//     printf("if (cnt == 0):\n");
//     printf("    print(\"ALL TRUE!\")\n");
//     bi_delete(&A);
// }

// void bit_cnt() {}