#include "bi.h"
#include "bi_op.h"

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
    bi_resize(&B, A->wordlen);
    bi_new(C, A->wordlen + 1);

    int c = 0; /* c is carry */

    for (int j = 0; j < A->wordlen; j++)
        bi_ADD_ABc(&(*C)->a[j], A->a[j], B->a[j], &c);

    (*C)->a[A->wordlen] = c;
    bi_refine(B);
    bi_refine(*C);
    (*C)->sign = A->sign;
}

#if 0
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

    (*C)->sign = A->sign;
    bi_delete(&T);
}
#endif
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_ADD(출력: C = A + B, 입력: 임의의 정수, 입력: 임의의 정수)
 * 임의의 두 정수 A, B를 입력받아 덧셈 연산 수행 후 출력값 C(= A + B)를 반환하는 함수.
 * Case 별로 덧셈 연산 수행
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#if 0
// // Case 1: A = 0, C = B
// if (bi_is_zero(A) == true)
// {
//     if (*C == NULL)
//     {
//         bi_assign(C, B);
//         return;
//     }

//     if (bi_cmp(*C, B) == 0)
//         return;

//     bi_assign(C, B);
//     return;
// }

// 보존
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
        if (*C == NULL)
        {
            bi_assign(C, A);
            return;
        }

        if (bi_cmp(*C, A) == 0)
            return;

        bi_assign(C, A);
        return;
    }

    // Case 3: A > 0 and B < 0, C = A - |B|
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        bi_abs(B);
        bi_SUB(C, A, B);
        B->sign = NEGATIVE;
        return;
    }

    // Case 4: A < 0 and B > 0, C = B - |A|
    if (A->sign == NEGATIVE and B->sign == NON_NEGATIVE)
    {
        // 보존
        bigint *T = NULL;
        bi_assign(&T, A);
        T->sign = NON_NEGATIVE;
        // bi_abs(A);
        bi_SUB(C, B, T);
        // A->sign = NEGATIVE;
        bi_delete(&T);
        return;

        // bi_abs(A);
        // bi_SUB(C, B, A);
        // A->sign = NEGATIVE;
        // return;
    }

    // Case 5: wordlen(A) ≥ wordlen(B)
    if (A->wordlen >= B->wordlen)
    {
        bi_ADDC(C, A, B);
        return;
    }
    // Case 6: wordlen(A) < wordlen(B)
    else
    {
        bi_ADDC(C, B, A);
        return;
    }
}
// 보존 end
#endif
#if 1
//  bi_ADD(출력: C = A + B, 입력: 임의의 정수, 입력: 임의의 정수)
void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    if (bi_is_zero(A) == true and bi_is_zero(B))
    {
        bi_set_zero(C);
        return;
    }
    /* Case 1: A = 0, C = B */
    if (bi_is_zero(A) == true)
    {
        bi_assign(C, B);
        return;
    }
    // Case 2: B = 0, C = A
    if (bi_is_zero(B) == true)
    {
        if (*C == NULL)
        {
            bi_assign(C, A);
            return;
        }

        if (bi_cmp(*C, A) == 0)
            return;

        bi_assign(C, A);
        return;
    }
    // Case 3: A > 0 and B < 0, C = A - |B|
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        bi_abs(B);
        bi_SUB(C, A, B);
        B->sign = NEGATIVE;
        return;
    }

    // Case 4: A < 0 and B > 0, C = B - |A|
    if (A->sign == NEGATIVE and B->sign == NON_NEGATIVE)
    {
        bi_abs(A); /* A ← |A| */
        bi_SUB(C, B, A);
        A->sign = NEGATIVE;
        return;
    }

    // Case 5: wordlen(A) ≥ wordlen(B)
    if (A->wordlen >= B->wordlen)
    {
        bi_ADDC(C, A, B);
        return;
    }
    // Case 6: wordlen(A) < wordlen(B)
    else
    {
        bi_ADDC(C, B, A);
        return;
    }
}
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_SUB_AbB(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드, 입력: 해당 borrow 값)
 * 단일 워드 2개를 입력받아 뺄셈 연산 수행 후 최대 1워드 크기의 출력값을 반환하는 함수.
 * borrow 를 고려한 단일 워드 뺄셈 처리 함수.
 * 단일 워드 뺄셈이므로 결과값 C의 최대 워드 길이는 1워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//  bi_SUB_AbB(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_SUB_AbB(OUT word *C, IN word A, IN word B, IN OUT int *b)
{
    word bb = 0; // 현재 borrow 값
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
#if 0
//  bi_SUBC(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *T = NULL;
    bi_new(&T, A->wordlen);

    bi_resize(&B, A->wordlen);
    int b = 0;

    for (int j = 0; j < A->wordlen; j++)
        bi_SUB_AbB(&T->a[j], A->a[j], B->a[j], &b);

    bi_refine(B);
    bi_assign(C, T);
    bi_refine(*C);
    bi_delete(&T);
}
#endif

//  bi_SUBC(출력: bigint형 배열, 입력: 단일 워드, 입력: 단일 워드)
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bi_resize(&B, A->wordlen);
    bi_new(C, A->wordlen);

    int b = 0; /* b is borrow */

    for (int j = 0; j < A->wordlen; j++)
        bi_SUB_AbB(&(*C)->a[j], A->a[j], B->a[j], &b);

    bi_refine(B);
    bi_refine(*C);
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
        if (*C == NULL)
        {
            bi_assign(C, B);
            bi_flip_sign(*C);
            return;
        }

        if (bi_cmp(*C, B) == 0)
        {
            bi_flip_sign(*C);
            return;
        }

        bi_assign(C, B);
        bi_flip_sign(*C);
        return;
    }
    // Case 3: B = 0, C = A
    if (bi_is_zero(B) == true)
    {
        if (*C == NULL)
        {
            bi_assign(C, A);
            return;
        }

        if (bi_cmp(*C, A) == 0)
        {
            printf("# hello\n");
            return;
        }
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

        A->sign = NEGATIVE;
        B->sign = NEGATIVE;
        return;
    }

    // Case 7: 0 > B > A,  C = |B| - |A|
    else if (A->sign == NEGATIVE and B->sign == NEGATIVE and bi_cmp(A, B) == -1)
    {
        bi_abs(A);
        bi_abs(B);

        bi_SUBC(C, A, B);

        A->sign = NEGATIVE;
        B->sign = NEGATIVE;
        (*C)->sign = NEGATIVE;

        return;
    }

    // Case 8: A > 0 and B < 0
    if (A->sign == NON_NEGATIVE and B->sign == NEGATIVE)
    {
        // printf("#수상\n");
        bi_abs(B);
        bi_ADD(C, A, B);
        B->sign = NEGATIVE;
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

/* C += A, ADDITION ASSIGNMENT(+=) OPERATOR (동일 부호 다중 워드 덧셈) */
void bi_addc_asg(IN OUT bigint **C, IN bigint *A)
{
    bigint *T = NULL;
    bi_assign(&T, *C); /* T ← C */

    if (bi_cmp(T, A) == 1) /* if C > B */
        bi_ADDC(C, T, A);
    else /* if C ≤ B */
        bi_ADDC(C, A, T);

    bi_delete(&T);
}

/* C += A, ADDITION ASSIGNMENT(+=) OPERATOR */
void bi_add_asg(IN OUT bigint **C, IN bigint *A)
{
    bigint *T = NULL;
    bi_assign(&T, *C); /* T ← C */

    bi_ADD(C, T, A);

    bi_delete(&T);
}

/* C -= A, subtraction assignment(+=) operator */
void bi_sub_asg(IN OUT bigint **C, IN bigint *A)
{
    bigint *T = NULL;
    bi_assign(&T, *C); /* T ← C */

    bi_SUB(C, T, A);

    bi_delete(&T);
}