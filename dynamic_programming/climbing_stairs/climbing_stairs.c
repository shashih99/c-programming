#include <stdio.h>

/**
 * Climbing Stairs
 * 
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways
 * can you climb to the top?
 * 
 * Algorithm: Iterative Dynamic Programming
 * 
 * This problem follows the Fibonacci sequence pattern:
 * - To reach step n, you can come from step n-1 (taking 1 step) or step n-2 (taking 2 steps)
 * - Therefore: ways(n) = ways(n-1) + ways(n-2)
 * - Base cases: ways(1) = 1, ways(2) = 2
 * 
 * Instead of using recursion (which would be O(2^n) time), we use an iterative approach:
 * 1. Handle base cases: if n <= 2, return n
 * 2. Use two variables to track previous two values (prev2 and prev1)
 * 3. Iterate from 3 to n, computing current = prev1 + prev2
 * 4. Update prev2 and prev1 for next iteration
 * 
 * Time Complexity: O(n) - single pass through steps 3 to n
 * Space Complexity: O(1) - only using two variables to store previous values
 * 
 * @param n: Number of steps to reach the top (1 <= n <= 45)
 * @return: Number of distinct ways to climb to the top
 */
int climbStairs(int n) {
    // Base cases
    if (n <= 2) {
        return n;
    }
    
    // Initialize: ways to reach step 1 and step 2
    int prev2 = 1;  // ways to reach step 1
    int prev1 = 2;  // ways to reach step 2
    
    // Iterate from step 3 to step n
    for (int i = 3; i <= n; i++) {
        // Current ways = ways from (i-1) + ways from (i-2)
        int current = prev1 + prev2;
        
        // Update for next iteration
        prev2 = prev1;
        prev1 = current;
    }
    
    return prev1;
}

/**
 * Helper function to print test case results
 */
void printTestCase(int n, int expected) {
    int result = climbStairs(n);
    printf("Input: n = %d\n", n);
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
    printf("Climbing Stairs Problem\n");
    printf("=======================\n\n");
    
    // Example 1: n = 2
    printf("Example 1:\n");
    printTestCase(2, 2);
    
    // Example 2: n = 3
    printf("Example 2:\n");
    printTestCase(3, 3);
    
    // Additional test cases
    printf("Additional Test Cases:\n\n");
    
    // Test case 3: n = 1
    printf("Test Case 3:\n");
    printTestCase(1, 1);
    
    // Test case 4: n = 4
    printf("Test Case 4:\n");
    printTestCase(4, 5);
    
    // Test case 5: n = 5
    printf("Test Case 5:\n");
    printTestCase(5, 8);
    
    // Test case 6: n = 10
    printf("Test Case 6:\n");
    printTestCase(10, 89);
    
    return 0;
}
