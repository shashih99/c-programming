#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Plus One
 * 
 * You are given a large integer represented as an integer array digits, where each 
 * digits[i] is the ith digit of the integer. The digits are ordered from most 
 * significant to least significant in left-to-right order. The large integer does 
 * not contain any leading 0's.
 * 
 * Increment the large integer by one and return the resulting array of digits.
 * 
 * Algorithm:
 * 1. Start from the rightmost digit (least significant)
 * 2. Add 1 to the current digit
 * 3. If the digit becomes 10, set it to 0 and carry over 1 to the next digit
 * 4. Continue until no carry remains
 * 5. If all digits were 9, create a new array with size + 1, set first digit to 1
 * 
 * Time Complexity: O(n) where n is the number of digits
 * Space Complexity: O(1) for in-place modification, O(n) if new array needed
 * 
 * @param digits: The input array of digits
 * @param digitsSize: The size of the digits array
 * @param returnSize: Pointer to store the size of the returned array
 * @return: The resulting array of digits after incrementing by one
 */
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    // Start from the rightmost digit
    int i = digitsSize - 1;
    
    // Add 1 to the rightmost digit
    digits[i] += 1;
    
    // Handle carry propagation
    while (i > 0 && digits[i] == 10) {
        digits[i] = 0;
        digits[i - 1] += 1;
        i--;
    }
    
    // Check if we need a new array (all digits were 9)
    if (digits[0] == 10) {
        // All digits were 9, need a new array with size + 1
        int* result = (int*)malloc((digitsSize + 1) * sizeof(int));
        result[0] = 1;
        for (int j = 1; j <= digitsSize; j++) {
            result[j] = 0;
        }
        *returnSize = digitsSize + 1;
        return result;
    }
    
    // No new array needed, return the modified input array
    *returnSize = digitsSize;
    return digits;
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

/**
 * Helper function to create a copy of an array for testing
 */
int* copyArray(int* arr, int size) {
    int* copy = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        copy[i] = arr[i];
    }
    return copy;
}

int main() {
    printf("Plus One Problem\n");
    printf("================\n\n");

    // Example 1: digits = [1,2,3]
    printf("Example 1:\n");
    int digits1[] = {1, 2, 3};
    int size1 = sizeof(digits1) / sizeof(digits1[0]);
    int* copy1 = copyArray(digits1, size1);
    int returnSize1;
    int* result1 = plusOne(copy1, size1, &returnSize1);
    printf("Input: ");
    printArray(digits1, size1);
    printf("\nOutput: ");
    printArray(result1, returnSize1);
    printf("\nExplanation: The array represents the integer 123.\n");
    printf("Incrementing by one gives 123 + 1 = 124.\n");
    printf("Thus, the result should be [1,2,4].\n\n");
    if (returnSize1 > size1) {
        free(result1);
    }
    free(copy1);

    // Example 2: digits = [4,3,2,1]
    printf("Example 2:\n");
    int digits2[] = {4, 3, 2, 1};
    int size2 = sizeof(digits2) / sizeof(digits2[0]);
    int* copy2 = copyArray(digits2, size2);
    int returnSize2;
    int* result2 = plusOne(copy2, size2, &returnSize2);
    printf("Input: ");
    printArray(digits2, size2);
    printf("\nOutput: ");
    printArray(result2, returnSize2);
    printf("\nExplanation: The array represents the integer 4321.\n");
    printf("Incrementing by one gives 4321 + 1 = 4322.\n");
    printf("Thus, the result should be [4,3,2,2].\n\n");
    if (returnSize2 > size2) {
        free(result2);
    }
    free(copy2);

    // Example 3: digits = [9]
    printf("Example 3:\n");
    int digits3[] = {9};
    int size3 = sizeof(digits3) / sizeof(digits3[0]);
    int* copy3 = copyArray(digits3, size3);
    int returnSize3;
    int* result3 = plusOne(copy3, size3, &returnSize3);
    printf("Input: ");
    printArray(digits3, size3);
    printf("\nOutput: ");
    printArray(result3, returnSize3);
    printf("\nExplanation: The array represents the integer 9.\n");
    printf("Incrementing by one gives 9 + 1 = 10.\n");
    printf("Thus, the result should be [1,0].\n\n");
    if (returnSize3 > size3) {
        free(result3);
    }
    free(copy3);

    // Additional test cases
    printf("Additional Test Cases:\n\n");

    // Test case 4: digits = [9, 9, 9]
    printf("Test Case 4:\n");
    int digits4[] = {9, 9, 9};
    int size4 = sizeof(digits4) / sizeof(digits4[0]);
    int* copy4 = copyArray(digits4, size4);
    int returnSize4;
    int* result4 = plusOne(copy4, size4, &returnSize4);
    printf("Input: ");
    printArray(digits4, size4);
    printf(" -> Output: ");
    printArray(result4, returnSize4);
    printf("\n\n");
    if (returnSize4 > size4) {
        free(result4);
    }
    free(copy4);

    // Test case 5: digits = [1, 9, 9]
    printf("Test Case 5:\n");
    int digits5[] = {1, 9, 9};
    int size5 = sizeof(digits5) / sizeof(digits5[0]);
    int* copy5 = copyArray(digits5, size5);
    int returnSize5;
    int* result5 = plusOne(copy5, size5, &returnSize5);
    printf("Input: ");
    printArray(digits5, size5);
    printf(" -> Output: ");
    printArray(result5, returnSize5);
    printf("\n\n");
    if (returnSize5 > size5) {
        free(result5);
    }
    free(copy5);

    // Test case 6: digits = [0]
    printf("Test Case 6:\n");
    int digits6[] = {0};
    int size6 = sizeof(digits6) / sizeof(digits6[0]);
    int* copy6 = copyArray(digits6, size6);
    int returnSize6;
    int* result6 = plusOne(copy6, size6, &returnSize6);
    printf("Input: ");
    printArray(digits6, size6);
    printf(" -> Output: ");
    printArray(result6, returnSize6);
    printf("\n\n");
    if (returnSize6 > size6) {
        free(result6);
    }
    free(copy6);

    return 0;
}

