#include <stdio.h>
#include <stdbool.h>

/**
 * Check if an integer is a palindrome
 * 
 * A palindrome reads the same from left to right and right to left.
 * Negative numbers are not palindromes.
 * Numbers ending in 0 (except 0 itself) are not palindromes.
 * 
 * @param x: Integer to check
 * @return: true if x is a palindrome, false otherwise
 */
bool isPalindrome(int x) {
    // Negative numbers are not palindromes
    if (x < 0) {
        return false;
    }
    
    // Numbers ending in 0 (except 0 itself) are not palindromes
    if (x != 0 && x % 10 == 0) {
        return false;
    }
    
    // Reverse the number and compare
    int original = x;
    long reversed = 0;  // Use long to prevent overflow during reversal
    
    while (x > 0) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    
    return original == reversed;
}

/**
 * Test function with the provided examples
 */
int main() {
    // Example 1: x = 121
    printf("Example 1:\n");
    int x1 = 121;
    bool result1 = isPalindrome(x1);
    printf("Input: x = %d\n", x1);
    printf("Output: %s\n", result1 ? "true" : "false");
    printf("Explanation: %d reads as %d from left to right and from right to left.\n\n", x1, x1);
    
    // Example 2: x = -121
    printf("Example 2:\n");
    int x2 = -121;
    bool result2 = isPalindrome(x2);
    printf("Input: x = %d\n", x2);
    printf("Output: %s\n", result2 ? "true" : "false");
    printf("Explanation: From left to right, it reads %d. From right to left, it becomes %d-. Therefore it is not a palindrome.\n\n", x2, -x2);
    
    // Example 3: x = 10
    printf("Example 3:\n");
    int x3 = 10;
    bool result3 = isPalindrome(x3);
    printf("Input: x = %d\n", x3);
    printf("Output: %s\n", result3 ? "true" : "false");
    printf("Explanation: Reads 01 from right to left. Therefore it is not a palindrome.\n\n");
    
    // Additional test cases
    printf("Additional test cases:\n");
    printf("x = 0: %s\n", isPalindrome(0) ? "true" : "false");
    printf("x = 1: %s\n", isPalindrome(1) ? "true" : "false");
    printf("x = 1221: %s\n", isPalindrome(1221) ? "true" : "false");
    printf("x = 12321: %s\n", isPalindrome(12321) ? "true" : "false");
    printf("x = 123: %s\n", isPalindrome(123) ? "true" : "false");
    
    return 0;
}

