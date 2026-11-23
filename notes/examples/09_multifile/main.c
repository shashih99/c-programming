/* main.c - uses mathutil through its header
 * Build:  gcc -Wall -Wextra -std=c11 main.c mathutil.c -o app && ./app
 * Or in steps:  gcc -c mathutil.c  &&  gcc -c main.c  &&  gcc main.o mathutil.o -o app */
#include <stdio.h>
#include "mathutil.h"
#include "mathutil.h"       /* included twice on purpose: the include guard makes it harmless */

int main(void)
{
    Range r = {0, 10};
    printf("mathutil v%s\n", MATHUTIL_VERSION);
    printf("clamp(-5) = %d, clamp(7) = %d, clamp(42) = %d\n",
           clamp(-5, r), clamp(7, r), clamp(42, r));
    printf("factorial(10) = %ld\n", factorial(10));
    printf("mathutil_calls = %d (extern variable from mathutil.c)\n", mathutil_calls);
    /* count_call();     -> link error: undefined reference (it's static in mathutil.c) */
    /* helper_count++;   -> compile error: undeclared here                            */
    return 0;
}
