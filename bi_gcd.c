#include "bi.h"
#include "bi_op.h"

void bi_gcd_bin(bigint **C, bigint *A, bigint *B)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bigint *T2 = NULL;

    bi_assign(&T0, A);
    bi_assign(&T1, B);
    bi_set_one(&T2);

    while (((T0->a[0] & 0x1) == 0) and ((T1->a[0] & 0x1) == 0))
    {
        bi_rshift(&T0, 1);
        bi_rshift(&T1, 1);
        bi_lshift(&T2, 1);
    }

    while (bi_is_zero(T1) == 0)
    {
        while ((T0->a[0] & 0x1) == 0)
        {
            bi_rshift(&T0, 1);
        }
        while ((T1->a[0] & 0x1) == 0)
        {
            bi_rshift(&T1, 1);
        }
        if ((bi_cmp(T1, T0) == 1) or (bi_cmp(T1, T0) == 0)) /* if T1 ≥ T0 */
        {
            bi_sub_asg(&T1, T0);
        }
        else
        {
            bi_sub_asg(&T0, T1);
        }
    }

    bi_KMUL(C, T0, T2);
    // bi_MUL(C, T0, T2);

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&T2);
}

void bi_xgcd_bin(bigint **C, bigint *A, bigint *B)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bigint *T2 = NULL;

    bi_assign(&T0, A);
    bi_assign(&T1, B);
    bi_set_one(&T2);

    bi_assign(&A, T0);
    bi_assign(&B, T1);

    bigint *U0 = NULL;
    bigint *V0 = NULL;

    bi_set_one(&U0);
    bi_set_zero(&U0);

    bigint *U1 = NULL;
    bigint *V1 = NULL;

    bi_set_zero(&U1);
    bi_set_one(&V1);

    while (bi_is_zero(T0) == true)
    {
        while ((T0->a[0] & 0x1) == 0)
        {
            bi_rshift(&T0, 1);
            if ((U0->a[0] & 0x1) == 0 and (V0->a[0] & 0x1) == 0)
            {
                bi_rshift(&U0, 1);
                bi_rshift(&V0, 1);
            }
            else
            {
                bi_ADD(&U0, U0, B);
                bi_rshift(&U0, 1);

                bi_SUB(&V0, V0, A);
                bi_rshift(&V0, 1);
            }
        }
        while ((T1->a[0] & 0x1) == 0)
        {
            bi_rshift(&T1, 1);
            if ((U1->a[0] & 0x1) == 0 and (V1->a[0] & 0x1) == 0)
            {
                bi_rshift(&U1, 1);
                bi_rshift(&V1, 1);
            }
            else
            {
                bi_sub_asg(&U1, A);
                bi_rshift(&U1, 1);

                bi_sub_asg(&V1, A);
                bi_rshift(&V1, 1);
            }
        }
        if ((bi_cmp(T0, T1) == 1) or (bi_cmp(T0, T1) == 0))
        {
            bi_sub_asg(&T0, T1);
            bi_sub_asg(&U0, U1);
            bi_sub_asg(&V0, V1);
        }
        else
        {
            bi_SUB(&T1, T1, T0);
            bi_SUB(&U1, U1, U0);
            bi_SUB(&V1, V1, V0);
        }
    }
    bi_assign(C, U1);

    // printf("T0 = ");
    // bi_print(T0);
    // printf("T1 = ");
    // bi_print(T1);
    // printf("T2 = ");
    // bi_print(T2);

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&T2);

    bi_delete(&U0);
    bi_delete(&U1);

    bi_delete(&V0);
    bi_delete(&V1);
}

// void eea_rec(bigint **C, bigint *A, bigint *B)
// {
//     if(bi_is_zero(B) == true)
// }

void bi_eea_itr(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bigint *U0 = NULL;
    bigint *V0 = NULL;
    bigint *U1 = NULL;
    bigint *V1 = NULL;
    bigint *U2 = NULL;
    bigint *V2 = NULL;

    bi_assign(&T0, A);
    bi_assign(&T1, B);

    bi_set_one(&U0);
    bi_set_zero(&V0);

    bi_set_zero(&U1);
    bi_set_one(&V1);

    bigint *Q = NULL;
    bigint *R = NULL;

    while (bi_is_zero(T1) != true) /* T1 is not zero */
    {
        bi_DIV(&Q, &R, T0, T1); /* Q, R = T0 / T1, T0 % T1 */

        bi_assign(&T0, T1);
        bi_assign(&T1, R);

        /* U2 = U0 - Q*U1 */
        bi_mul_asg(&Q, U1);
        bi_SUB(&U2, U0, Q);

        /* V2 = V0 - Q*V1 */
        bi_mul_asg(&Q, V1);
        bi_SUB(&V2, V0, Q);

        bi_assign(&U0, U1);
        bi_assign(&V0, V1);

        bi_assign(&U1, U2);
        bi_assign(&V1, V2);

        // bi_print(T0);
        // printf(" = ");
        // bi_print(A);
        // printf(" * ");
        // bi_print(U0);
        // printf(" + ");
        // bi_print(B);
        // printf(" * ");
        // bi_print(V0);
        // newline;
    }
    bi_assign(C, U0);

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&U0);
    bi_delete(&U1);
    bi_delete(&U2);
    bi_delete(&V0);
    bi_delete(&V1);
    bi_delete(&V2);
    bi_delete(&Q);
    bi_delete(&R);
}