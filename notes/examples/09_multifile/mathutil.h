/* mathutil.h - the PUBLIC interface: declarations only, no definitions */
#ifndef MATHUTIL_H          /* include guard: safe to #include more than once */
#define MATHUTIL_H

#define MATHUTIL_VERSION "1.0"

typedef struct {
    int min, max;
} Range;

extern int mathutil_calls;  /* DECLARATION of a global defined in mathutil.c */

int  clamp(int x, Range r); /* function prototypes (external linkage by default) */
long factorial(int n);

#endif /* MATHUTIL_H */
