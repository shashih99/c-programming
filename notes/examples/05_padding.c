/* 05_padding.c - alignment, padding, member ordering, packing */
#include <stdio.h>
#include <stddef.h>     /* offsetof */

struct Bad {            /* poorly ordered */
    char  a;            /* 1 byte  + 3 padding */
    int   b;            /* 4 bytes             */
    char  c;            /* 1 byte  + 7 padding */
    double d;           /* 8 bytes             */
};

struct Good {           /* largest first */
    double d;           /* 8 */
    int    b;           /* 4 */
    char   a;           /* 1 */
    char   c;           /* 1 + 2 tail padding */
};

struct __attribute__((packed)) Packed {   /* GCC/Clang: no padding at all */
    char  a;
    int   b;
    char  c;
    double d;
};

#define SHOW(T, m) printf("  %-8s offset %2zu, size %zu\n", #m, offsetof(T, m), sizeof(((T *)0)->m))

int main(void)
{
    printf("struct Bad    : sizeof = %zu, align = %zu\n", sizeof(struct Bad), _Alignof(struct Bad));
    SHOW(struct Bad, a); SHOW(struct Bad, b); SHOW(struct Bad, c); SHOW(struct Bad, d);

    printf("struct Good   : sizeof = %zu, align = %zu\n", sizeof(struct Good), _Alignof(struct Good));
    SHOW(struct Good, d); SHOW(struct Good, b); SHOW(struct Good, a); SHOW(struct Good, c);

    printf("struct Packed : sizeof = %zu\n", sizeof(struct Packed));
    SHOW(struct Packed, a); SHOW(struct Packed, b); SHOW(struct Packed, c); SHOW(struct Packed, d);
    return 0;
}
