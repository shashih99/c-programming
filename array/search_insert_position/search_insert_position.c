#include <stdio.h>

/**
 * Search Insert Position
 * 
 * Given a sorted array of distinct integers and a target value, return the index
 * if the target is found. If not, return the index where it would be if it were
 * inserted in order.
 * 
 * Algorithm: Binary Search
 * 1. Use binary search to find the target or the insertion position
 * 2. Maintain left and right pointers
 * 3. If target is found, return its index
 * 4. If target is not found, left will point to the insertion position
 * 
 * Time Complexity: O(log n) where n is the length of the array
 * Space Complexity: O(1) - only using a few variables
 * 
 * @param nums: Sorted array of distinct integers
 * @param numsSize: Size of the array
 * @param target: Target value to search for or insert
 * @return: Index where target is found or should be inserted
 */
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    
    // Binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            // Target found, return its index
            return mid;
        } else if (nums[mid] < target) {
            // Target is in the right half
            left = mid + 1;
        } else {
            // Target is in the left half
            right = mid - 1;
        }
    }
    
    // Target not found, left points to the insertion position
    return left;
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
 * Test function with the provided examples
 */
int main() {
    printf("Search Insert Position Problem\n");
    printf("==============================\n\n");
    
    // Example 1: nums = [1,3,5,6], target = 5
    printf("Example 1:\n");
    int nums1[] = {1, 3, 5, 6};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    int target1 = 5;
    
    printf("Input: nums = ");
    printArray(nums1, size1);
    printf(", target = %d\n", target1);
    
    int result1 = searchInsert(nums1, size1, target1);
    printf("Output: %d\n", result1);
    printf("Explanation: %d is found at index %d.\n\n", target1, result1);
    
    // Example 2: nums = [1,3,5,6], target = 2
    printf("Example 2:\n");
    int nums2[] = {1, 3, 5, 6};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    int target2 = 2;
    
    printf("Input: nums = ");
    printArray(nums2, size2);
    printf(", target = %d\n", target2);
    
    int result2 = searchInsert(nums2, size2, target2);
    printf("Output: %d\n", result2);
    printf("Explanation: %d is not found. If it were inserted, it would be at index %d.\n\n", target2, result2);
    
    // Example 3: nums = [1,3,5,6], target = 7
    printf("Example 3:\n");
    int nums3[] = {1, 3, 5, 6};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    int target3 = 7;
    
    printf("Input: nums = ");
    printArray(nums3, size3);
    printf(", target = %d\n", target3);
    
    int result3 = searchInsert(nums3, size3, target3);
    printf("Output: %d\n", result3);
    printf("Explanation: %d is not found. If it were inserted, it would be at index %d.\n\n", target3, result3);
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    printf("=====================\n\n");
    
    // Test 1: Target at the beginning
    printf("Test 1: Target at the beginning\n");
    int nums4[] = {1, 3, 5, 6};
    int size4 = sizeof(nums4) / sizeof(nums4[0]);
    int target4 = 0;
    
    printf("Input: nums = ");
    printArray(nums4, size4);
    printf(", target = %d\n", target4);
    
    int result4 = searchInsert(nums4, size4, target4);
    printf("Output: %d\n\n", result4);
    
    // Test 2: Target smaller than all elements
    printf("Test 2: Target smaller than all elements\n");
    int nums5[] = {2, 4, 6, 8};
    int size5 = sizeof(nums5) / sizeof(nums5[0]);
    int target5 = 1;
    
    printf("Input: nums = ");
    printArray(nums5, size5);
    printf(", target = %d\n", target5);
    
    int result5 = searchInsert(nums5, size5, target5);
    printf("Output: %d\n\n", result5);
    
    // Test 3: Target larger than all elements
    printf("Test 3: Target larger than all elements\n");
    int nums6[] = {1, 3, 5, 7};
    int size6 = sizeof(nums6) / sizeof(nums6[0]);
    int target6 = 9;
    
    printf("Input: nums = ");
    printArray(nums6, size6);
    printf(", target = %d\n", target6);
    
    int result6 = searchInsert(nums6, size6, target6);
    printf("Output: %d\n\n", result6);
    
    // Test 4: Single element array, target found
    printf("Test 4: Single element array, target found\n");
    int nums7[] = {5};
    int size7 = sizeof(nums7) / sizeof(nums7[0]);
    int target7 = 5;
    
    printf("Input: nums = ");
    printArray(nums7, size7);
    printf(", target = %d\n", target7);
    
    int result7 = searchInsert(nums7, size7, target7);
    printf("Output: %d\n\n", result7);
    
    // Test 5: Single element array, target not found (smaller)
    printf("Test 5: Single element array, target smaller\n");
    int nums8[] = {5};
    int size8 = sizeof(nums8) / sizeof(nums8[0]);
    int target8 = 2;
    
    printf("Input: nums = ");
    printArray(nums8, size8);
    printf(", target = %d\n", target8);
    
    int result8 = searchInsert(nums8, size8, target8);
    printf("Output: %d\n\n", result8);
    
    // Test 6: Single element array, target not found (larger)
    printf("Test 6: Single element array, target larger\n");
    int nums9[] = {5};
    int size9 = sizeof(nums9) / sizeof(nums9[0]);
    int target9 = 8;
    
    printf("Input: nums = ");
    printArray(nums9, size9);
    printf(", target = %d\n", target9);
    
    int result9 = searchInsert(nums9, size9, target9);
    printf("Output: %d\n\n", result9);
    
    // Test 7: Target in the middle (not found)
    printf("Test 7: Target in the middle (not found)\n");
    int nums10[] = {1, 3, 5, 7, 9};
    int size10 = sizeof(nums10) / sizeof(nums10[0]);
    int target10 = 4;
    
    printf("Input: nums = ");
    printArray(nums10, size10);
    printf(", target = %d\n", target10);
    
    int result10 = searchInsert(nums10, size10, target10);
    printf("Output: %d\n\n", result10);
    
    // Test 8: Target at first position (found)
    printf("Test 8: Target at first position (found)\n");
    int nums11[] = {1, 3, 5, 6};
    int size11 = sizeof(nums11) / sizeof(nums11[0]);
    int target11 = 1;
    
    printf("Input: nums = ");
    printArray(nums11, size11);
    printf(", target = %d\n", target11);
    
    int result11 = searchInsert(nums11, size11, target11);
    printf("Output: %d\n\n", result11);
    
    // Test 9: Target at last position (found)
    printf("Test 9: Target at last position (found)\n");
    int nums12[] = {1, 3, 5, 6};
    int size12 = sizeof(nums12) / sizeof(nums12[0]);
    int target12 = 6;
    
    printf("Input: nums = ");
    printArray(nums12, size12);
    printf(", target = %d\n", target12);
    
    int result12 = searchInsert(nums12, size12, target12);
    printf("Output: %d\n\n", result12);
    
    return 0;
}

