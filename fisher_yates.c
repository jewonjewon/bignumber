#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST 100

void swap(int *a, int *b)
{
    int t = 0;
    t = *a;
    *a = *b;
    *b = t;
}

void fisher_yates(int *A, int *cnt)
{
    for (int i = TEST - 1; i > 0; i--)
    {
        int j = rand() % i;
        swap(&A[i], &A[j]);
        *cnt = *cnt + 1;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int A[TEST] = {
        0,
    };
    int cnt = 1;

    // 배열안에 원소 셋팅
    for (int j = 0; j < TEST; j++)
        A[j] = j + 1;

    fisher_yates(A, &cnt);

    // 배열 원소 잘 섞였나 확인
    for (int j = 0; j < TEST; j++)
    {
        printf("%3d ", A[j]);
        if (j % 10 == 9)
            printf("\n");
    }
    printf("\n");

    printf("cnt = %d\n", cnt);

    return 0;
}
