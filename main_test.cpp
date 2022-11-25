#include <stdio.h>
#include <iostream>

#include "includes/bi_util.h"
#include "includes/bi.h"
#include "includes/bi_op.h"

/* Return user CPU time measured in milliseconds. (1/1000 sec.)  */
#if !defined(__sun) && (defined(USG) || defined(__SVR4) || defined(_UNICOS) || defined(__hpux))
#include <time.h>

int cputime()
{
    return (int)((double)clock() * 1000 / CLOCKS_PER_SEC);
}
#else
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

// user CPU time measured in milliseconds
int cputime()
{
    struct rusage rus;

    getrusage(0, &rus);
    return rus.ru_utime.tv_sec * 1000 + rus.ru_utime.tv_usec / 1000;
}
#endif

#define CHECK_TIME(t, func)                     \
    do                                          \
    {                                           \
        long int __t0, __times, __t, __tmp;     \
        __times = 1;                            \
        {                                       \
            func;                               \
        }                                       \
        do                                      \
        {                                       \
            __times <<= 1;                      \
            __t0 = cputime();                   \
            for (__t = 0; __t < __times; __t++) \
            {                                   \
                func;                           \
            }                                   \
            __tmp = cputime() - __t0;           \
        } while (__tmp < 250);                  \
        (t) = (double)__tmp / __times;          \
        printf("#time = %f\n\n", t);            \
    } while (0)

int main()
{
    double millisec;

    const char *str1 = "2524355355523523";
    const char *str2 = "523454";
    const char *str3 = "212343124234324334321413244213";

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;
    bigint *D = NULL;

    bi_new(&A, 5);
    bi_new(&B, 5);
    bi_new(&C, 20);
    bi_new(&D, 5);

    hexstrToBigint(A->a, str1);
    hexstrToBigint(B->a, str2);
    hexstrToBigint(D->a, str3);

    bi_gen_rand(&A, NON_NEGATIVE, 5);
    bi_gen_rand(&B, NON_NEGATIVE, 5);
    bi_gen_rand(&D, NON_NEGATIVE, 5);

    bi_refine(A);
    bi_refine(B);
    bi_refine(D);

    bi_print("A", A);
    bi_print("B", B);
    bi_print("D", D);

    bi_mod_exp_l2r(&C, A, B, D);
    CHECK_TIME(millisec, bi_mod_exp_l2r(&C, A, B, D));
    CHECK_TIME(millisec, bi_add(&C, A, B));

    bi_print("C", C);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
    bi_delete(&D);

    return 0;
}