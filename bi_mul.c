#include "bi_local.h"
#include "bi_op.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_MUL_AB(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
 * 단일 워드 2개를 입력받아 곱셈 연산 수행 후 최대 2워드 크기의 출력값을 반환하는 함수.
 * 단일 워드 곱셈이므로 결과값 C의 최대 워드 길이는 2워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_MUL_AB(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_MUL_AB(OUT bigint **C, IN word A, IN word B)
{
    // 이 부분 new 해줘도 안해줘도 둘다 컴파일 되는데 어떤거 쓰는지 궁금
    bi_new(C, 2);

    // A1, B1 = A, B의 상위 w/2비트
    // A0, B0 = A, B의 하위 w/2비트

    word A1 = A >> (w / 2);
    word A0 = A << (w / 2) >> (w / 2);

    word B1 = B >> (w / 2);
    word B0 = B << (w / 2) >> (w / 2);

    word T1 = A1 * B0;
    word T0 = A0 * B1;

    T0 = T1 + T0;
    T1 = T0 < T1;

    word C1 = A1 * B1;
    word C0 = A0 * B0;

    word T = C0;

    C0 = C0 + (T0 << (w / 2));
    C1 = C1 + (T1 << (w / 2)) + (T0 >> (w / 2)) + (C0 < T);

    // C = C1 || C0
    (*C)->a[1] = C1;
    (*C)->a[0] = C0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_MULC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
 * 다중 워드 2개를 입력받아 곱셈 연산 수행 후 최대 wordlen(A) + wordlen(B) 워드 크기의 출력값을 반환하는 함수.
 * 다중 워드 곱셈이므로 결과값 C의 최대 워드 길이는 wordlen(A) + wordlen(B) 워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_MULC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
void bi_MULC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bi_new(C, A->wordlen + B->wordlen);
    bigint *T = NULL;

    for (int j = 0; j < A->wordlen; j++)
        for (int i = 0; i < B->wordlen; i++)
        {
            // bi_resize 함수 안쓰고 ADD 함수로 대체하는 방법도 있음 어느것을 쓸지 고민 중
            bi_resize(C, A->wordlen + B->wordlen);
            bi_new(&T, 2);

            bi_MUL_AB(&T, A->a[j], B->a[i]);
            bi_word_lshift(&T, i + j);
            bi_ADDC(C, *C, T);
        }

    bi_delete(&T);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_MUL(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
 * 임의의 정수 A와 B를 입력받아 MULC를 통한 곱셈 연산 수행 후 결과값 C를 반환하는 함수.
 * 다중 워드 곱셈이므로 결과값 C의 최대 워드 길이는 wordlen(A) + wordlen(B) 워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_MUL(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
// void bi_MUL(OUT bigint **C, IN bigint *A, IN bigint *B)
// {
//     // Case 1: A = 0 or B = 0 then C = 0
//     if (bi_is_zero(A) == true or bi_is_zero(B) == true)
//     {
//         bi_set_zero(C);
//         return;
//     }

//     // Case 2: A = 1 then C = 1 * B
//     if (bi_is_one(A) == true)
//     {
//         bi_assign(C, B);
//         return;
//     }
//     // Case 3: A = -1 then C = -(1) * B
//     else if (bi_is_minus_one(A) == true)
//     {
//         bi_assign(C, B);
//         bi_flip_sign(*C);
//         return;
//     }
//     // Case 4: B = 1 then C = 1 * A
//     if (bi_is_one(B) == true)
//     {
//         bi_assign(C, A);
//         return;
//     }
//     // Case 5: B = -1 then C = -(1) * A
//     else if (bi_is_minus_one(B) == true)
//     {
//         bi_assign(C, A);
//         bi_flip_sign(*C);
//         return;
//     }
//     // Case 6: Otherwise
//     bi_abs(A);
//     bi_abs(B);
//     bi_MULC(C, A, B);
//     (*C)->sign = A->sign ^ B->sign;
//     bi_flip_sign(A);
//     bi_flip_sign(B);
// }

void bi_MUL(OUT bigint **C, IN bigint *A, IN bigint *B)
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
        bi_flip_sign(*C);
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
        bi_flip_sign(*C);
        return;
    }
    // Case 6: Otherwise
    // bi_abs(A);
    // bi_abs(B);
    bi_MULC(C, A, B);
    (*C)->sign = A->sign ^ B->sign;
    // bi_flip_sign(A);
    // bi_flip_sign(B);
}

void bi_MULC_karatsuba(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    int flag = 5;
    if (flag >= bi_min(A->wordlen, B->wordlen))
    {
        // printf("wordlen(A) = %d, wordlen(B) = %d\n", A->wordlen, B->wordlen);
        // printf("min(n, m): %d\n", bi_min(A->wordlen, B->wordlen));
        printf("if문 들어옴\n");
        bi_MUL(C, A, B);
        return;
    }

    int l = (bi_max(A->wordlen, B->wordlen) + 1) >> 1;
    printf("max(n, m): %d\n", bi_max(A->wordlen, B->wordlen));
    printf("l = %d\n", l);

    bigint *A1 = NULL;
    bigint *A0 = NULL;

    bi_assign(&A1, A);
    bi_assign(&A0, A);

    bi_word_rshift(&A1, l);
    bi_word_reduction(&A0, l);

    bigint *B1 = NULL;
    bigint *B0 = NULL;

    bi_assign(&B1, B);
    bi_assign(&B0, B);

    bi_word_rshift(&B1, l);
    bi_word_reduction(&B0, l);

    // 테스트
    printf("A1 = ");
    bi_print(A1);
    printf("A0 = ");
    bi_print(A0);
    printf("\n");

    printf("B1 = ");
    bi_print(B1);
    printf("B0 = ");
    bi_print(B0);
    printf("\n");

    // printf("A1 sign = %d, A0 sign = %d\n", A1->sign, A0->sign);

    bigint *T1 = NULL;
    bigint *T0 = NULL;

    // printf("sign(A1) = %d, sign(B0) = %d\n", A1->sign, B1->sign);
    bi_MULC_karatsuba(&T1, A1, B1);
    // printf("sign(A1) = %d, sign(B0) = %d\n", A1->sign, B1->sign);
    bi_MULC_karatsuba(&T0, A0, B0);

    printf("T1 = ");
    bi_print(T1);

    printf("T0 = ");
    bi_print(T0);
    printf("\n");

    bigint *R = NULL;

    // if (R == NULL)
    //     bi_new(&R, 1);

    bi_attach(&R, T1, T0);

    bigint *S1 = NULL;
    bigint *S0 = NULL;

    // printf("이상: A1 sign = %d, A0 sign = %d\n", A1->sign, A0->sign);
    bi_SUB(&S1, A0, A1);
    printf("S1 = ");
    bi_print(S1);

    bi_SUB(&S0, B1, B0);
    printf("S0 = ");
    bi_print(S0);
    printf("\n");

    bigint *S = NULL;

    if (S == NULL)
        bi_new(&S, 1);

    int t_sign1 = S1->sign;
    int t_sign0 = S0->sign;

    S1->sign = NON_NEGATIVE;
    S0->sign = NON_NEGATIVE;

    bi_MULC_karatsuba(&S, S1, S0);

    S1->sign = t_sign1;
    S0->sign = t_sign0;

    S->sign = S1->sign ^ S0->sign;
    printf("kara_S = ");
    bi_print(S);

    // printf("T1 = ");
    // bi_print(T1);
    printf("sign(S) = %d\n", S->sign);

    bi_ADD(&S, S, T1);

    printf("S = ");
    bi_print(S);

    bi_ADD(&S, S, T0);

    printf("S = ");
    bi_print(S);
    printf("\n");

    bi_word_lshift(&S, l);
    bi_ADD(&R, R, S);

    bi_assign(C, R);
}
