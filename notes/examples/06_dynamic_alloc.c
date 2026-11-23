/* 06_dynamic_alloc.c - malloc, calloc, realloc, free; growable array; 2-D; flexible array member */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {               /* a growable int array ("vector") */
    int *data;
    size_t len, cap;
} Vec;

int vec_push(Vec *v, int x)
{
    if (v->len == v->cap) {
        size_t new_cap = v->cap ? v->cap * 2 : 4;
        int *tmp = realloc(v->data, new_cap * sizeof *tmp);   /* never assign straight to v->data */
        if (!tmp) return 0;                                    /* old block still valid */
        v->data = tmp;
        v->cap = new_cap;
        printf("  (grew capacity to %zu)\n", new_cap);
    }
    v->data[v->len++] = x;
    return 1;
}

typedef struct {               /* flexible array member (C99) */
    size_t len;
    char text[];               /* must be last; no size */
} Message;

Message *message_new(const char *s)
{
    size_t n = strlen(s) + 1;
    Message *m = malloc(sizeof *m + n);        /* header + room for the text */
    if (!m) return NULL;
    m->len = n - 1;
    memcpy(m->text, s, n);
    return m;
}

int main(void)
{
    /* malloc: uninitialised */
    int n = 5;
    int *a = malloc(n * sizeof *a);
    if (a == NULL) { perror("malloc"); return 1; }
    for (int i = 0; i < n; i++) a[i] = i * i;
    printf("malloc : ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    /* calloc: zero-initialised */
    int *z = calloc(n, sizeof *z);
    if (!z) { free(a); return 1; }
    printf("calloc : ");
    for (int i = 0; i < n; i++) printf("%d ", z[i]);
    printf("\n");

    /* realloc: resize, keeps existing contents */
    int *tmp = realloc(a, 8 * sizeof *a);
    if (!tmp) { free(a); free(z); return 1; }
    a = tmp;
    for (int i = n; i < 8; i++) a[i] = -1;
    printf("realloc: ");
    for (int i = 0; i < 8; i++) printf("%d ", a[i]);
    printf("\n");

    free(a); a = NULL;
    free(z); z = NULL;

    /* growable array */
    Vec v = {0};
    printf("vec_push 1..9:\n");
    for (int i = 1; i <= 9; i++)
        if (!vec_push(&v, i)) { free(v.data); return 1; }
    printf("vec: len=%zu cap=%zu, last=%d\n", v.len, v.cap, v.data[v.len - 1]);
    free(v.data);

    /* dynamic 2-D array, one contiguous block: rows x cols */
    int rows = 3, cols = 4;
    int *grid = malloc((size_t)rows * cols * sizeof *grid);
    if (!grid) return 1;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            grid[r * cols + c] = r * 10 + c;
    printf("grid[2][3] = %d\n", grid[2 * cols + 3]);
    free(grid);

    /* dynamic 2-D array, array of row pointers (jagged-capable) */
    int **m = malloc(rows * sizeof *m);
    if (!m) return 1;
    for (int r = 0; r < rows; r++) {
        m[r] = calloc(r + 1, sizeof **m);          /* row r has r+1 elements */
        if (!m[r]) { while (r--) free(m[r]); free(m); return 1; }
    }
    m[2][2] = 7;
    printf("jagged m[2][2] = %d\n", m[2][2]);
    for (int r = 0; r < rows; r++) free(m[r]);     /* free rows first ... */
    free(m);                                       /* ... then the pointer array */

    Message *msg = message_new("flexible!");
    if (!msg) return 1;
    printf("Message: len=%zu text=%s sizeof(Message)=%zu\n", msg->len, msg->text, sizeof(Message));
    free(msg);
    return 0;
}
