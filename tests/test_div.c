#include "../includes/bi.h"
#include "../includes/bi_op.h"

void sage_show_div(bigint **Q, bigint **R, bigint *A, bigint *B, int j)
{
    bi_print("A", A);
    bi_print("B", B);
    bi_print("Q", *Q);
    bi_print("R", *R);

    printf("if ((Q != A // B) and (Q != A %% B)):\n");
    printf("    print(\"{} : {}\".format(%d, A // B == Q)) #%d\n", j, j);
    printf("    print(\"{} : {}\".format(%d, A %% B == R)) #%d\n", j, j);
    printf("    cnt = cnt + 1\n");
}

// void test_bi_long_div_2word(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;

//     for (int j = 0; j < TEST; j++)
//     {
//         bi_gen_rand(&A, NON_NEGATIVE, 2);
//         bi_gen_rand(&B, NON_NEGATIVE, 1);

//         if (A->a[1] < B->a[0])
//             printf("A1 ≥ B\n");

//         Q = bi_long_div_2word(A, B->a[0]);

//     //         bi_print("A", A);
//     //         bi_print("B", B);
//         printf("Q = %#llx\n", Q);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(hex(A//B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
// }

// void test_DIVCC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {
//         // int num1 = rand() % 0x0f + 2;
//         // int num2 = rand() % 0x0f + 1;
//         // while (1)
//         // {
//         //     bi_gen_rand(&A, NON_NEGATIVE, num1);
//         //     bi_gen_rand(&B, NON_NEGATIVE, num2);
//         //     if (bi_cmp(B, A) == -1 and bi_cmp(B, A) == 0)
//         //     {
//         //         bigint *T = NULL;
//         //         bi_new(&T, 1);
//         //         bi_assign(&T, B);
//         //         bi_word_lshift(&T, 1);
//         //         if (bi_cmp(A, T) == -1)
//         //             if (B->a[B->wordlen - 1] >= pow2(w - 1))
//         //             {
//         //                 printf("DIVCC 입력 조건 0 < B ≤ A < BW, B_{m-1} ≥ 2^{w-1} 성립!\n");
//         //                 bi_delete(&T);
//         //                 break;
//         //             }
//         //         bi_delete(&T);
//         //     }
//         //     check;
//         // }

//         int num1 = rand() % 0x0f + 1;
//         // int num2 = rand() % 0x0f + 1;
//         // while (num1 < num2)
//         // {

//         num1 = rand() % 0x0f + 1;
//         // num2 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num1 - 1);
//         // }

//         if (bi_cmp(B, A) == -1 and bi_cmp(B, A) == 0)
//         {
//             bigint *T = NULL;
//             bi_new(&T, 1);
//             bi_assign(&T, B);
//             bi_word_lshift(&T, 1);
//             if (bi_cmp(A, T) == -1)
//                 if (B->a[B->wordlen - 1] >= pow2(w - 1))
//                 {
//                     printf("DIVCC 입력 조건 0 < B ≤ A < BW, B_{m-1} ≥ 2^{w-1} 성립!\n");
//                     bi_delete(&T);
//                     break;
//                 }
//             bi_delete(&T);
//         }

//         bi_DIVCC(&Q, &R, A, B);

//     //         bi_print("A", A);
//
//         printf("Q = %#llx\n", "x", Q);
//
//         bi_print("R", R);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(A %% B == R) #%d\n", j);

//         printf("print(hex(A//B))\n");
//         printf("print(hex(A%%B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&R);
// }

// void test_DIVC(int TEST)
// {
//     bigint *A = NULL;
//     bigint *B = NULL;
//     word Q = 0;
//     bigint *R = NULL;

//     for (int j = 0; j < TEST; j++)
//     {

//         int num1 = rand() % 0x0f + 1;

//         bi_gen_rand(&A, NON_NEGATIVE, num1);
//         bi_gen_rand(&B, NON_NEGATIVE, num1 - 1);

//         // bi_gen_rand(&A, NON_NEGATIVE, 5);
//         // bi_gen_rand(&B, NON_NEGATIVE, 3);

//         ///
//         bigint *T = NULL;

//         bi_assign(&T, B);
//         bi_word_lshift(&T, 1);

//         if (bi_cmp(A, T) == -1)
//         {
//             if (B->a[B->wordlen - 1] >= pow2(w - 1))
//             {
//                 printf("DIVC 입력 조건 0 ≤ A < BW 성립!\n");
//             }
//         }
//         bi_delete(&T);
//         ///

//         bi_DIVC(&Q, &R, A, B);

//     //         bi_print("A", A);
//
//         printf("Q = %#llx\n", "x", Q);
//
//         bi_print("R", R);

//         printf("print(A // B == Q) #%d\n", j);
//         printf("print(A %% B == R) #%d\n", j);

//         printf("print(hex(A//B))\n");
//         printf("print(hex(A%%B))\n");
//     }
//     bi_delete(&A);
//     bi_delete(&B);
//     bi_delete(&R);
// }

void test_DIV(int TEST)
{
    printf("print(\"### DIV TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
            {
                bi_gen_rand(&A, NON_NEGATIVE, num1);
                bi_gen_rand(&B, NON_NEGATIVE, num2);
                if (bi_is_zero(B) == true)
                    continue;
                break;
            }
        }

        bi_div(&Q, &R, A, B);
        sage_show_div(&Q, &R, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);
}

void test_long_div_bin(int TEST)
{
    printf("print(\"### BINARY LONG DIVISION TEST ###\\n\")\n");
    printf("cnt = 0\n");

    bigint *A = NULL;
    bigint *B = NULL;
    bigint *Q = NULL;
    bigint *R = NULL;

    for (int j = 0; j < TEST; j++)
    {

        int num1 = rand() % 0x0f + 1;
        int num2 = rand() % 0x0f + 1;

        while (1)
        {
            num1 = rand() % 0x0f + 1;
            num2 = rand() % 0x0f + 1;

            if (num1 >= num2)
            {
                bi_gen_rand(&A, NON_NEGATIVE, num1);
                bi_gen_rand(&B, NON_NEGATIVE, num2);
                if (bi_is_zero(B) == true)
                    continue;
                break;
            }
        }

        bi_long_div_bin(&Q, &R, A, B);
        sage_show_div(&Q, &R, A, B, j);
    }
    printf("if (cnt == 0):\n");
    printf("    print(\"ALL TRUE!\")\n");
    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);
}
