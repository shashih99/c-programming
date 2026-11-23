/* 02_inline.c - inline functions vs macros */
#include <stdio.h>

#define SQUARE_MACRO(x) ((x) * (x))     /* text substitution: x evaluated twice */

static inline int square(int x)         /* type-checked, x evaluated once */
{
    return x * x;
}

int main(void)
{
    printf("square(4)       = %d\n", square(4));
    printf("SQUARE_MACRO(4) = %d\n", SQUARE_MACRO(4));

    int i = 3;
    int r = square(i++);                /* i++ evaluated once: r = 9, i = 4 */
    printf("square(i++)     = %d, i = %d\n", r, i);

    /* SQUARE_MACRO(i++) would expand to ((i++) * (i++)):
       i modified twice in one expression -> undefined behaviour. Don't do it. */
    return 0;
}
