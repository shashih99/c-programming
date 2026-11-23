/* 02_param_passing.c - pass by value vs pass by pointer ("by reference") */
#include <stdio.h>

void swap_by_value(int a, int b)        /* gets COPIES */
{
    int t = a; a = b; b = t;
    printf("  inside swap_by_value: a=%d b=%d\n", a, b);
}

void swap_by_pointer(int *a, int *b)    /* gets ADDRESSES */
{
    int t = *a; *a = *b; *b = t;
}

void double_all(int arr[], int n)       /* arrays decay to a pointer: changes are visible */
{
    for (int i = 0; i < n; i++)
        arr[i] *= 2;
}

void min_max(const int arr[], int n, int *min, int *max)   /* "return" two values */
{
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int main(void)
{
    int x = 1, y = 2;
    swap_by_value(x, y);
    printf("after swap_by_value:   x=%d y=%d\n", x, y);
    swap_by_pointer(&x, &y);
    printf("after swap_by_pointer: x=%d y=%d\n", x, y);

    int a[] = {1, 2, 3};
    double_all(a, 3);
    printf("after double_all: %d %d %d\n", a[0], a[1], a[2]);

    int lo, hi;
    int v[] = {7, -3, 12, 5};
    min_max(v, 4, &lo, &hi);
    printf("min=%d max=%d\n", lo, hi);
    return 0;
}
