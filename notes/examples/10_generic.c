/* 10_generic.c - C11 _Generic: choose an expression based on the TYPE of an argument */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TYPE_NAME(x) _Generic((x),          \
    int:           "int",                   \
    long:          "long",                  \
    float:         "float",                 \
    double:        "double",                \
    char:          "char",                  \
    char *:        "char *",                \
    const char *:  "const char *",          \
    default:       "other")

/* "overloaded" print */
void print_int(int x)            { printf("int: %d\n", x); }
void print_double(double x)      { printf("double: %.3f\n", x); }
void print_str(const char *s)    { printf("string: \"%s\"\n", s); }

#define PRINT(x) _Generic((x),   \
    int:          print_int,     \
    double:       print_double,  \
    float:        print_double,  \
    char *:       print_str,     \
    const char *: print_str      \
)(x)

/* type-generic absolute value: picks abs / labs / fabs */
#define ABS(x) _Generic((x), int: abs, long: labs, float: fabsf, double: fabs)(x)

/* type-generic max without double evaluation, via inline helpers */
static inline int    max_i(int a, int b)       { return a > b ? a : b; }
static inline double max_d(double a, double b) { return a > b ? a : b; }
#define MAX(a, b) _Generic((a) + (b), int: max_i, double: max_d)(a, b)

int main(void)
{
    int i = 5; double d = 2.5; float f = 1.5f; char c = 'x'; char *s = "hi"; long l = 7L;
    short sh = 3;
    printf("TYPE_NAME: %s %s %s %s %s %s %s\n",
           TYPE_NAME(i), TYPE_NAME(d), TYPE_NAME(f), TYPE_NAME(c), TYPE_NAME(s), TYPE_NAME(l), TYPE_NAME(sh));
    printf("TYPE_NAME('x') = %s   (character constants are int in C!)\n", TYPE_NAME('x'));
    printf("TYPE_NAME(c + 1) = %s (char promoted to int in arithmetic)\n", TYPE_NAME(c + 1));

    PRINT(42);
    PRINT(3.14159);
    PRINT("generic");

    printf("ABS(-7) = %d, ABS(-7L) = %ld, ABS(-2.5) = %.1f\n", ABS(-7), ABS(-7L), ABS(-2.5));
    printf("MAX(3, 9) = %d, MAX(2.5, 1.0) = %.1f, MAX(2, 1.5) = %.1f\n", MAX(3, 9), MAX(2.5, 1.0), MAX(2, 1.5));
    return 0;
}
