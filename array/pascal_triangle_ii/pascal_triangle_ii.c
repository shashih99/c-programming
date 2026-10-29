#include <stdio.h>
#include <stdlib.h>

int* getRow(int rowIndex, int* returnSize) {
    *returnSize = rowIndex + 1;
    int* row = (int*)calloc(*returnSize, sizeof(int));
    row[0] = 1;

    for (int i = 1; i <= rowIndex; i++) {
        for (int j = i; j >= 1; j--) {
            row[j] += row[j - 1];
        }
    }

    return row;
}

int main(void) {
    int tests[] = {0, 1, 3, 4};
    int n = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int t = 0; t < n; t++) {
        int returnSize;
        int* row = getRow(tests[t], &returnSize);

        printf("rowIndex = %d: ", tests[t]);
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", row[i]);
        }
        printf("\n");

        free(row);
    }

    return 0;
}
