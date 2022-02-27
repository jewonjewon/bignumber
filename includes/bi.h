#ifndef _INCLUDE_BI_H
#define _INCLUDE_BI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define w 64 /* w: 워드 크기 지정 */

#define check printf("#?????\n")
#define newline printf("\n")

#define IN  // function input
#define OUT // function output
#define CONSTATNT

#define NON_NEGATIVE 0
#define NEGATIVE 1

#define and &&
#define or ||

#define ZEROLIZE

#if w == 64 // 64비트
typedef unsigned long long word;
#define MASK (0xffffffffffffffff)
#define HALF_MASK (0xffffffff) // 32비트 마스크
#define W (0xffffffffffffffff)
#elif w == 32 // 32비트
typedef unsigned int word;
#define MASK (0xffffffff)
#define HALF_MASK (0xffff) // 16비트 마스크
#define W (0xffffffff)
#elif w == 8 // 8비트
typedef unsigned char word;
#define MASK (0xff)
#define HALF_MASK (0xf) // 4비트 마스크
#define W (0xff)
#endif

typedef struct
{
    int sign;    /* 부호 */
    int wordlen; /* 워드길이 */
    word *a;     /* 배열 */
} bigint;

/* == == == == == BASIC FUNCTION == == == == == */
void bi_delete(IN OUT bigint **A);
void bi_new(IN OUT bigint **A, IN int wordlen);
void bi_refine(bigint *A);
void bi_assign(IN OUT bigint **y, IN bigint *x);
void bi_resize(IN OUT bigint **A, IN int wordlen);

void bi_init(IN OUT bigint **A);

void bi_print(char *str, bigint *A);

void arr_rand(word *dst, IN int wordlen);
void bi_gen_rand(OUT bigint **A, IN int sign, IN int wordlen);

void bi_set_one(OUT bigint **A);
void bi_set_zero(OUT bigint **A);

int bi_is_zero(IN bigint *A);
int bi_is_one(IN bigint *A);
int bi_is_minus_one(IN bigint *A);
int bi_is_two(IN bigint *A);
int bi_is_even(IN bigint *A);

int bi_compare_abs(IN bigint *A, IN bigint *B);
int bi_cmp(IN bigint *A, IN bigint *B);

void bi_abs(IN bigint *A);
void bi_flip_sign(IN bigint *A);

int bi_min(IN int a, IN int b);
int bi_max(IN int a, IN int b);

#endif