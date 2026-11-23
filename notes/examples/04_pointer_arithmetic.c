/* 04_pointer_arithmetic.c - +, -, ++, comparison, difference, array <-> pointer */
#include <stdio.h>
#include <stddef.h>

int main(void)
{
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;                              /* == &a[0] */

    printf("p     = %p -> %d\n", (void *)p, *p);
    printf("p + 1 = %p -> %d (moved %zu bytes)\n", (void *)(p + 1), *(p + 1), sizeof(int));

    char s[] = "abc";
    char *c = s;
    printf("c     = %p, c + 1 = %p (moved 1 byte)\n", (void *)c, (void *)(c + 1));

    printf("walk with pointer: ");
    for (int *q = a; q < a + 5; q++)         /* a + 5 = one past the end: OK to form, not to deref */
        printf("%d ", *q);
    printf("\n");

    int *end = &a[4];
    ptrdiff_t diff = end - p;                /* difference = number of ELEMENTS */
    printf("end - p = %td elements\n", diff);

    p += 2;
    printf("after p += 2: *p = %d, p[1] = %d, p[-1] = %d\n", *p, p[1], p[-1]);

    int *r = a;
    printf("*r++ = %d, ", *r++);             /* use *r, THEN move r */
    printf("now *r = %d\n", *r);
    printf("++*r = %d (increments the value a[1])\n", ++*r);
    printf("a[1] = %d\n", a[1]);

    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*row)[3] = m;                       /* pointer to an array of 3 ints */
    printf("row[1][2] = %d, *(*(m + 1) + 2) = %d\n", row[1][2], *(*(m + 1) + 2));
    return 0;
}
