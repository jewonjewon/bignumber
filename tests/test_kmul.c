#include "../includes/bi.h"
#include "../includes/bi_op.h"
#include "../includes/bi_test.h"

// Case 1_1: A = 0 then C = 0 * B
void sub_test_KMUL1_1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_1: A = 0 then C = 0 * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");

    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 1_2: B = 0 then C = A * 0
void sub_test_KMUL1_2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_2: B = 0 then C = A * 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);

        bi_new(&B, 1);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 1_3: A = 0 and B = 0 then C = 0 * 0
void sub_test_KMUL1_3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 1_3: A = 0 and B = 0 then C = 0 * 0 ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        bi_new(&A, 1);
        bi_new(&B, 1);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 2: A = 1 then C = 1 * B
void sub_test_KMUL2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 2: A = 1 then C = 1 * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 3: A = -1 then C = -(1) * B
void sub_test_KMUL3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 3: A = -1 then C = -(1) * B ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        bi_new(&A, 1);
        A->a[0] = 1;
        A->sign = NEGATIVE;

        int sign2 = rand() % 2;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&B, sign2, num2);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 4: B = 1 then C = 1 * A
void sub_test_KMUL4(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 4: B = 1 then C = 1 * A ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_new(&B, 1);
        B->a[0] = 1;

        bi_gen_rand(&A, sign1, num1);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 5: B = -1 then C = -(1) * A
void sub_test_KMUL5(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 5: B = -1 then C = -(1) * A ###\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {
        int sign1 = rand() % 2;
        int num1 = rand() % 0x0f + 1;

        bi_new(&B, 1);
        B->a[0] = 1;
        B->sign = NEGATIVE;

        bi_gen_rand(&A, sign1, num1);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 6_1: wordlen(A) == wordlen(B)
void sub_test_KMUL6_1(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_1: wordlen(A) == wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    for (int j = 0; j < TEST; j++)
    {

        int sign1 = rand() % 2;
        int sign2 = rand() % 2;

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 6_2: wordlen(A) > wordlen(B)
void sub_test_KMUL6_2(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_2: wordlen(A) > wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    int num1 = 0;
    int num2 = 0;

    int sign1 = rand() % 2;
    int sign2 = rand() % 2;

    for (int j = 0; j < TEST; j++)
    {
        do
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;
        } while (num1 >= num2);

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

// Case 6_3: wordlen(A) < wordlen(B)
void sub_test_KMUL6_3(bigint **C, bigint *A, bigint *B, IN int TEST)
{
    printf("print(\"### Case 6_3: wordlen(A) < wordlen(B)\\n\")\n");
    printf("cnt = 0\n");

    int num1 = 0;
    int num2 = 0;

    int sign1 = rand() % 2;
    int sign2 = rand() % 2;

    for (int j = 0; j < TEST; j++)
    {
        do
        {
            num1 = rand() % 0x0f + 2;
            num2 = rand() % 0x0f + 1;
        } while (num1 <= num2);

        bi_gen_rand(&A, sign1, num1);
        bi_gen_rand(&B, sign2, num2);

        bi_kmul(C, A, B);
        sage_show_mul(C, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    printf("print()\n");
    bi_delete(C);
    bi_delete(&A);
    bi_delete(&B);
}

void test_KMUL(IN int TEST)
{
    bigint *A = NULL;
    bigint *B = NULL;
    bigint *C = NULL;

    int Case = 6;

    printf("print(\"### KMUL TEST ###\")\n");

    sub_test_KMUL1_1(&C, A, B, TEST / Case);
    sub_test_KMUL1_2(&C, A, B, TEST / Case);
    sub_test_KMUL1_3(&C, A, B, TEST / Case);
    sub_test_KMUL2(&C, A, B, TEST / Case);
    sub_test_KMUL3(&C, A, B, TEST / Case);
    sub_test_KMUL4(&C, A, B, TEST / Case);
    sub_test_KMUL5(&C, A, B, TEST / Case);
    sub_test_KMUL6_1(&C, A, B, TEST / Case);
    sub_test_KMUL6_2(&C, A, B, TEST / Case);
    sub_test_KMUL6_3(&C, A, B, TEST / Case);
}