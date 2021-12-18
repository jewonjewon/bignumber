#include "bi_local.h"

void bi_delete(IN OUT bigint **arr)
{
    if (*arr == NULL)
        return;

#ifdef ZEROLIZE
    // 입력 배열 초기화
    array_init((*arr)->a, (*arr)->wordlen);
#endif

    free((*arr)->a);
    free(*arr);
    *arr = NULL;
}
// bigint형 배열 생성(부호= NON_NEGATIVE, 워드길이= wordlen, 배열= 0)
void bi_new(IN OUT bigint **arr, IN int wordlen)
{
    // 입력받은 배열에 어떠한 값이 저장되어있는 경우 free 후 새롭게 할당
    if (*arr != NULL)
        bi_delete(arr);

    *arr = (bigint *)malloc(sizeof(bigint));
    (*arr)->sign = NON_NEGATIVE;
    (*arr)->wordlen = wordlen;
    (*arr)->a = (word *)calloc(wordlen, sizeof(word));
}

void bi_refine(bigint *arr)
{
    if (arr == NULL)
        bi_delete(arr);

    int new_wordlen = arr->wordlen;

    while (new_wordlen > 1)
    {
        if (arr->a[new_wordlen - 1] != 0)
            break;
        new_wordlen--;
    }

    if (arr->wordlen != new_wordlen)
    {
        arr->wordlen = new_wordlen;
        arr->a = (word *)realloc(arr->a, sizeof(word) * new_wordlen);
    }

    if ((arr->wordlen == 1) and (arr->a[0] == 0))
        arr->sign = NON_NEGATIVE;
}

void test()
{
    printf("hello World!\n");
    printf("출력 확인용");
}