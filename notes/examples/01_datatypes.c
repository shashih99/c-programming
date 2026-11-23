/* 01_datatypes.c - sizes, limits and type conversion */
#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("char   : %zu byte\n",  sizeof(char));
    printf("short  : %zu bytes\n", sizeof(short));
    printf("int    : %zu bytes\n", sizeof(int));
    printf("long   : %zu bytes\n", sizeof(long));
    printf("float  : %zu bytes\n", sizeof(float));
    printf("double : %zu bytes\n", sizeof(double));
    printf("INT_MAX = %d, INT_MIN = %d\n", INT_MAX, INT_MIN);

    unsigned int u = 0;
    u = u - 1;                          /* unsigned wraps around (well-defined) */
    printf("0u - 1 = %u\n", u);

    int a = 7, b = 2;
    printf("7 / 2 = %d\n", a / b);              /* integer division truncates */
    printf("(double)7 / 2 = %.1f\n", (double)a / b);  /* explicit cast */

    char c = 'A';
    printf("'A' + 1 = %d (%c)\n", c + 1, c + 1);     /* char promoted to int */
    return 0;
}
