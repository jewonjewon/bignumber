#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define check printf("?????\n")

#define IN  // function input
#define OUT // function output
#define CONSTATNT

#define NON_NEGATIVE 0
#define NEGATIVE 1

#define and &&
#define or ||

#define w 64 // w: 워드의 크기 지정

#if w == 64 // 64비트
typedef unsigned long long word;
#elif w == 32 // 32비트
typedef unsigned int word;
#elif w == 8  // 8비트
typedef unsigned char word;
#endif

// bigint 구조체 설정(sign= 부호, wordlen= 워드길이, a=배열)
typedef struct
{
    int sign;
    int wordlen;
    word *a;
} bigint;

void test();
/* == == == == == BASIC FUNCTION == == == == == */
void bi_delete(IN OUT bigint **arr);
void bi_new(IN OUT bigint **arr, IN int wordlen);
void bi_refine(bigint *arr);
void bi_assign(IN OUT bigint **y, IN bigint *x);

void bi_print(bigint *arr);

// bi_assign(IN OUT bigint **y, IN bigint *x);