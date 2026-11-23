/* 04_pointers.c - &, *, NULL, void*, sizes, dangling/wild pointers */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 42;
    int *p = &x;                            /* p holds the ADDRESS of x */

    printf("x  = %d\n", x);
    printf("&x = %p\n", (void *)&x);
    printf("p  = %p (same as &x)\n", (void *)p);
    printf("*p = %d (value at that address)\n", *p);

    *p = 100;                               /* write through the pointer */
    printf("after *p = 100, x = %d\n", x);

    printf("&p = %p (p has its own address)\n", (void *)&p);

    printf("sizeof(int*) = %zu, sizeof(char*) = %zu, sizeof(double*) = %zu\n",
           sizeof(int *), sizeof(char *), sizeof(double *));

    int *np = NULL;                         /* points nowhere: safe "empty" value */
    if (np == NULL)
        printf("np is NULL, don't dereference it\n");

    /* void* : generic pointer, must be cast/converted before dereferencing */
    double d = 3.14;
    void *vp = &d;
    printf("*(double *)vp = %.2f\n", *(double *)vp);
    vp = &x;
    printf("*(int *)vp    = %d\n", *(int *)vp);

    /* dangling pointer after free */
    int *heap = malloc(sizeof *heap);
    if (!heap) return 1;
    *heap = 7;
    printf("*heap = %d\n", *heap);
    free(heap);                             /* heap is now DANGLING */
    heap = NULL;                            /* good habit: reset after free */
    printf("heap reset to NULL after free\n");

    /* int *wild;  *wild = 5;   -> wild pointer: uninitialised, UB */
    return 0;
}

/* Returning address of a local -> dangling pointer once the function returns.
int *bad_return(void) { int local = 5; return &local; }   // gcc warns: -Wreturn-local-addr
*/
