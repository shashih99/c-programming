/* 04_const_pointers.c - const int *, int *const, const int *const */
#include <stdio.h>

int main(void)
{
    int a = 1, b = 2;

    const int *p1 = &a;          /* pointer to const int: can't change *p1, can move p1 */
    /* *p1 = 10;   error */
    p1 = &b;                     /* OK */
    printf("p1 -> %d\n", *p1);

    int *const p2 = &a;          /* const pointer to int: can change *p2, can't move p2 */
    *p2 = 10;                    /* OK */
    /* p2 = &b;    error */
    printf("p2 -> %d (a = %d)\n", *p2, a);

    const int *const p3 = &b;    /* neither */
    /* *p3 = 5; p3 = &a;   both errors */
    printf("p3 -> %d\n", *p3);
    return 0;
}
