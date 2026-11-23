/* 03_arrays.c - 1-D arrays: init, sizeof, decay, passing, common ops */
#include <stdio.h>

#define LEN(a) (sizeof(a) / sizeof((a)[0]))    /* only works on real arrays, not pointers */

void print(const int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void size_in_function(int *arr)     /* identical to: int arr[] */
{
    printf("sizeof(arr) in function = %zu (pointer!)\n", sizeof(arr));
}

void reverse(int arr[], int n)
{
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
    }
}

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};    /* full init */
    int b[5] = {1, 2};                  /* rest become 0 */
    int c[]  = {7, 8, 9};               /* size deduced = 3 */
    int z[5] = {0};                     /* all zeros */
    int d[6] = {[1] = 5, [4] = 9};      /* designated initialisers (C99) */

    printf("a: "); print(a, 5);
    printf("b: "); print(b, 5);
    printf("c: "); print(c, (int)LEN(c));
    printf("z: "); print(z, 5);
    printf("d: "); print(d, 6);

    printf("sizeof(a) = %zu, LEN(a) = %zu\n", sizeof(a), LEN(a));
    size_in_function(a);

    printf("a[2] = %d, *(a + 2) = %d, 2[a] = %d\n", a[2], *(a + 2), 2[a]);
    printf("a = %p, &a[0] = %p (same address)\n", (void *)a, (void *)&a[0]);

    reverse(a, 5);
    printf("reversed a: "); print(a, 5);

    int max = a[0];
    for (size_t i = 1; i < LEN(a); i++)
        if (a[i] > max) max = a[i];
    printf("max = %d\n", max);
    return 0;
}
