#include <stdio.h>

/**
 * Merge Sorted Array
 *
 * Given two integer arrays nums1 and nums2, sorted in non-decreasing order,
 * merge them into a single sorted array stored in nums1.
 *
 * nums1 has length m + n: first m elements are valid, last n are 0 (placeholder).
 * nums2 has length n.
 *
 * Algorithm: Three-Pointer Merge from the End
 *
 * Merge from the end of nums1 to avoid overwriting elements we haven't read.
 * Use three pointers: i (nums1 tail), j (nums2 tail), k (write position).
 *
 * Time Complexity: O(m + n) - single pass through both arrays
 * Space Complexity: O(1) - in-place merge
 *
 * @param nums1: Array to merge into (size m + n)
 * @param nums1Size: Total size of nums1 (m + n)
 * @param m: Number of valid elements in nums1
 * @param nums2: Second sorted array (size n)
 * @param nums2Size: Size of nums2 (n)
 * @param n: Number of elements in nums2
 */
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    (void)nums1Size;
    (void)nums2Size;
    int i = m - 1;      /* Last valid element in nums1 */
    int j = n - 1;      /* Last element in nums2 */
    int k = m + n - 1;  /* Position to write in nums1 */

    /* Merge from the end while both arrays have elements */
    while (i >= 0 && j >= 0) {
        if (nums1[i] >= nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }

    /* If nums2 has remaining elements, copy them over */
    /* (If nums1 has remaining, they're already in place) */
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

/**
 * Helper function to print an array
 */
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]");
}

int main() {
    printf("Merge Sorted Array\n");
    printf("==================\n\n");

    /* Example 1: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3 */
    printf("Example 1:\n");
    int nums1_1[] = {1, 2, 3, 0, 0, 0};
    int nums2_1[] = {2, 5, 6};
    printf("Input: nums1 = ");
    printArray(nums1_1, 6);
    printf(", m = 3, nums2 = ");
    printArray(nums2_1, 3);
    printf(", n = 3\n");

    merge(nums1_1, 6, 3, nums2_1, 3, 3);
    printf("Output: ");
    printArray(nums1_1, 6);
    printf("\nExplanation: The arrays [1,2,3] and [2,5,6] merge to [1,2,2,3,5,6].\n\n");

    /* Example 2: nums1 = [1], m = 1, nums2 = [], n = 0 */
    printf("Example 2:\n");
    int nums1_2[] = {1};
    int nums2_2[] = {0};  /* Dummy - not accessed when n = 0 */
    printf("Input: nums1 = ");
    printArray(nums1_2, 1);
    printf(", m = 1, nums2 = []");
    printf(", n = 0\n");

    merge(nums1_2, 1, 1, nums2_2, 0, 0);
    printf("Output: ");
    printArray(nums1_2, 1);
    printf("\nExplanation: The arrays [1] and [] merge to [1].\n\n");

    /* Example 3: nums1 = [0], m = 0, nums2 = [1], n = 1 */
    printf("Example 3:\n");
    int nums1_3[] = {0};
    int nums2_3[] = {1};
    printf("Input: nums1 = ");
    printArray(nums1_3, 1);
    printf(", m = 0, nums2 = ");
    printArray(nums2_3, 1);
    printf(", n = 1\n");

    merge(nums1_3, 1, 0, nums2_3, 1, 1);
    printf("Output: ");
    printArray(nums1_3, 1);
    printf("\nExplanation: The arrays [] and [1] merge to [1].\n\n");

    /* Additional test cases */
    printf("Additional Test Cases:\n\n");

    /* Test 4: nums1 empty, nums2 has elements */
    printf("Test 4: nums1 = [0,0], m = 0, nums2 = [1,2]\n");
    int nums1_4[] = {0, 0};
    int nums2_4[] = {1, 2};
    merge(nums1_4, 2, 0, nums2_4, 2, 2);
    printf("Output: ");
    printArray(nums1_4, 2);
    printf("\n\n");

    /* Test 5: nums2 empty */
    printf("Test 5: nums1 = [1,2,3,0,0,0], m = 3, nums2 = []\n");
    int nums1_5[] = {1, 2, 3, 0, 0, 0};
    int nums2_5[] = {0};  /* Dummy - not accessed when n = 0 */
    merge(nums1_5, 6, 3, nums2_5, 0, 0);
    printf("Output: ");
    printArray(nums1_5, 6);
    printf("\n\n");

    /* Test 6: All nums2 elements larger than nums1 */
    printf("Test 6: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [4,5,6]\n");
    int nums1_6[] = {1, 2, 3, 0, 0, 0};
    int nums2_6[] = {4, 5, 6};
    merge(nums1_6, 6, 3, nums2_6, 3, 3);
    printf("Output: ");
    printArray(nums1_6, 6);
    printf("\n\n");

    /* Test 7: Interleaved elements */
    printf("Test 7: nums1 = [1,3,5,0,0,0], m = 3, nums2 = [2,4,6]\n");
    int nums1_7[] = {1, 3, 5, 0, 0, 0};
    int nums2_7[] = {2, 4, 6};
    merge(nums1_7, 6, 3, nums2_7, 3, 3);
    printf("Output: ");
    printArray(nums1_7, 6);
    printf("\n\n");

    return 0;
}
