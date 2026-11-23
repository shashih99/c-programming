/* 04_double_pointer.c - pointer to pointer, changing a caller's pointer */
#include <stdio.h>
#include <stdlib.h>

/* WRONG: p is a copy, caller's pointer stays NULL and the block LEAKS
   (gcc -fsanitize=address reports: "detected memory leaks ... 12 byte(s)") */
void alloc_wrong(int *p, int n)
{
    p = malloc(n * sizeof *p);
    (void)p;
}

/* RIGHT: pass the ADDRESS of the caller's pointer */
int alloc_right(int **pp, int n)
{
    *pp = malloc(n * sizeof **pp);
    return *pp != NULL;
}

int main(void)
{
    int x = 5;
    int *p = &x;
    int **pp = &p;

    printf("x = %d, *p = %d, **pp = %d\n", x, *p, **pp);
    printf("&x = %p, p = %p, *pp = %p\n", (void *)&x, (void *)p, (void *)*pp);

    **pp = 50;
    printf("after **pp = 50, x = %d\n", x);

    int *arr = NULL;
    alloc_wrong(arr, 3);
    printf("after alloc_wrong: arr is %s\n", arr ? "set" : "still NULL");

    if (!alloc_right(&arr, 3)) return 1;
    for (int i = 0; i < 3; i++) arr[i] = (i + 1) * 11;
    printf("after alloc_right: %d %d %d\n", arr[0], arr[1], arr[2]);
    free(arr);

    const char *names[] = {"Ada", "Linus", "Dennis"};   /* array of pointers */
    const char **it = names;
    for (int i = 0; i < 3; i++, it++)
        printf("names[%d] = %s (first char %c)\n", i, *it, **it);
    return 0;
}
