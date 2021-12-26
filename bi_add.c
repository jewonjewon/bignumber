#include "bi_local.h"
#include "bi_op.h"

// ADD함수에서 SUB함수가 사용되기 때문에 프로토 타입으로 지정
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_ADD_ABc(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드, 입력: 해당 carry 값)
 * 단일 워드 2개를 입력받아 덧셈 연산 수행 후 1워드 크기 출력값 C와 carry c를 반환하는 함수.
 * carry를 고려한 단일 워드 덧셈 처리 함수.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_ADD_ABc(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드, 입력: 해당 carry 값)
void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c)
{
    int cc = 0;
    *C = A + B;

    if (*C < A)
        cc = 1;

    *C = *C + *c;

    if (*C < *c)
        cc += 1;

    *c = cc;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_ADDC(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드): 덧셈 core 함수
 * 기본 가정: A와 B의 부호는 같음, wordlen(A) ≥ wordlen(B)
 * 다중 워드 2개를 입력받아 덧셈 연산 수행 후 최대 wordlen(A) + 1의 워드 크기의 출력값을 반환하는 함수.
 * (오류 방지)덧셈 연산 수행을 위해 bi_resize()함수를 사용하여 B의 워드길이를 A의 워드길이와 동일하게 설정해줌
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_ADDC(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_ADDC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *T = NULL;
    bi_new(&T, A->wordlen + 1);

    bi_resize(&B, A->wordlen);
    int c = 0;

    for (int j = 0; j < A->wordlen; j++)
        bi_ADD_ABc(&T->a[j], A->a[j], B->a[j], &c);

    T->a[A->wordlen] = c;

    bi_refine(B);
    bi_assign(C, T);
    bi_refine(*C);
    bi_delete(&T);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_ADD(출력: C = A + B, 입력: 임의의 정수, 입력: 임의의 정수)
 * 임의의 두 정수 A, B를 입력받아 덧셈 연산 수행 후 출력값 C(= A + B)를 반환하는 함수.
 * Case 별로 덧셈 연산 수행
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_ADD(출력: C = A + B, 입력: 임의의 정수, 입력: 임의의 정수)
void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    // Case 1: A = 0, C = B
    if (bi_is_zero(A) == true)
    {
        bi_assign(C, B);
        return;
    }
    // Case 2: B = 0, C = A
    if (bi_is_zero(B) == true)
    {
        bi_assign(C, A);
        return;
    }
    // Case 3: A > 0 and B < 0, C = A - |B|
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        bi_abs(B);
        bi_SUB(C, A, B);
        bi_flip_sign(B);
        return;
    }

    // Case 4: A < 0 and B > 0, C = B - |A|
    if (A->sign == NEGATIVE and B->sign == NON_NEGATIVE)
    {
        bi_abs(A);
        bi_SUB(C, B, A);
        bi_flip_sign(A);
        return;
    }

    // Case 5: wordlen(A) ≥ wordlen(B)
    if (A->wordlen >= B->wordlen)
    {
        bi_ADDC(C, A, B);
        (*C)->sign = A->sign;
        return;
    }
    // Case 6: wordlen(A) < wordlen(B)
    else
    {
        bi_ADDC(C, B, A);
        (*C)->sign = A->sign;
        return;
    }
}