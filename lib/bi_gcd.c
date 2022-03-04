#include "../includes/bi.h"
#include "../includes/bi_op.h"

/* 유클리드 알고리듬을 이용한 gcd(A, B) 계산 함수 */
void bi_ea_rcs(bigint **C, bigint *A, bigint *B)
{
    if (bi_is_zero(B) == true)
    {
        bi_assign(C, A); /* if B = 0, then gcd(A, B) = A */
        return;
    }

    bigint *T = NULL; /* 임시 변수 */
    bi_assign(&T, A);

    bi_mod_asg(&T, B);  /* T %= B */
    bi_ea_rcs(C, B, T); /* bi_ea_rcs(C, B, A%B) */

    bi_delete(&T);
}

void bi_ea_itr(bigint **C, bigint *A, bigint *B)
{
    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bigint *T2 = NULL;

    bi_assign(&T0, A);
    bi_assign(&T1, B);

    while (bi_is_zero(T1) != true)
    {
        bi_assign(&T2, T0);
        bi_assign(&T0, T1);
        bi_mod_asg(&T2, T1);
        bi_assign(&T1, T2);
    }

    bi_assign(C, T0); /* return T0 */

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&T2);
}

void bi_ea_bin_itr(bigint **C, bigint *A, bigint *B)
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

    while (bi_is_zero(T1) == false)
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

    bi_kmul(C, T0, T2);

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&T2);
}

void bi_eea_bin_itr(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *a = NULL;
    bigint *b = NULL;

    bi_assign(&a, A);
    bi_assign(&b, B);

    bigint *T0 = NULL;
    bigint *T1 = NULL;
    bigint *T2 = NULL;
    bigint *U0 = NULL;
    bigint *V0 = NULL;
    bigint *U1 = NULL;
    bigint *V1 = NULL;

    bi_assign(&T0, a);
    bi_assign(&T1, b);
    bi_set_one(&T2);

    while ((T0->a[0] & 0x1) == 0 and (T1->a[0] & 0x1) == 0)
    {
        bi_rshift(&T0, 1);
        bi_rshift(&T1, 1);
        bi_lshift(&T2, 1);
    }

    bi_assign(&a, T0);
    bi_assign(&b, T1);

    bi_set_one(&U0);
    bi_set_zero(&V0);

    bi_set_zero(&U1);
    bi_set_one(&V1);

    while (bi_is_zero(T0) == false)
    {
        while ((T0->a[0] & 0x1) == 0) /* T0 is even? */
        {
            bi_rshift(&T0, 1);

            if ((U0->a[0] & 0x1) == 0 and (V0->a[0] & 0x1) == 0)
            {
                bi_rshift(&U0, 1);
                bi_rshift(&V0, 1);
            }
            else
            {
                bi_add_asg(&U0, b);
                bi_rshift(&U0, 1);

                bi_sub_asg(&V0, a);
                bi_rshift(&V0, 1);
            }
            // printf("# T0 = ");
            // bi_print(T0);
            // printf("U0 = ");
            // bi_print(U0);
            // printf("V0 = ");
            // bi_print(V0);
            // newline;
        }
        while ((T1->a[0] & 0x1) == 0) /* T1 is even? */
        {
            bi_rshift(&T1, 1);

            if ((U1->a[0] & 0x1) == 0 and (V1->a[0] & 0x1) == 0)
            {
                bi_rshift(&U1, 1);
                bi_rshift(&V1, 1);
            }
            else
            {
                bi_add_asg(&U1, b);
                bi_rshift(&U1, 1);

                bi_sub_asg(&V1, a);
                bi_rshift(&V1, 1);
            }
            // printf("# T1 = ");
            // bi_print(T1);
            // printf("U1 = ");
            // bi_print(U1);
            // printf("V1 = ");
            // bi_print(V1);
            // newline;
        }
        if ((bi_cmp(T0, T1) == 1) or (bi_cmp(T0, T1) == 0)) /* T0 ≥ T1 ? */
        {
            // printf("#if\n");
            bi_sub_asg(&T0, T1);
            bi_sub_asg(&U0, U1);
            bi_sub_asg(&V0, V1);
        }
        else
        {
            // printf("#else\n");
            bi_sub_asg(&T1, T0);
            bi_sub_asg(&U1, U0);
            bi_sub_asg(&V1, V0);
        }
    }
    bigint *rr = NULL;
    bi_assign(&rr, U1);

    bigint *tmp1 = NULL;
    bigint *tmp2 = NULL;
    bigint *tmp3 = NULL;
    bigint *tmp4 = NULL;
    bi_kmul(&tmp1, a, U1);
    bi_kmul(&tmp2, b, V1);

    bi_add(&tmp3, tmp1, tmp2);
    bi_kmul(&tmp4, T1, T2);

    printf("%d\n", bi_cmp(tmp4, tmp3));
    bi_assign(C, U1);

    // printf("%d\n", bi_compare_abs(C, B));

    bi_delete(&T0);
    bi_delete(&T1);
    bi_delete(&T2);

    bi_delete(&U0);
    bi_delete(&U1);

    bi_delete(&V0);
    bi_delete(&V1);

    bi_delete(&a);
    bi_delete(&b);
    // bi_delete(&rr);
}

void bi_eea_itr(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    if (bi_is_zero(A) == true or bi_is_zero(B))
    {
        bi_set_zero(C);
        return;
    }

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
        bi_div(&Q, &R, T0, T1); /* Q, R = T0 / T1, T0 % T1 */

        bi_assign(&T0, T1);
        bi_assign(&T1, R);

        /* U2 = U0 - Q*U1 */
        bi_kmul_asg(&Q, U1);
        bi_sub(&U2, U0, Q);

        /* V2 = V0 - Q*V1 */
        bi_kmul_asg(&Q, V1);
        bi_sub(&V2, V0, Q);

        bi_assign(&U0, U1);
        bi_assign(&V0, V1);

        bi_assign(&U1, U2);
        bi_assign(&V1, V2);
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

void lehmer_gcd(OUT bigint **C, IN bigint *A, IN bigint *B)
{
    bigint *AA = NULL;
    bigint *BB = NULL;

    bigint *x = NULL;
    bigint *y = NULL;

    bigint *a = NULL;
    bigint *b = NULL;
    bigint *c = NULL;
    bigint *d = NULL;

    /* ㄹㅇ 임시 변수*/
    bigint *t0 = NULL; /* t0 = y + C  */
    bigint *t1 = NULL; /* t1 = y + D  */
    bigint *t2 = NULL; /* t2 = x + A  */
    bigint *t3 = NULL; /* t3 = x + B  */
    bigint *q = NULL;
    bigint *qq = NULL;

    bigint *t = NULL;
    bigint *T = NULL;
    bigint *u = NULL;

    if (bi_cmp(A, B) == -1)
    {
        bi_assign(&AA, B);
        bi_assign(&BB, A);
        printf("#오류 떠야함\n");
    }
    else
    {
        bi_assign(&AA, A);
        bi_assign(&BB, B);
    }

    bi_assign(&x, AA);
    bi_assign(&y, BB);

    while (BB->wordlen > 1)
    {
        int size = bi_bit_cnt(AA) - w;

        bi_rshift(&x, size);
        bi_rshift(&y, size);

        /* a, b, c, d = 1, 0, 0, 1 */
        bi_set_one(&a);
        bi_set_zero(&b);
        bi_set_zero(&c);
        bi_set_one(&d);

        bi_add(&t0, y, c);
        bi_add(&t1, y, d);

        while (1)
        {
            /* y + C == 0 or y + D == 0 */
            if (bi_is_zero(t0) == true or bi_is_zero(t1) == true)
            {
                break;
            }

            bi_add(&t2, x, b);
            bi_add(&t3, x, a);

            bi_div_q(&q, t2, t0);
            bi_div_q(&qq, t3, t1);

            if (bi_cmp(q, qq) != 0)
                break;

            /* 1. c ← a - q*c  */
            bi_assign(&t0, q);
            bi_kmul_asg(&t0, c);
            bi_sub(&t, a, t0);

            bi_assign(&a, c); /* 2. a ← c */

            bi_assign(&c, t); /* 3. c ← t */

            /* 4. d ← b - q*d  */
            bi_assign(&t0, q);
            bi_kmul_asg(&t0, d);
            bi_sub(&t, b, t0);

            bi_assign(&b, d); /* 5. b ← d */

            bi_assign(&d, t); /* 6. d ← t */

            /* 1. t ← x - q*y  */
            bi_assign(&t0, q);
            bi_kmul_asg(&t0, y);
            bi_sub(&t, x, t0);

            bi_assign(&x, y); /* 2. x ← y */
            bi_assign(&y, t); /* 2. y ← t */
        }

        if (bi_is_zero(b) == true)
        {
            bi_assign(&t0, AA);
            bi_assign(&AA, BB);
            bi_mod_asg(&t0, BB);
            bi_assign(&BB, t0);
        }
        else
        {
            bi_kmul(&t0, a, AA);
            bi_kmul(&t1, b, BB);
            bi_add(&T, t0, t1);

            bi_kmul(&t0, c, AA);
            bi_kmul(&t1, d, BB);
            bi_add(&u, t0, t1);
            bi_assign(&AA, T);
            bi_assign(&BB, u);
        }
    }

    bi_ea_itr(C, AA, BB);

    bi_delete(&x);
    bi_delete(&y);
    bi_delete(&a);
    bi_delete(&b);
    bi_delete(&c);
    bi_delete(&d);
    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&t2);
    bi_delete(&t3);
    bi_delete(&q);
    bi_delete(&qq);
    bi_delete(&AA);
    bi_delete(&BB);
    bi_delete(&t);
}

void bi_eea_rcs(bigint **d, bigint **alpha, bigint **beta, bigint *a, bigint *b)
{
    bigint *T = NULL;
    bi_assign(&T, b);

    if (bi_is_zero(T) == true)
    {
        bi_assign(d, a);
        bi_set_one(alpha);
        bi_set_zero(beta);
    }

    bi_assign(&T, a);

    bi_mod_asg(&T, b);

    if (bi_is_zero(b) == true)
        return;

    bi_eea_rcs(d, alpha, beta, b, T);

    bi_print("a", a);
    bi_print("b", b);

    bigint *t0 = NULL;
    bigint *t1 = NULL;
    bigint *t2 = NULL;

    bi_assign(&t0, *d);
    bi_assign(&t1, *beta);

    bi_div_asg(&T, b);
    bi_kmul_asg(&T, *beta);
    bi_sub_asg(alpha, T);

    bi_assign(&t2, T);

    bi_print("t0", t0);
    bi_print("t1", t1);
    bi_print("t2", t2);

    bi_assign(alpha, t1);

    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&t2);
    bi_delete(&T);
}
