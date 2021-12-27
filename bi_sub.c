#include "bi_local.h"
#include "bi_op.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SUB_AbB(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드, 입력: 해당 borrow 값)
 * 단일 워드 2개를 입력받아 뺄셈 연산 수행 후 최대 1워드 크기의 출력값을 반환하는 함수.
 * borrow 를 고려한 단일 워드 뺄셈 처리 함수.
 * 단일 워드 뺄셈이므로 결과값 C의 최대 워드 길이는 1워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_SUB_AbB(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_SUB_AbB(OUT word *C, IN word A, IN word B, IN OUT int *b)
{
    int bb = 0; // 현재 borrow 값
    *C = A - *b;

    if (A < *b)
        bb = 1;

    if (*C < B)
        bb = bb + 1;
    *C = *C - B;

    *b = bb;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SUBC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드): 뺄셈 core 함수
 * 기본 가정: A와 B의 부호는 같음, wordlen(A) ≥ wordlen(B)
 * 다중 워드 2개를 입력받아 뺄셈 연산 수행 후 최대 입력 배열 A의 워드 크기의 출력값을 반환하는 함수.
 * (오류 방지)뺄셈 연산 수행을 위해 bi_resize()함수를 사용하여 B의 워드 길이를 A의 워드 길이와 동일하게 설정해줌
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_SUBC(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    // printf("A = ");
    // bi_print(A);

    // printf("B = ");
    // bi_print(B);

    // bigint *T = NULL;
    // bi_new(&T, A->wordlen);
    bi_new(C, A->wordlen);

    bi_resize(&B, A->wordlen);
    int b = 0;

    for (int j = 0; j < A->wordlen; j++)
        bi_SUB_AbB(&(*C)->a[j], A->a[j], B->a[j], &b);

    bi_refine(B);
    // bi_assign(C, T);
    bi_refine(*C);
    // bi_delete(&T);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SUB(출력: C = A - B, 입력: 임의의 정수, 입력: 임의의 정수)
 * 임의의 두 정수 A, B를 입력받아 뺄셈 연산 수행 후 출력값 C(= A - B)를 반환하는 함수.
 * Case 별로 뺄셈 연산 수행
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_SUB(출력: C = A - B, 입력: 임의의 정수, 입력: 임의의 정수)
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    // Case 1: A = B ,C = 0
    if (bi_cmp(A, B) == 0)
    {
        bi_set_zero(C);
        return;
    }
    // Case 2: A = 0, C = -B
    if (bi_is_zero(A) == true)
    {
        bi_assign(C, B);
        bi_flip_sign(*C);
        return;
    }
    // Case 3: B = 0, C = -A
    if (bi_is_zero(B) == true)
    {
        bi_assign(C, A);
        return;
    }

    // Case 4: 0 < B ≤ A,  C = A - B
    if (A->sign == NON_NEGATIVE and B->sign == NON_NEGATIVE and bi_cmp(A, B) == 1)
    {
        bi_SUBC(C, A, B);
        return;
    }

    // Case 5: 0 < A < B,  -C = B - A
    else if (A->sign == NON_NEGATIVE and B->sign == NON_NEGATIVE and bi_cmp(A, B) == -1)
    {
        bi_SUBC(C, B, A);
        (*C)->sign = NEGATIVE;
        return;
    }
    // Case 6: 0 > A ≥ B,  C = |B| - |A|
    if (A->sign == NEGATIVE and B->sign == NEGATIVE and bi_cmp(A, B) == 1)
    {
        bi_abs(A);
        bi_abs(B);
        bi_SUBC(C, B, A);
        bi_flip_sign(A);
        bi_flip_sign(B);
        return;
    }

    // Case 7: 0 > B > A,  C = |B| - |A|
    else if (A->sign == NEGATIVE and B->sign == NEGATIVE and bi_cmp(A, B) == -1)
    {
        bi_abs(A);
        bi_abs(B);
        bi_SUBC(C, A, B);
        (*C)->sign = NEGATIVE;
        bi_flip_sign(A);
        bi_flip_sign(B);
        return;
    }

    // Case 8: A > 0 and B < 0
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        bi_abs(B);
        bi_ADD(C, A, B);
        bi_flip_sign(B);
        return;
    }
    else
    {
        bi_abs(A);
        bi_ADD(C, A, B);
        bi_flip_sign(A);
        (*C)->sign = NEGATIVE;
        return;
    }
}