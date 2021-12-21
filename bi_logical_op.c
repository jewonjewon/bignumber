#include "bi_local.h"
#include "bi_op.h"

void bi_word_lshift(OUT bigint **A, IN int x)
{
    bi_resize(A, (*A)->wordlen + x);

    // 기존 값 왼쪽으로 워드 시프트
    for (int j = (*A)->wordlen - 1; j >= x; j--)
        (*A)->a[j] = (*A)->a[j - x];

    // 남은 배열 0으로 초기화
    for (int j = x - 1; j >= 0; j--)
        (*A)->a[j] = 0;
}

void bi_word_reduction(OUT bigint **A, IN int x)
{
    return;
}