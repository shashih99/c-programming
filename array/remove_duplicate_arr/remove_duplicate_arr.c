#include <stdio.h>
#include <stdlib.h>

/**
 * Remove duplicates from sorted array in-place
 * 
 * Algorithm:
 * 1. Use two pointers: one (write) for the position to write unique elements,
 *    and one (read) to scan through the array
 * 2. Since the array is sorted, duplicates will be adjacent
 * 3. Compare current element with the last written unique element
 * 4. If different, write it to the next position
 * 5. Return the count of unique elements
 * 
 * Time Complexity: O(n) where n is the length of the array
 * Space Complexity: O(1) - only using a few pointers, modifying array in-place
 * 
 * @param nums: Sorted array of integers (will be modified in-place)
 * @param numsSize: Size of the array
 * @return: Number of unique elements (k)
 */
int removeDuplicates(int* nums, int numsSize) {
    // Handle edge case: empty array
    if (numsSize == 0) {
        return 0;
    }
    
    // Pointer for writing unique elements (starts at index 1)
    int write = 1;
    
    // Scan through the array starting from index 1
    for (int read = 1; read < numsSize; read++) {
        // If current element is different from the last written unique element
        if (nums[read] != nums[write - 1]) {
            // Write it to the current write position
            nums[write] = nums[read];
            write++;
        }
        // If it's a duplicate, just skip it (don't increment write)
    }
    
    // Return the number of unique elements
    return write;
}

/**
 * Helper function to print an array
 */
void printArray(int* nums, int size) {
    if (size == 0) {
        printf("[]");
        return;
    }
    
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", nums[i]);
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]");
}

/**
 * Helper function to copy an array (for testing without modifying original)
 */
int* copyArray(int* nums, int size) {
    int* copy = (int*)malloc(size * sizeof(int));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        copy[i] = nums[i];
    }
    return copy;
}

/**
 * Test function with the provided examples
 */
int main() {
    printf("Remove Duplicates from Sorted Array Problem\n");
    printf("===========================================\n\n");
    
    // Example 1: nums = [1,1,2]
    printf("Example 1:\n");
    int nums1[] = {1, 1, 2};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int* copy1 = copyArray(nums1, size1);
    
    printf("Input: nums = ");
    printArray(copy1, size1);
    printf("\n");
    
    int k1 = removeDuplicates(copy1, size1);
    printf("Output: k = %d, nums = ", k1);
    printArray(copy1, k1);
    printf("\n");
    printf("Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.\n");
    printf("It does not matter what you leave beyond the returned k (hence they are underscores).\n\n");
    
    free(copy1);
    
    // Example 2: nums = [0,0,1,1,1,2,2,3,3,4]
    printf("Example 2:\n");
    int nums2[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    int* copy2 = copyArray(nums2, size2);
    
    printf("Input: nums = ");
    printArray(copy2, size2);
    printf("\n");
    
    int k2 = removeDuplicates(copy2, size2);
    printf("Output: k = %d, nums = ", k2);
    printArray(copy2, k2);
    printf("\n");
    printf("Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.\n");
    printf("It does not matter what you leave beyond the returned k (hence they are underscores).\n\n");
    
    free(copy2);
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    printf("=====================\n\n");
    
    // Test 1: Single element
    printf("Test 1: Single element\n");
    int nums3[] = {1};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    int* copy3 = copyArray(nums3, size3);
    
    printf("Input: nums = ");
    printArray(copy3, size3);
    printf("\n");
    
    int k3 = removeDuplicates(copy3, size3);
    printf("Output: k = %d, nums = ", k3);
    printArray(copy3, k3);
    printf("\n\n");
    
    free(copy3);
    
    // Test 2: All duplicates
    printf("Test 2: All duplicates\n");
    int nums4[] = {1, 1, 1, 1, 1};
    int size4 = sizeof(nums4) / sizeof(nums4[0]);
    int* copy4 = copyArray(nums4, size4);
    
    printf("Input: nums = ");
    printArray(copy4, size4);
    printf("\n");
    
    int k4 = removeDuplicates(copy4, size4);
    printf("Output: k = %d, nums = ", k4);
    printArray(copy4, k4);
    printf("\n\n");
    
    free(copy4);
    
    // Test 3: No duplicates
    printf("Test 3: No duplicates\n");
    int nums5[] = {1, 2, 3, 4, 5};
    int size5 = sizeof(nums5) / sizeof(nums5[0]);
    int* copy5 = copyArray(nums5, size5);
    
    printf("Input: nums = ");
    printArray(copy5, size5);
    printf("\n");
    
    int k5 = removeDuplicates(copy5, size5);
    printf("Output: k = %d, nums = ", k5);
    printArray(copy5, k5);
    printf("\n\n");
    
    free(copy5);
    
    // Test 4: Empty array
    printf("Test 4: Empty array\n");
    int* nums6 = NULL;
    int size6 = 0;
    
    printf("Input: nums = ");
    printArray(nums6, size6);
    printf("\n");
    
    int k6 = removeDuplicates(nums6, size6);
    printf("Output: k = %d, nums = ", k6);
    printArray(nums6, k6);
    printf("\n\n");
    
    // Test 5: Negative numbers
    printf("Test 5: Negative numbers\n");
    int nums7[] = {-5, -5, -3, -3, -1, 0, 0, 2, 2};
    int size7 = sizeof(nums7) / sizeof(nums7[0]);
    int* copy7 = copyArray(nums7, size7);
    
    printf("Input: nums = ");
    printArray(copy7, size7);
    printf("\n");
    
    int k7 = removeDuplicates(copy7, size7);
    printf("Output: k = %d, nums = ", k7);
    printArray(copy7, k7);
    printf("\n\n");
    
    free(copy7);
    
    // Test 6: Large array with many duplicates
    printf("Test 6: Large array with many duplicates\n");
    int nums8[] = {1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 5};
    int size8 = sizeof(nums8) / sizeof(nums8[0]);
    int* copy8 = copyArray(nums8, size8);
    
    printf("Input: nums = ");
    printArray(copy8, size8);
    printf("\n");
    
    int k8 = removeDuplicates(copy8, size8);
    printf("Output: k = %d, nums = ", k8);
    printArray(copy8, k8);
    printf("\n\n");
    
    free(copy8);
    
    return 0;
}

