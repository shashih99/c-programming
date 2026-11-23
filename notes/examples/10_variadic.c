/* 10_variadic.c - functions with a variable number of arguments (<stdarg.h>) */
#include <stdio.h>
#include <stdarg.h>

/* 1. count passed explicitly */
int sum(int count, ...)
{
    va_list ap;
    va_start(ap, count);                 /* init after the LAST named parameter */
    int total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(ap, int);        /* fetch next arg, you must state its type */
    va_end(ap);                          /* always pair with va_start */
    return total;
}

/* 2. sentinel-terminated list (NULL marks the end) */
void print_words(const char *first, ...)
{
    va_list ap;
    va_start(ap, first);
    for (const char *w = first; w != NULL; w = va_arg(ap, const char *))
        printf("[%s] ", w);
    va_end(ap);
    printf("\n");
}

/* 3. default argument promotions: float -> double, char/short -> int */
double average(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    double total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(ap, double);     /* NOT va_arg(ap, float) */
    va_end(ap);
    return count ? total / count : 0;
}

/* 4. wrapping printf: forward a va_list with vfprintf */
void log_msg(const char *level, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf("[%s] ", level);
    vprintf(fmt, ap);                    /* the v- versions take a va_list */
    printf("\n");
    va_end(ap);
}

/* 5. va_copy: walk the same arguments twice */
int max_and_count_above(int threshold, int count, ...)
{
    va_list ap, ap2;
    va_start(ap, count);
    va_copy(ap2, ap);
    int max = 0;
    for (int i = 0; i < count; i++) { int v = va_arg(ap, int); if (i == 0 || v > max) max = v; }
    int above = 0;
    for (int i = 0; i < count; i++) if (va_arg(ap2, int) > threshold) above++;
    va_end(ap2);
    va_end(ap);
    printf("max = %d, %d values above %d\n", max, above, threshold);
    return max;
}

int main(void)
{
    printf("sum(3, 10, 20, 30) = %d\n", sum(3, 10, 20, 30));
    printf("sum(0)             = %d\n", sum(0));
    print_words("alpha", "beta", "gamma", (char *)NULL);
    float f = 2.5f;
    printf("average(3, 1.0, 2.0, f) = %.2f\n", average(3, 1.0, 2.0, f));  /* f promoted to double */
    log_msg("INFO", "user %s logged in from %d.%d.%d.%d", "asha", 10, 0, 0, 7);
    max_and_count_above(5, 5, 3, 9, 4, 7, 6);
    return 0;
}
