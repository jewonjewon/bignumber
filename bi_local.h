#ifndef __BI_LOCAL_H__
#define __BI_LOCAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

#define w 32 // w: 워드의 크기 지정

#if w == 64 // 64비트
typedef unsigned long long word;
#define MASK (0xffffffffffffffff)
#define W (0xffffffffffffffff)
#elif w == 32 // 32비트
typedef unsigned int word;
#define MASK (0xffffffff)
#define W (0xffffffff)
#elif w == 8 // 8비트
typedef unsigned char word;
#define MASK (0xff)
#define W (0xff)
#endif

// bigint 구조체 설정(sign= 부호, wordlen= 워드길이, a=배열)
typedef struct
{
    int sign;
    int wordlen;
    word *a;
} bigint;

/* == == == == == BASIC FUNCTION == == == == == */
void bi_delete(IN OUT bigint **A);
void bi_new(IN OUT bigint **A, IN int wordlen);
void bi_refine(bigint *A);
void bi_assign(IN OUT bigint **y, IN bigint *x);
void bi_resize(IN OUT bigint **A, IN int wordlen);
void bi_init(IN OUT bigint **A);

void bi_print(bigint *A);

void arr_rand(word *dst, IN int wordlen);
void bi_gen_rand(OUT bigint **A, IN int sign, IN int wordlen);

void bi_set_one(OUT bigint **A);
void bi_set_zero(OUT bigint **A);

int bi_is_zero(IN bigint *A);
int bi_is_one(IN bigint *A);
int bi_is_minus_one(IN bigint *A);

int bi_compare_abs(IN bigint *A, IN bigint *B);
int bi_cmp(IN bigint *A, IN bigint *B);

void bi_abs(IN bigint *A);
void bi_flip_sign(IN bigint *A);

int bi_min(IN int a, IN int b);
int bi_max(IN int a, IN int b);

void bi_attach(bigint **C, bigint *A, bigint *B);

#endif