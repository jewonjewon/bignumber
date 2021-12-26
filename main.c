#include <stdio.h>

#include "bi_local.h"
#include "bi_op.h"
#include "bi_test.h"

int main()
{
    srand((unsigned)time(NULL));

    // test_ADD(1000);
    // test_SUB(10000);
    // test_MULC(100);
    // test_MUL(10000);

    // test_bi_lshift(10000);
    // test_SQU_A(100);
    // SQUC에서 memory leak 발생.
    test_SQUC(1);

    // test_SQU(100);

    return 0;
}
