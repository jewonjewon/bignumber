#include "bi_local.h"
#include "bi_op.h"

void bi_MUL_AB(OUT bigint **C, IN word A, IN word B)
{
    // 단일 워드 곱셈이므로 결과값의 길이는 최대 2워드
    // 이 부분 new 해줘도 안해줘도 둘다 컴파일 되는데 어떤거 쓰는지 궁금
    // bi_new(C, 2);

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

    (*C)->a[1] = C1;
    (*C)->a[0] = C0;
}

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