#include "bi.h"
#include "bi_op.h"

word pow2(int a)
{
    word x = 1;
    return (x << a);
}

int bitlen(word a)
{
    int cnt = 0;

    do
    {
        a = a >> 1;
        cnt++;
    } while (a > 0);

    return cnt;
}

// min(a, b)
int min(IN int a, IN int b)
{
    // Case 1: a < b, then return a.
    if (a < b)
        return a;

    // Case 2: a ≥ b, then return b.
    return b;
}

// max(a, b) → max(a, b)
int max(IN int a, IN int b)
{
    // Case 1: a ≥ b, then return a.
    if (a >= b)
        return a;

    // Case 2: a < b, then return b.
    return b;
}
