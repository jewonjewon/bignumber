#include "../includes/bi.h"
#include "../includes/bi_op.h"

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
    word A0 = A & HALF_MASK;

    word C1 = A1 * A1;
    word C0 = A0 * A0;

    // C = C1 || C0
    (*C)->a[1] = C1;
    (*C)->a[0] = C0;

    bigint *T = NULL;
    bi_new(&T, 2);

    bi_MUL_AB(&T, A0, A1);
    bi_lshift(&T, w / 2 + 1);
    bi_addc_asg(C, T);

    bi_delete(&T);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_squ_core(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
 * 다중 워드 2개를 입력받아 제곱 연산 수행 후 최대 wordlen(A) + wordlen(B) 워드 크기의 출력값을 반환하는 함수.
 * 다중 워드 제곱이므로 결과값 C의 최대 워드 길이는 wordlen(A) + wordlen(B) 워드.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_squ_core(출력: bigint형 배열, 입력: 다중 워드, 입력: 다중 워드)
void bi_squ_core(OUT bigint **C, IN bigint *A)
{
    // bi_new(C, 2 * A->wordlen);
    int n = A->wordlen; /* n is wordlen(A) */

    bigint *C0 = NULL;
    bigint *C1 = NULL;

    bi_set_zero(&C0);
    bi_set_zero(&C1);

    bigint *T0 = NULL;
    bigint *T1 = NULL;

    for (int j = 0; j < n; j++)
    {
        bi_SQU_A(&T0, A->a[j]);
        bi_word_lshift(&T0, 2 * j); /* T0 <<= 2jw  */
        bi_addc_asg(&C0, T0);       /* C0 += T0 */

        for (int i = j + 1; i < n; i++)
        {
            bi_MUL_AB(&T1, A->a[j], A->a[i]);
            bi_word_lshift(&T1, i + j); /* T1 <<= 2jw  */
            bi_addc_asg(&C1, T1);       /* C1 += T1 */
        }
    }
    bi_lshift(&C1, 1);
    bi_add(C, C0, C1);

    bi_delete(&C0);
    bi_delete(&C1);
    bi_delete(&T0);
    bi_delete(&T1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * bi_squ(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
 * 임의의 정수 A와 B를 입력받아 SQUC()함수를 통한 제곱 연산 수행 후 결과값 C를 반환하는 함수.
 * Case 별로 제곱 연산 수행
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// bi_squ(출력: bigint형 배열, 입력: 임의의 정수, 입력: 임의의 정수)
void bi_squ(OUT bigint **C, IN bigint *A)
{
    // Case 1: A = 0 or A = 1 or A = -1
    if (bi_is_zero(A) == true or bi_is_one(A) == true or bi_is_minus_one(A) == true)
    {
        bi_assign(C, A);
        bi_abs(*C);
        return;
    }

    // Case 2: Otherwise
    bi_squ_core(C, A);
}

void bi_squ_asg(OUT bigint **C)
{
    bigint *T = NULL;

    bi_assign(&T, *C);
    bi_squ(C, T);

    bi_delete(&T);
}

void bi_ksqu_core(OUT bigint **C, IN bigint *A)
{
    int sign_A = A->sign;

    int flag = 3;

    if (flag >= A->wordlen)
    {
        bi_squ_core(C, A);
        return;
    }

    int l = (A->wordlen + 1) >> 1;

    bigint *A1 = NULL;
    bigint *A0 = NULL;

    bi_abs(A);
    bi_assign(&A1, A);
    bi_assign(&A0, A);

    bi_word_rshift(&A1, l);
    bi_word_reduction(&A0, l);

    bigint *T1 = NULL;
    bigint *T0 = NULL;

    bi_ksqu_core(&T1, A1);
    bi_ksqu_core(&T0, A0);

    bigint *R = NULL;

    bi_assign(&R, T1);
    bi_word_lshift(&R, 2 * l);
    bi_add_asg(&R, T0);

    bigint *S = NULL;
    bi_kmul_core(&S, A1, A0);
    bi_lshift(&S, l * w + 1);
    bi_add_core(C, R, S);

    A->sign = sign_A;

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&T1);
    bi_delete(&T0);
    bi_delete(&R);
    bi_delete(&S);
}

void bi_ksqu(OUT bigint **C, IN bigint *A)
{
    // Case 1: A = 0 or A = 1 or A = -1
    if (bi_is_zero(A) == true or bi_is_one(A) == true or bi_is_minus_one(A) == true)
    {
        bi_assign(C, A);
        (*C)->sign = NON_NEGATIVE;
        return;
    }

    // Case 2: Otherwise
    bi_ksqu_core(C, A);
}

void bi_ksqu_asg(OUT bigint **C)
{
    bigint *T = NULL;
    bi_assign(&T, *C);

    bi_ksqu(C, T);

    bi_delete(&T);
}