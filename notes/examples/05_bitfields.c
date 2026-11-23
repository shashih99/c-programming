/* 05_bitfields.c - bit fields: packing small values into fewer bits */
#include <stdio.h>

struct DateNormal {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

struct DateBits {
    unsigned int day   : 5;     /* 0..31   */
    unsigned int month : 4;     /* 0..15   */
    unsigned int year  : 12;    /* 0..4095 */
};

struct Flags {
    unsigned int is_open   : 1;
    unsigned int is_dirty  : 1;
    unsigned int mode      : 2; /* 0..3 */
};

int main(void)
{
    struct DateBits d = {23, 11, 2026};
    printf("date = %u/%u/%u\n", d.day, d.month, d.year);
    printf("sizeof(DateNormal) = %zu, sizeof(DateBits) = %zu\n",
           sizeof(struct DateNormal), sizeof(struct DateBits));

    struct Flags f = {0};
    f.is_open = 1;
    f.mode = 3;
    printf("flags: open=%u dirty=%u mode=%u, sizeof = %zu\n",
           f.is_open, f.is_dirty, f.mode, sizeof f);

    unsigned v = 5;
    f.mode = v;                 /* only 2 bits: 5 (101) is truncated to 1 (01).
                                   (f.mode = 5 with a constant -> gcc -Woverflow warning) */
    printf("f.mode = 5 stored as %u\n", f.mode);
    /* &f.mode;  -> error: cannot take address of a bit-field */
    return 0;
}
