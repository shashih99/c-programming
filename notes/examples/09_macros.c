/* 09_macros.c - function-like macros, pitfalls, do-while(0), #, ##, __VA_ARGS__, X-macros */
#include <stdio.h>

#define SQUARE_BAD(x)  x * x                 /* missing parentheses */
#define SQUARE(x)      ((x) * (x))           /* parenthesise args AND whole body */
#define MAX(a, b)      ((a) > (b) ? (a) : (b))

#define SWAP(T, a, b)  do { T tmp_ = (a); (a) = (b); (b) = tmp_; } while (0)

#define STR(x)         #x                    /* stringify */
#define XSTR(x)        STR(x)                /* expand first, then stringify */
#define CONCAT(a, b)   a##b                  /* token pasting */
#define VERSION        3

#define PRINT_VAR(v)   printf(#v " = %d\n", v)
#define LOGF(fmt, ...) printf("[log] " fmt "\n", __VA_ARGS__)   /* variadic macro */

/* X-macro: one list, used to generate both an enum and a string table */
#define COLOR_LIST \
    X(RED)         \
    X(GREEN)       \
    X(BLUE)

#define X(name) COLOR_##name,
enum Color { COLOR_LIST COLOR_COUNT };
#undef X

#define X(name) #name,
static const char *color_names[] = { COLOR_LIST };
#undef X

int main(void)
{
    printf("SQUARE_BAD(2 + 3) = %d  (expands to 2 + 3 * 2 + 3)\n", SQUARE_BAD(2 + 3));
    printf("SQUARE(2 + 3)     = %d\n", SQUARE(2 + 3));
    printf("100 / SQUARE_BAD(5) = %d (expands to 100 / 5 * 5)\n", 100 / SQUARE_BAD(5));
    printf("100 / SQUARE(5)     = %d\n", 100 / SQUARE(5));
    printf("MAX(7, 12)        = %d\n", MAX(7, 12));

    int a = 1, b = 2;
    if (a < b)
        SWAP(int, a, b);                       /* do-while(0) makes this safe without braces */
    else
        printf("not swapped\n");
    printf("after SWAP: a = %d, b = %d\n", a, b);

    printf("STR(hello world)  = \"%s\"\n", STR(hello world));
    printf("STR(VERSION)      = \"%s\"\n", STR(VERSION));
    printf("XSTR(VERSION)     = \"%s\"\n", XSTR(VERSION));

    int CONCAT(my, Var) = 99;                 /* declares myVar */
    PRINT_VAR(myVar);

    LOGF("%s has %d items", "cart", 3);

    for (int i = 0; i < COLOR_COUNT; i++)
        printf("color %d = %s\n", i, color_names[i]);
    return 0;
}
