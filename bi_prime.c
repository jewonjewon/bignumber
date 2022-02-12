#include "bi.h"
#include "bi_op.h"
#include "bi_test.h"
#include "bi_rand.h"
#include "benchmark.h"

/* C-- */
void bi_sub_minus_one(bigint **A)
{

    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bi_set_one(&T0);    /* T0 = 1 */
    bi_assign(&T1, *A); /* T1 = A */

    bi_SUB(A, T1, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}
// end sub_minus_one

// /* C -= a , a in [0,W) i.e. a is word */
void bi_sub_minus_a(IN OUT bigint **A, IN word a)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;

    bi_new(&T0, 1);
    T0->a[0] = a; /* T0 = 2 */

    bi_assign(&T1, *A); /* T1 = A */

    bi_SUB(A, T1, T0);

    bi_delete(&T0);
    bi_delete(&T1);
}
// // end sub_minus_two

int bi_get_l(bigint *a)
{
    int cnt = 0;

    bigint *T = NULL;
    bi_assign(&T, a);

    while (1)
    {
        if ((T->a[0] & 0x1) == 0)
        {
            bi_rshift(&T, 1);
            cnt++;
        }
        else
        {
            bi_delete(&T);
            return cnt;
        }
    }
}
// end bi_get_l()

/* A(판별하고자 하는 정수),  */
int bi_is_composite(IN bigint *n, IN bigint *q, IN int l, IN bigint *a)
{
    bigint *t = NULL;
    bigint *r = NULL;
    bigint *nn = NULL;

    bi_mod_l2r(&t, a, q, n);
    bi_assign(&nn, n);
    bi_div_r(&r, t, n);

    if (bi_is_one(r) == true)
        return false; /* NOT COMPOSITE */

    for (int j = 0; j < l; j++)
    {
        bi_sub_minus_a(&nn, 1);
        // bi_sub_minus_one(&nn);

        if (bi_cmp(t, nn) == 0)
        {
            bi_delete(&nn);
            bi_delete(&t);
            bi_delete(&r);
            return false; /* NOT COMPOSITE */
        }
        bi_ksqu_asg(&t);
        bi_mod_asg(&t, n);
    }
    bi_delete(&nn);
    bi_delete(&t);
    bi_delete(&r);

    return true; /* COMPOSITE */
}
// end bi_is_composite()

/* n: 판별하고자 하는 정수, k: 시행 횟수 , use miller-rabin primallity test*/
int bi_is_prime(bigint *n, int k)
{
    if (bi_is_even(n) == true) /* n is even, n is NOT prime */
        return false;

    if (bi_is_one(n) == true or bi_is_zero(n) == true) /* n is 1 or n is 0, n is NOT prime */
        return false;

    bigint *q = NULL;
    bigint *t = NULL;
    bigint *d = NULL;
    bigint *a = NULL;

    bi_assign(&t, n);      /* t ← n */
    bi_sub_minus_a(&t, 1); /* t ← n-1 */

    int l = bi_get_l(t);

    bi_assign(&q, t);
    bi_rshift(&q, 1); /* q ← (A-1) >> 1 */

    bi_sub_minus_a(&t, 1);

    while (k > 0) /* k번 시행 */
    {
        do
        {
            bi_SPDM(&a, t); /* Choose random bit a in [2, a - 2)*/

        } while (bi_is_zero(a) == true or bi_is_one(a) == true);

        bi_ea_bin_itr(&d, a, n);

        if (bi_is_one(d) == false)
            return false; /* n is NOT prime */

        if (bi_is_composite(n, q, l, a) == true)
            return false; /* n is NOT prime */
        k--;
    }

    bi_delete(&q);
    bi_delete(&t);
    bi_delete(&a);
    bi_delete(&d);

    return true; /* n is prime */
}
// end bi_is_prime()

void bi_gen_prime(bigint **p, int bitlen)
{
    int k = 40; /* k: 시행횟수 */
    int x = 0;
    int j = 0;
    int len = bitlen / w;

    bigint *n = NULL;

    while (1)
    {
        bi_gen_rand(&n, NON_NEGATIVE, len);

        x = bi_is_prime(n, k);

        if (x == 1) /* x is 1 then x is prime */
        {
            // printf("n = ");
            // bi_print(n);
            bi_assign(p, n);
            bi_delete(&n);
            break;
        }
    }
}