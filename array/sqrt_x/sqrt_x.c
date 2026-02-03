#include <stdio.h>

/**
 * Sqrt(x)
 * 
 * Given a non-negative integer x, return the square root of x rounded down
 * to the nearest integer.
 * 
 * Algorithm: Binary Search
 * 1. Search in the range [0, x]
 * 2. For a mid value, compare mid * mid with x (use long long to avoid overflow)
 * 3. If mid * mid <= x, move right to find a larger valid square root
 * 4. If mid * mid > x, move left
 * 
 * Time Complexity: O(log x)
 * Space Complexity: O(1)
 * 
 * @param x: Non-negative integer
 * @return: Floor of the square root of x
 */
int mySqrt(int x) {
    if (x < 2) {
        return x;
    }
    
    int left = 1;
    int right = x / 2;
    int answer = 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long square = (long long)mid * mid;
        
        if (square == x) {
            return mid;
        } else if (square < x) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return answer;
}

/**
 * Helper function to print test case results
 */
void printTestCase(int x, int expected) {
    int result = mySqrt(x);
    printf("Input: x = %d\n", x);
    printf("Output: %d\n", result);
    printf("Expected: %d\n", expected);
    if (result == expected) {
        printf("✓ Test PASSED\n");
    } else {
        printf("✗ Test FAILED\n");
    }
    printf("\n");
}

int main() {
    printf("Sqrt(x) Problem\n");
    printf("===============\n\n");
    
    // Example 1: x = 4
    printf("Example 1:\n");
    printTestCase(4, 2);
    
    // Example 2: x = 8
    printf("Example 2:\n");
    printTestCase(8, 2);
    
    // Additional test cases
    printf("Additional Test Cases:\n\n");
    
    // Test case 3: x = 0
    printf("Test Case 3:\n");
    printTestCase(0, 0);
    
    // Test case 4: x = 1
    printf("Test Case 4:\n");
    printTestCase(1, 1);
    
    // Test case 5: perfect square
    printf("Test Case 5:\n");
    printTestCase(16, 4);
    
    // Test case 6: large non-square
    printf("Test Case 6:\n");
    printTestCase(27, 5);
    
    // Test case 7: large value
    printf("Test Case 7:\n");
    printTestCase(2147395599, 46339);
    
    return 0;
}
