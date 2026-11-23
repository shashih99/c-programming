#include <stdio.h>
#include <stdlib.h>

/**
 * LeetCode 163. Missing Ranges
 *
 * Given an inclusive range [lower, upper] and a sorted array of unique
 * integers nums (all within the range), return the shortest sorted list of
 * ranges [a, b] that exactly covers every number in [lower, upper] that is
 * NOT in nums.
 *
 * Approach: walk through nums keeping track of the next expected number
 * (`next`). Whenever nums[i] > next, the gap [next, nums[i] - 1] is missing.
 * After the loop, if next <= upper, the tail [next, upper] is missing.
 * long long is used so that nums[i] + 1 cannot overflow when nums[i] == INT_MAX.
 *
 * Time:  O(n)
 * Space: O(n) for the output (at most n + 1 ranges)
 *
 * @param nums              sorted array of unique integers
 * @param numsSize          size of nums
 * @param lower             lower bound (inclusive)
 * @param upper             upper bound (inclusive)
 * @param returnSize        out: number of ranges returned
 * @param returnColumnSizes out: array holding the size of each range (always 2)
 * @return array of ranges; each range is an int[2] {start, end}.
 *         Caller frees each range, the outer array and *returnColumnSizes.
 */
int** findMissingRanges(int* nums, int numsSize, int lower, int upper,
                        int* returnSize, int** returnColumnSizes) {
    int maxRanges = numsSize + 1;
    int** result = (int**)malloc(maxRanges * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxRanges * sizeof(int));
    *returnSize = 0;
    if (result == NULL || *returnColumnSizes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(result);
        free(*returnColumnSizes);
        *returnColumnSizes = NULL;
        return NULL;
    }

    long long next = lower; /* smallest number not yet accounted for */

    for (int i = 0; i <= numsSize; i++) {
        /* Treat upper + 1 as a sentinel after the last element. */
        long long cur = (i < numsSize) ? (long long)nums[i] : (long long)upper + 1;

        if (cur > next) {
            int* range = (int*)malloc(2 * sizeof(int));
            if (range == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                break;
            }
            range[0] = (int)next;
            range[1] = (int)(cur - 1);
            result[*returnSize] = range;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
        next = cur + 1;
    }

    return result;
}

static void freeRanges(int** ranges, int size, int* columnSizes) {
    for (int i = 0; i < size; i++) {
        free(ranges[i]);
    }
    free(ranges);
    free(columnSizes);
}

static void printArray(const int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], i + 1 < size ? "," : "");
    }
    printf("]");
}

static void runTest(const char* name, int* nums, int numsSize, int lower, int upper) {
    int returnSize;
    int* columnSizes;
    int** ranges = findMissingRanges(nums, numsSize, lower, upper, &returnSize, &columnSizes);

    printf("%s:\n", name);
    printf("Input: nums = ");
    printArray(nums, numsSize);
    printf(", lower = %d, upper = %d\n", lower, upper);
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("[%d,%d]%s", ranges[i][0], ranges[i][1], i + 1 < returnSize ? "," : "");
    }
    printf("]\n\n");

    freeRanges(ranges, returnSize, columnSizes);
}

int main(void) {
    /* Example 1: expected [[2,2],[4,49],[51,74],[76,99]] */
    int nums1[] = {0, 1, 3, 50, 75};
    runTest("Example 1", nums1, 5, 0, 99);

    /* Example 2: expected [] */
    int nums2[] = {-1};
    runTest("Example 2", nums2, 1, -1, -1);

    /* Empty array: expected [[1,1]] */
    runTest("Empty nums", NULL, 0, 1, 1);

    /* Overflow edge: expected [[-2147483648,2147483646]] */
    int nums4[] = {2147483647};
    runTest("INT_MAX edge", nums4, 1, -2147483647 - 1, 2147483647);

    /* No gaps: expected [] */
    int nums5[] = {1, 2, 3};
    runTest("No gaps", nums5, 3, 1, 3);

    return 0;
}
