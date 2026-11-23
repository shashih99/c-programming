/* 08_setjmp.c - non-local jumps with setjmp/longjmp: a try/catch-like pattern */
#include <stdio.h>
#include <setjmp.h>

static jmp_buf on_error;

enum { ERR_NONE, ERR_PARSE, ERR_RANGE };

int parse_digit(char c)
{
    if (c < '0' || c > '9') longjmp(on_error, ERR_PARSE);   /* "throw" */
    return c - '0';
}

int checked_sum(const char *s)
{
    int sum = 0;
    for (; *s; s++) {
        sum += parse_digit(*s);
        if (sum > 20) longjmp(on_error, ERR_RANGE);
    }
    return sum;
}

int main(void)
{
    const char *tests[] = {"123", "12a", "99999"};
    for (int i = 0; i < 3; i++) {
        /* setjmp returns 0 the first time, and the longjmp value when jumped back to.
           The standard only allows it in contexts like this (not "int e = setjmp(...)"). */
        switch (setjmp(on_error)) {
        case ERR_NONE:                   /* "try" */
            printf("\"%s\" -> sum %d\n", tests[i], checked_sum(tests[i]));
            break;
        case ERR_PARSE:                  /* "catch" */
            printf("\"%s\" -> error PARSE\n", tests[i]);
            break;
        case ERR_RANGE:
            printf("\"%s\" -> error RANGE\n", tests[i]);
            break;
        }
    }
    return 0;
}
