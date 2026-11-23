/* 03_multidim.c - 2-D arrays: row-major layout, passing to functions */
#include <stdio.h>

#define ROWS 2
#define COLS 3

void print_fixed(int m[][COLS], int rows)        /* column size MUST be given */
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%3d", m[i][j]);
        printf("\n");
    }
}

void print_vla(int rows, int cols, int m[rows][cols])   /* C99 VLA parameter */
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d", m[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int m[ROWS][COLS] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    printf("print_fixed:\n");
    print_fixed(m, ROWS);

    printf("row-major memory: ");
    int *flat = &m[0][0];
    for (int k = 0; k < ROWS * COLS; k++)
        printf("%d ", flat[k]);
    printf("\n");

    printf("sizeof(m) = %zu, sizeof(m[0]) = %zu\n", sizeof(m), sizeof(m[0]));

    int t[COLS][ROWS];                           /* transpose */
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            t[j][i] = m[i][j];
    printf("transpose (print_vla):\n");
    print_vla(COLS, ROWS, t);

    int cube[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    printf("cube[1][0][1] = %d\n", cube[1][0][1]);
    return 0;
}
