/* 02_recursion.c - factorial, fibonacci, tail recursion, recursion vs iteration */
#include <stdio.h>

unsigned long long factorial(int n)
{
    if (n <= 1) return 1;               /* base case */
    return n * factorial(n - 1);        /* recursive case */
}

/* tail recursive: the recursive call is the LAST thing done */
unsigned long long fact_tail(int n, unsigned long long acc)
{
    if (n <= 1) return acc;
    return fact_tail(n - 1, acc * n);
}

int fib(int n)                          /* tree recursion: O(2^n) */
{
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

int fib_iter(int n)                     /* iterative: O(n) */
{
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        int t = a + b; a = b; b = t;
    }
    return a;
}

void print_down_up(int n)               /* code before vs after the call */
{
    if (n == 0) return;
    printf("%d ", n);                   /* runs on the way down */
    print_down_up(n - 1);
    printf("%d ", n);                   /* runs on the way back up */
}

int sum_digits(int n)
{
    return n == 0 ? 0 : n % 10 + sum_digits(n / 10);
}

int main(void)
{
    printf("factorial(5)      = %llu\n", factorial(5));
    printf("fact_tail(20, 1)  = %llu\n", fact_tail(20, 1));
    printf("fib(10)           = %d\n", fib(10));
    printf("fib_iter(40)      = %d\n", fib_iter(40));
    printf("sum_digits(1234)  = %d\n", sum_digits(1234));
    printf("print_down_up(3)  : ");
    print_down_up(3);
    printf("\n");
    return 0;
}
