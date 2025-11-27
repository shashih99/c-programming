#include <stdio.h>
#include <stdlib.h>

/**
 * Remove all occurrences of val from array in-place
 * 
 * Algorithm:
 * 1. Use two pointers: one (write) for the position to write valid elements,
 *    and one (read) to scan through the array
 * 2. For each element, check if it's not equal to val
 * 3. If it's valid (not equal to val), write it to the current write position
 * 4. Increment write pointer only when we write a valid element
 * 5. Return the count of valid elements (k)
 * 
 * Time Complexity: O(n) where n is the length of the array
 * Space Complexity: O(1) - only using a few pointers, modifying array in-place
 * 
 * @param nums: Array of integers (will be modified in-place)
 * @param numsSize: Size of the array
 * @param val: Value to remove from the array
 * @return: Number of elements not equal to val (k)
 */
int removeElement(int* nums, int numsSize, int val) {
    // Pointer for writing valid elements (starts at index 0)
    int write = 0;
    
    // Scan through the array
    for (int read = 0; read < numsSize; read++) {
        // If current element is not equal to val, it's valid
        if (nums[read] != val) {
            // Write it to the current write position
            nums[write] = nums[read];
            write++;
        }
        // If it equals val, just skip it (don't increment write)
    }
    
    // Return the number of valid elements
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
    printf("Remove Element Problem\n");
    printf("======================\n\n");
    
    // Example 1: nums = [3,2,2,3], val = 3
    printf("Example 1:\n");
    int nums1[] = {3, 2, 2, 3};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int val1 = 3;
    int* copy1 = copyArray(nums1, size1);
    
    printf("Input: nums = ");
    printArray(copy1, size1);
    printf(", val = %d\n", val1);
    
    int k1 = removeElement(copy1, size1, val1);
    printf("Output: k = %d, nums = ", k1);
    printArray(copy1, k1);
    printf("\n");
    printf("Explanation: Your function should return k = 2, with the first two elements of nums being 2.\n");
    printf("It does not matter what you leave beyond the returned k (hence they are underscores).\n\n");
    
    free(copy1);
    
    // Example 2: nums = [0,1,2,2,3,0,4,2], val = 2
    printf("Example 2:\n");
    int nums2[] = {0, 1, 2, 2, 3, 0, 4, 2};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    int val2 = 2;
    int* copy2 = copyArray(nums2, size2);
    
    printf("Input: nums = ");
    printArray(copy2, size2);
    printf(", val = %d\n", val2);
    
    int k2 = removeElement(copy2, size2, val2);
    printf("Output: k = %d, nums = ", k2);
    printArray(copy2, k2);
    printf("\n");
    printf("Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.\n");
    printf("Note that the five elements can be returned in any order.\n");
    printf("It does not matter what you leave beyond the returned k (hence they are underscores).\n\n");
    
    free(copy2);
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    printf("=====================\n\n");
    
    // Test 1: Single element, matches val
    printf("Test 1: Single element matching val\n");
    int nums3[] = {3};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    int val3 = 3;
    int* copy3 = copyArray(nums3, size3);
    
    printf("Input: nums = ");
    printArray(copy3, size3);
    printf(", val = %d\n", val3);
    
    int k3 = removeElement(copy3, size3, val3);
    printf("Output: k = %d, nums = ", k3);
    printArray(copy3, k3);
    printf("\n\n");
    
    free(copy3);
    
    // Test 2: Single element, doesn't match val
    printf("Test 2: Single element not matching val\n");
    int nums4[] = {3};
    int size4 = sizeof(nums4) / sizeof(nums4[0]);
    int val4 = 2;
    int* copy4 = copyArray(nums4, size4);
    
    printf("Input: nums = ");
    printArray(copy4, size4);
    printf(", val = %d\n", val4);
    
    int k4 = removeElement(copy4, size4, val4);
    printf("Output: k = %d, nums = ", k4);
    printArray(copy4, k4);
    printf("\n\n");
    
    free(copy4);
    
    // Test 3: All elements match val
    printf("Test 3: All elements match val\n");
    int nums5[] = {2, 2, 2, 2, 2};
    int size5 = sizeof(nums5) / sizeof(nums5[0]);
    int val5 = 2;
    int* copy5 = copyArray(nums5, size5);
    
    printf("Input: nums = ");
    printArray(copy5, size5);
    printf(", val = %d\n", val5);
    
    int k5 = removeElement(copy5, size5, val5);
    printf("Output: k = %d, nums = ", k5);
    printArray(copy5, k5);
    printf("\n\n");
    
    free(copy5);
    
    // Test 4: No elements match val
    printf("Test 4: No elements match val\n");
    int nums6[] = {1, 2, 3, 4, 5};
    int size6 = sizeof(nums6) / sizeof(nums6[0]);
    int val6 = 6;
    int* copy6 = copyArray(nums6, size6);
    
    printf("Input: nums = ");
    printArray(copy6, size6);
    printf(", val = %d\n", val6);
    
    int k6 = removeElement(copy6, size6, val6);
    printf("Output: k = %d, nums = ", k6);
    printArray(copy6, k6);
    printf("\n\n");
    
    free(copy6);
    
    // Test 5: Empty array
    printf("Test 5: Empty array\n");
    int* nums7 = NULL;
    int size7 = 0;
    int val7 = 3;
    
    printf("Input: nums = ");
    printArray(nums7, size7);
    printf(", val = %d\n", val7);
    
    int k7 = removeElement(nums7, size7, val7);
    printf("Output: k = %d, nums = ", k7);
    printArray(nums7, k7);
    printf("\n\n");
    
    // Test 6: Val at beginning and end
    printf("Test 6: Val at beginning and end\n");
    int nums8[] = {3, 1, 2, 3, 4, 3};
    int size8 = sizeof(nums8) / sizeof(nums8[0]);
    int val8 = 3;
    int* copy8 = copyArray(nums8, size8);
    
    printf("Input: nums = ");
    printArray(copy8, size8);
    printf(", val = %d\n", val8);
    
    int k8 = removeElement(copy8, size8, val8);
    printf("Output: k = %d, nums = ", k8);
    printArray(copy8, k8);
    printf("\n\n");
    
    free(copy8);
    
    // Test 7: Val in middle only
    printf("Test 7: Val in middle only\n");
    int nums9[] = {1, 2, 3, 4, 5};
    int size9 = sizeof(nums9) / sizeof(nums9[0]);
    int val9 = 3;
    int* copy9 = copyArray(nums9, size9);
    
    printf("Input: nums = ");
    printArray(copy9, size9);
    printf(", val = %d\n", val9);
    
    int k9 = removeElement(copy9, size9, val9);
    printf("Output: k = %d, nums = ", k9);
    printArray(copy9, k9);
    printf("\n\n");
    
    free(copy9);
    
    return 0;
}

