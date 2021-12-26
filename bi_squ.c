#include "bi_local.h"
#include "bi_op.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SQU_A(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
 * 단일 워드 2개를 입력받아 제곱 연산 수행 후 최대 2워드 크기의 출력값을 반환하는 함수.
 * 단일 워드 제곱이므로 결과값 C의 최대 워드 길이는 2워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_SQU_A(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_SQU_A(OUT bigint **C, word A)
{
    bi_new(C, 2);

    // A1 = A의 상위 w/2비트, A0 = A의 하위 w/2비트
    word A1 = A >> (w / 2);
    word A0 = (A << (w / 2)) >> (w / 2);

    word C1 = A1 * A1;
    word C0 = A0 * A0;

    // C = C1 || C0
    (*C)->a[1] = C1;
    (*C)->a[0] = C0;

    bigint *T = NULL;
    bi_new(&T, 2);

    bi_MUL_AB(&T, A0, A1);

    bi_lshift(&T, w / 2 + 1);

    bi_ADDC(C, *C, T);
    bi_delete(&T);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SQUC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
 * 다중 워드 2개를 입력받아 제곱 연산 수행 후 최대 wordlen(A) + wordlen(B) 워드 크기의 출력값을 반환하는 함수.
 * 다중 워드 제곱이므로 결과값 C의 최대 워드 길이는 wordlen(A) + wordlen(B) 워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_SQUC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
void bi_SQUC(OUT bigint **C, IN bigint *A)
{
    // bi_new(C, 2 * A->wordlen);

    bigint *C1 = NULL;
    bigint *C2 = NULL;

    bi_new(&C1, 1);
    bi_new(&C2, 1);

    bigint *T1 = NULL;
    bigint *T2 = NULL;

    for (int j = 0; j < A->wordlen; j++)
    {
        bi_SQU_A(&T1, A->a[j]);
        bi_word_lshift(&T1, 2 * j);
        bi_ADDC(&C1, T1, C1);

        for (int i = j + 1; i < A->wordlen; i++)
        {
            bi_MUL_AB(&T2, A->a[j], A->a[i]);
            bi_word_lshift(&T2, i + j);
            bi_ADD(&C2, C2, T2);
        }
    }
    bi_lshift(&C2, 1);
    bi_ADD(C, C1, C2);

    bi_delete(&C1);
    bi_delete(&C2);
    bi_delete(&T1);
    bi_delete(&T2);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SQU(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
 * 임의의 정수 A와 B를 입력받아 SQUC()함수를 통한 제곱 연산 수행 후 결과값 C를 반환하는 함수.
 * Case 별로 제곱 연산 수행
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_SQU(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
void bi_SQU(OUT bigint **C, IN bigint *A)
{
    // Case 1: A = 0 or A = 1 or A = -1
    if (bi_is_zero(A) == true or bi_is_one(A) == true or bi_is_minus_one(A) == true)
    {
        bi_assign(C, A);
        bi_abs(*C);
        return;
    }

    // Case 2: Otherwise
    bi_SQUC(C, A);
}