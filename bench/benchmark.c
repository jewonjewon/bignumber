#include <stdio.h>

#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"

void bench_bi_MUL(IN int TEST, int len)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    // printf("### bi_mul ###\n");
    // printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % (8 * len) + 1;
        int num2 = rand() % (8 * len) + 1;
        // printf("%d, %d\n", num1, num2);

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_mul(&C, A, B);
        // sage_show_mul(&C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");

    bi_delete_3(&C, &A, &B);
}

void bi_check_MULC_karatsuba(OUT bigint **C, IN bigint *A, IN bigint *B, int FLAG)
{
    // flag = 3일 때 가장 빠름
    int flag = FLAG;
    // printf("flag = %d\n", flag);

    if (flag >= bi_min(A->wordlen, B->wordlen))
    {
        bi_mul(C, A, B);
        return;
    }

    int l = (bi_max(A->wordlen, B->wordlen) + 1) >> 1;

    bigint *A1 = NULL;
    bigint *A0 = NULL;

    bi_assign(&A1, A);
    bi_word_rshift(&A1, l);

    bi_assign(&A0, A);
    bi_word_reduction(&A0, l);

    bigint *B1 = NULL;
    bigint *B0 = NULL;

    bi_assign(&B1, B);
    bi_word_rshift(&B1, l);

    bi_assign(&B0, B);
    bi_word_reduction(&B0, l);

    //
    // printf("# l = %d\n", l);
    // printf("# A1 = ");
    // bi_print(A1);
    // printf("# A0 = ");
    // bi_print(A0);
    // newline;
    // printf("# B1 = ");
    // bi_print(B1);
    // printf("# B0 = ");
    // bi_print(B0);
    // newline;

    bigint *T1 = NULL;
    bigint *T0 = NULL;

    bi_check_MULC_karatsuba(&T1, A1, B1, flag);
    bi_check_MULC_karatsuba(&T0, A0, B0, flag);

    bigint *R = NULL;

    bi_assign(&R, T1);
    bi_word_lshift(&R, 2 * l);
    bi_add(&R, R, T0);

    bigint *S1 = NULL;
    bigint *S0 = NULL;

    bi_sub(&S1, A0, A1);
    bi_sub(&S0, B1, B0);

    //
    // printf("# T1 = ");
    // bi_print(T1);
    // printf("# T0 = ");
    // bi_print(T0);
    // newline;
    // printf("#  R = ");
    // bi_print(R);
    // newline;
    // printf("# S1 = ");
    // bi_print(S1);
    // printf("# S0 = ");
    // bi_print(S0);
    // newline;

    bigint *S = NULL;

    int t1 = S1->sign;
    int t0 = S0->sign;

    bi_abs(S1);
    bi_abs(S0);

    bi_kmul_core(&S, S1, S0);

    S1->sign = t1;
    S0->sign = t0;
    S->sign = S1->sign ^ S0->sign;

    //
    // printf("#1.   S = ");
    // bi_print(S);
    // newline;

    bi_add(&S, S, T1);

    //
    // printf("# T1 = ");
    // bi_print(T1);

    // printf("#2.   S = ");
    // bi_print(S);
    // newline;

    bi_add(&S, S, T0);

    //
    // printf("#3.   S = ");
    // bi_print(S);
    // newline;

    bi_word_lshift(&S, l);

    //
    // printf("#4.   S = ");
    // bi_print(S);
    // newline;

    bi_add(&R, R, S);
    // 함수를 두개 만들기
    // z = x + y, z = z + x

    //
    // printf("#  R = ");
    // bi_print(R);
    // newline;

    bi_assign(C, R);

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&B1);
    bi_delete(&B0);
    bi_delete(&R);
    bi_delete(&T1);
    bi_delete(&T0);
    bi_delete(&S);
    bi_delete(&S1);
    bi_delete(&S0);

    return;
}

// bi_mul(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
void bi_check_KMUL(OUT bigint **C, IN bigint *A, IN bigint *B, int FLAG)
{
    // Case 1: A = 0 or B = 0 then C = 0
    if (bi_is_zero(A) == true or bi_is_zero(B) == true)
    {
        bi_set_zero(C);
        return;
    }

    // Case 2: A = 1 then C = 1 * B
    if (bi_is_one(A) == true)
    {
        bi_assign(C, B);
        return;
    }
    // Case 3: A = -1 then C = -(1) * B
    else if (bi_is_minus_one(A) == true)
    {
        bi_assign(C, B);
        (*C)->sign = A->sign ^ B->sign;
        return;
    }
    // Case 4: B = 1 then C = 1 * A
    if (bi_is_one(B) == true)
    {
        bi_assign(C, A);
        return;
    }
    // Case 5: B = -1 then C = -(1) * A
    else if (bi_is_minus_one(B) == true)
    {
        bi_assign(C, A);
        (*C)->sign = A->sign ^ B->sign;
        return;
    }
    // Case 6: Otherwise
    int t1 = A->sign;
    int t0 = B->sign;

    bi_abs(A);
    bi_abs(B);

    bi_check_MULC_karatsuba(C, A, B, FLAG);

    A->sign = t1;
    B->sign = t0;
    (*C)->sign = t1 ^ t0;
}

void bench_bi_check_KMUL(IN int TEST, int FLAG)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    // printf("### bi_kmul ###\n");
    // printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_check_KMUL(&C, A, B, FLAG);
        // sage_show_mul(&C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");

    bi_delete_3(&C, &A, &B);
}

// void bench_bi_KMUL(IN int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     bigint *C = NULL;
//     // printf("### bi_kmul ###\n");
//     // printf("cnt = 0\n");

//     for (int j = 0; j < TEST; j++)
//     {
//         int sign1 = rand() % 2;
//         int sign2 = rand() % 2;

//         int num1 = rand() % 0x0f + 1;
//         int num2 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, sign1, num1);
//         bi_gen_rand(&B, sign2, num2);

//         bi_kmul(&C, A, B);
//         // sage_show_mul(&C, A, B, j);
//     }
//     // printf("if (cnt == 0):\n");
//     // printf("    print(\"ALL TRUE!\")\n");

//     bi_delete_3(&C, &A, &B);
// }

// 워드길이별 카라추바와 스쿨북 비교 (1워드 ~  64워드)
void bench_bi_KMUL(IN int TEST, int len)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    // printf("### bi_kmul ###\n");
    // printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % (8 * len) + 1;
        int num2 = rand() % (8 * len) + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_kmul(&C, A, B);
        // sage_show_mul(&C, A, B, j);
    }
    // printf("if (cnt == 0):\n");
    // printf("    print(\"ALL TRUE!\")\n");

    bi_delete_3(&C, &A, &B);
}

void bench_MUL()
{
    printf("# Schoolbook MUL v.s. Karatsuba MUL \n");
    // cnt = 시행 횟수
    int cnt = 10000;

    double start1, start2;
    double end1, end2;
    for (int j = 1; j < 7; j++)
    {
        start1 = (double)clock() / CLOCKS_PER_SEC;
        bench_bi_MUL(cnt, j);
        end1 = (((double)clock()) / CLOCKS_PER_SEC);
        start2 = (double)clock() / CLOCKS_PER_SEC;
        bench_bi_KMUL(cnt, j);
        end2 = (((double)clock()) / CLOCKS_PER_SEC);

        // printf("# ===== ===== 측정 결과 ===== =====\n");
        // printf("# %.0d번 수행 기준\n\n", cnt);

        printf("%lf, ", (end1 - start1));
        // printf("# 1번 함수 1회 수행 시간 :%lf\n", (end1 - start1) / cnt);
        printf("%lf, ", (end2 - start2));
        // printf("# 2번 함수 1회 수행 시간 :%lf\n", (end2 - start2) / cnt);
    }
}