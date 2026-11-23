/* 01_operators.c - arithmetic, relational, logical, bitwise, misc */
#include <stdio.h>

int main(void)
{
    int a = 10, b = 3;
    printf("a+b=%d a-b=%d a*b=%d a/b=%d a%%b=%d\n", a + b, a - b, a * b, a / b, a % b);
    printf("-7 %% 3 = %d\n", -7 % 3);           /* sign follows the dividend */

    printf("a>b=%d a==b=%d\n", a > b, a == b);  /* relational -> 0 or 1 */

    int x = 0;
    if (x != 0 && 10 / x > 1)                   /* short-circuit: 10/x never runs */
        printf("never\n");
    printf("short-circuit avoided divide by zero\n");

    unsigned p = 12, q = 10;                    /* 1100, 1010 */
    printf("p&q=%u p|q=%u p^q=%u ~p&0xF=%u p<<1=%u p>>2=%u\n",
           p & q, p | q, p ^ q, ~p & 0xF, p << 1, p >> 2);

    int i = 5;
    int pre = ++i;      /* i becomes 6, then pre = 6 */
    int post = i++;     /* post = 6, then i becomes 7 */
    printf("pre=%d post=%d i=%d\n", pre, post, i);

    int max = (a > b) ? a : b;                  /* ternary */
    printf("max=%d\n", max);

    printf("2 + 3 * 4 = %d, (2 + 3) * 4 = %d\n", 2 + 3 * 4, (2 + 3) * 4);
    return 0;
}
