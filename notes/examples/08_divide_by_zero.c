/* 08_divide_by_zero.c - integer vs floating division by zero, checks, assert */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* returns 0 on success, -1 on error; result through pointer */
int safe_divide(int a, int b, int *result)
{
    if (b == 0) {
        fprintf(stderr, "  error: division by zero (%d / %d)\n", a, b);
        return -1;
    }
    if (a == -2147483647 - 1 && b == -1) {          /* INT_MIN / -1 overflows too */
        fprintf(stderr, "  error: overflow (INT_MIN / -1)\n");
        return -1;
    }
    *result = a / b;
    return 0;
}

double average(const int *a, int n)
{
    assert(a != NULL && "array must not be NULL");  /* programmer errors: removed by -DNDEBUG */
    assert(n > 0);
    long sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return (double)sum / n;
}

int main(void)
{
    int q;
    int pairs[][2] = {{10, 2}, {7, 0}, {-2147483647 - 1, -1}, {-9, 4}};
    for (int i = 0; i < 4; i++) {
        if (safe_divide(pairs[i][0], pairs[i][1], &q) == 0)
            printf("  %d / %d = %d\n", pairs[i][0], pairs[i][1], q);
        fflush(stdout); fflush(stderr);
    }

    /* floating point: NOT an error in IEEE-754, gives inf or nan */
    double zero = 0.0;
    printf("1.0 / 0.0 = %f, -1.0 / 0.0 = %f, 0.0 / 0.0 = %f\n", 1.0 / zero, -1.0 / zero, zero / zero);
    printf("isinf(1.0/0.0) = %d, isnan(0.0/0.0) = %d\n", isinf(1.0 / zero) != 0, isnan(zero / zero) != 0);

    int data[] = {3, 4, 5};
    printf("average = %.2f\n", average(data, 3));
    /* average(data, 0);  -> Assertion `n > 0' failed. Aborted (core dumped) */
    return 0;
}
