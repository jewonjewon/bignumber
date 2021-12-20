#ifndef __BI_OPERATION_H__
#define __BI_OPERATION_H__

#include "bi_local.h"

void bi_ADD_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_ADDC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_ADD(OUT bigint **C, IN bigint *A, IN bigint *B);

void bi_SUB_ABc(OUT word *C, IN word A, IN word B, IN OUT int *c);
void bi_SUBC(OUT bigint **C, IN bigint *A, IN bigint *B);
void bi_SUB(OUT bigint **C, IN bigint *A, IN bigint *B);

#endif