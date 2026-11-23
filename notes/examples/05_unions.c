/* 05_unions.c - shared storage, size, type punning, tagged union */
#include <stdio.h>
#include <stdint.h>

union Data {
    int    i;
    float  f;
    char   str[12];
};

union Word {                    /* view the same 4 bytes two ways */
    uint32_t value;
    uint8_t  bytes[4];
};

typedef enum { SHAPE_CIRCLE, SHAPE_RECT } ShapeKind;

typedef struct {                /* tagged union: the tag says which member is valid */
    ShapeKind kind;
    union {
        struct { double r; } circle;
        struct { double w, h; } rect;
    };                          /* anonymous union (C11) */
} Shape;

double area(const Shape *s)
{
    switch (s->kind) {
    case SHAPE_CIRCLE: return 3.14159 * s->circle.r * s->circle.r;
    case SHAPE_RECT:   return s->rect.w * s->rect.h;
    }
    return 0;
}

int main(void)
{
    union Data d;
    printf("sizeof(union Data) = %zu (largest member = 12)\n", sizeof d);

    d.i = 42;
    printf("d.i = %d\n", d.i);
    d.f = 2.5f;                 /* overwrites the same bytes */
    printf("d.f = %.1f, d.i now = %d (reinterpreted bits)\n", d.f, d.i);

    printf("&d.i = %p, &d.f = %p, &d.str = %p (all same)\n",
           (void *)&d.i, (void *)&d.f, (void *)&d.str);

    union Word w = { .value = 0x11223344 };
    printf("bytes of 0x11223344: %02x %02x %02x %02x -> %s-endian\n",
           w.bytes[0], w.bytes[1], w.bytes[2], w.bytes[3],
           w.bytes[0] == 0x44 ? "little" : "big");

    Shape shapes[] = {
        { .kind = SHAPE_CIRCLE, .circle = { 1.0 } },
        { .kind = SHAPE_RECT,   .rect   = { 3.0, 4.0 } },
    };
    for (int i = 0; i < 2; i++)
        printf("shape %d area = %.2f\n", i, area(&shapes[i]));
    printf("sizeof(Shape) = %zu\n", sizeof(Shape));
    return 0;
}
