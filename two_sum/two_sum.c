#include <stdio.h>
#include <stdlib.h>

/**
 * Find two indices in nums such that nums[i] + nums[j] == target
 * Uses brute force approach: O(n²) time complexity
 * 
 * @param nums: Array of integers
 * @param numsSize: Size of the array
 * @param target: Target sum
 * @param returnSize: Pointer to store the size of the returned array (will be set to 2)
 * @return: Array of two indices, or NULL on failure
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    
    // Brute force: check all pairs
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    
    // Should not reach here if input is valid (guaranteed one solution)
    return result;
}

/**
 * Test function with the provided examples
 */
int main() {
    int returnSize;
    int* result;
    
    // Example 1: nums = [2,7,11,15], target = 9
    printf("Example 1:\n");
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    result = twoSum(nums1, 4, target1, &returnSize);
    if (result != NULL) {
        printf("Input: nums = [2,7,11,15], target = %d\n", target1);
        printf("Output: [%d,%d]\n", result[0], result[1]);
        printf("Explanation: nums[%d] + nums[%d] = %d + %d = %d\n\n", 
               result[0], result[1], nums1[result[0]], nums1[result[1]], target1);
        free(result);
    }
    
    // Example 2: nums = [3,2,4], target = 6
    printf("Example 2:\n");
    int nums2[] = {3, 2, 4};
    int target2 = 6;
    result = twoSum(nums2, 3, target2, &returnSize);
    if (result != NULL) {
        printf("Input: nums = [3,2,4], target = %d\n", target2);
        printf("Output: [%d,%d]\n", result[0], result[1]);
        printf("Explanation: nums[%d] + nums[%d] = %d + %d = %d\n\n", 
               result[0], result[1], nums2[result[0]], nums2[result[1]], target2);
        free(result);
    }
    
    // Example 3: nums = [3,3], target = 6
    printf("Example 3:\n");
    int nums3[] = {3, 3};
    int target3 = 6;
    result = twoSum(nums3, 2, target3, &returnSize);
    if (result != NULL) {
        printf("Input: nums = [3,3], target = %d\n", target3);
        printf("Output: [%d,%d]\n", result[0], result[1]);
        printf("Explanation: nums[%d] + nums[%d] = %d + %d = %d\n\n", 
               result[0], result[1], nums3[result[0]], nums3[result[1]], target3);
        free(result);
    }
    
    return 0;
}

