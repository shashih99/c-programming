/* 02_nested.c - nested functions: a GCC extension, NOT standard C.
 * Compiles with gcc (gnu11), fails with clang or gcc -std=c11 -pedantic-errors. */
#include <stdio.h>

int main(void)
{
    int factor = 10;

    int scale(int x)                    /* defined inside main */
    {
        return x * factor;              /* can read main's local variables */
    }

    printf("scale(5) = %d\n", scale(5));
    return 0;
}
