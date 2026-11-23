/* 06_memory_leak.c - common leak patterns and their fixes.
 * Run:  gcc -g 06_memory_leak.c -o leak && valgrind --leak-check=full ./leak
 *  or:  gcc -g -fsanitize=address 06_memory_leak.c -o leak && ./leak
 * Build with -DFIXED to get the leak-free version. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *make_greeting(const char *name)      /* returns heap memory: CALLER must free */
{
    char *s = malloc(strlen(name) + 8);
    if (s) sprintf(s, "Hello, %s", name);
    return s;
}

int process(int fail)
{
    int *buf = malloc(100 * sizeof *buf);
    if (!buf) return -1;
    if (fail) {
#ifdef FIXED
        free(buf);                          /* FIX: free on every exit path */
#endif
        return -1;                          /* LEAK 1: early return forgets free */
    }
    free(buf);
    return 0;
}

int main(void)
{
    /* LEAK 2: caller ignores ownership of returned memory */
    char *g = make_greeting("C");
    printf("%s\n", g);
#ifdef FIXED
    free(g);
#endif

    /* LEAK 3: overwriting the only pointer to a block */
    int *p = malloc(sizeof *p);
#ifdef FIXED
    free(p);
#endif
    p = malloc(sizeof *p);                  /* first block now unreachable */
    free(p);

    process(1);
    printf("done\n");
    return 0;
}
