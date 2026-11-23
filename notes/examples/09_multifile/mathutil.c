/* mathutil.c - the IMPLEMENTATION */
#include "mathutil.h"       /* include own header: compiler checks declarations match */

int mathutil_calls = 0;     /* DEFINITION: external linkage, visible to other files */

static int helper_count = 0;           /* internal linkage: private to this file */

static void count_call(void)           /* internal linkage: other files can't call it */
{
    mathutil_calls++;
    helper_count++;
}

int clamp(int x, Range r)
{
    count_call();
    if (x < r.min) return r.min;
    if (x > r.max) return r.max;
    return x;
}

long factorial(int n)
{
    count_call();
    long f = 1;
    for (int i = 2; i <= n; i++) f *= i;
    return f;
}
