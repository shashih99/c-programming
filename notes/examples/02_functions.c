/* 02_functions.c - declaration (prototype), definition, call, return */
#include <stdio.h>

int add(int a, int b);          /* prototype: tells compiler name, return type, params */
void greet(void);               /* no params, no return value */
double average(const int arr[], int n);

int main(void)
{
    greet();
    int s = add(3, 4);          /* 3 and 4 are arguments (actual parameters) */
    printf("add(3, 4) = %d\n", s);

    int nums[] = {4, 8, 15, 16, 23, 42};
    printf("average = %.2f\n", average(nums, 6));
    return 0;
}

int add(int a, int b)           /* a, b are parameters (formal parameters) */
{
    return a + b;
}

void greet(void)
{
    printf("Hello from greet()\n");
    return;                     /* optional in void functions */
}

double average(const int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return (double)sum / n;
}
