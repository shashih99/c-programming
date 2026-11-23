/* 04_function_pointers.c - declaring, calling, callbacks, qsort, dispatch table */
#include <stdio.h>
#include <stdlib.h>

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

typedef int (*binop)(int, int);              /* typedef makes it readable */

int apply(binop f, int a, int b)             /* callback: function passed as argument */
{
    return f(a, b);
}

int cmp_asc(const void *x, const void *y)
{
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);                /* avoids overflow of a - b */
}

int cmp_desc(const void *x, const void *y) { return cmp_asc(y, x); }

void print(const int *a, int n)
{
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main(void)
{
    int (*fp)(int, int) = add;               /* raw syntax; &add also works */
    printf("fp(2, 3)        = %d\n", fp(2, 3));
    printf("(*fp)(2, 3)     = %d\n", (*fp)(2, 3));

    printf("apply(mul,4,5)  = %d\n", apply(mul, 4, 5));

    binop ops[] = {add, sub, mul};           /* dispatch table */
    const char *sym = "+-*";
    for (int i = 0; i < 3; i++)
        printf("9 %c 3 = %d\n", sym[i], ops[i](9, 3));

    int v[] = {5, -2, 9, 1, 7};
    qsort(v, 5, sizeof v[0], cmp_asc);
    printf("qsort asc : "); print(v, 5);
    qsort(v, 5, sizeof v[0], cmp_desc);
    printf("qsort desc: "); print(v, 5);
    return 0;
}
