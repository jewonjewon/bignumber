#include <stdio.h>

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"

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

void test_l2r(int TEST)
{
    printf("print(\"### l2r ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *C = NULL;

    for (int j = 0; j < TEST; j++)
    {
        int n = rand() % 0xf;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, NON_NEGATIVE, num1);
        bi_l2r(&C, A, n);
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
        printf("    cnt = cnt + 1\n");
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}
int main()
{
    srand((unsigned)time(NULL));

    // test_ADD(1000);
    // test_SUB(1000);
    // test_MUL(1000);
    // test_SQU(1000);
    // test_KMUL(1000);
    // test_KSQU(1000);
    // test_DIV(1000);

    // test_l2r(1);
    // test_r2l(1);
    // test_mns(1);
    test_gcd_bin(100);

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

    // // 시간 측정
    // printf("SHIFT 함수 시간 측정\n");
    // int cnt = 1000000;

    // double start1, start2;
    // double end1, end2;

    // start1 = (double)clock() / CLOCKS_PER_SEC;
    // test_bi_word_lshift1(cnt);
    // end1 = (((double)clock()) / CLOCKS_PER_SEC);

    // start2 = (double)clock() / CLOCKS_PER_SEC;
    // test_bi_word_lshift2(cnt);
    // end2 = (((double)clock()) / CLOCKS_PER_SEC);

    // printf("%.0d번 수행 기준\n\n", cnt);

    // printf("1번 함수 수행 시간 :%lf\n", (end1 - start1));
    // printf("2번 함수 수행 시간 :%lf\n", (end2 - start2));

    // word Q = 0;
    // word B = 0x81234007;
    // bigint *A = NULL;
    // bi_new(&A, 2);

    // A->a[1] = 0x11112222;
    // A->a[0] = 0xf3334444;
    // Q = bi_long_div_2word(A, B);

    // printf("%x\n", Q);

    // // TEST div 용
    // bigint *A = NULL;
    // bigint *B = NULL;

    // bigint *Q = NULL;
    // bigint *R = NULL;

    // int num1 = rand() % 0x07 + 1;
    // int num2 = rand() % 0x05 + 1;

    // bi_gen_rand(&A, NON_NEGATIVE, num1);
    // bi_gen_rand(&B, NON_NEGATIVE, num2);

    // printf("A = ");
    // bi_print(A);
    // printf("B = ");
    // bi_print(B);

    // bi_DIV(&Q, &R, A, B);
    // // bi_DIVC(&Q, &R, A, B);
    // // bi_DIVCC(&Q, &R, A, B);

    // printf("Q = ");
    // bi_print(Q);
    // printf("R = ");
    // bi_print(R);
    // printf("print(A//B ==Q)\n");
    // printf("print(hex(A//B))\n");
    // printf("print(A%%B ==R)\n");
    // printf("print(hex(A%%B))\n");

    // bi_delete(&A);
    // bi_delete(&B);
    // bi_delete(&Q);
    // bi_delete(&R);

    // // End TEST

    return 0;
}
