#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Add Binary
 * 
 * Given two binary strings a and b, return their sum as a binary string.
 * 
 * Algorithm:
 * 1. Start from the rightmost (least significant) bit of both strings
 * 2. Add corresponding bits along with any carry from previous addition
 * 3. Store the result bit (sum % 2) and update carry (sum / 2)
 * 4. Continue until both strings are processed
 * 5. If there's a final carry, add it to the result
 * 6. Reverse the result since we built it from right to left
 * 
 * Time Complexity: O(max(m, n)) where m and n are lengths of strings a and b
 * Space Complexity: O(max(m, n)) for the result string
 * 
 * @param a: First binary string
 * @param b: Second binary string
 * @return: Sum of a and b as a binary string (caller must free this memory)
 */
char* addBinary(const char* a, const char* b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = (lenA > lenB) ? lenA : lenB;
    
    // Allocate memory for result (maxLen + 2 for possible carry and null terminator)
    char* result = (char*)malloc((maxLen + 2) * sizeof(char));
    int resultIndex = 0;
    
    int i = lenA - 1;  // Index for string a (start from rightmost)
    int j = lenB - 1;  // Index for string b (start from rightmost)
    int carry = 0;
    
    // Process both strings from right to left
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        
        // Add bit from string a if available
        if (i >= 0) {
            sum += (a[i] - '0');
            i--;
        }
        
        // Add bit from string b if available
        if (j >= 0) {
            sum += (b[j] - '0');
            j--;
        }
        
        // Store the result bit (sum % 2)
        result[resultIndex++] = (sum % 2) + '0';
        
        // Update carry (sum / 2)
        carry = sum / 2;
    }
    
    // Null terminate the result
    result[resultIndex] = '\0';
    
    // Reverse the result since we built it from right to left
    for (int k = 0; k < resultIndex / 2; k++) {
        char temp = result[k];
        result[k] = result[resultIndex - 1 - k];
        result[resultIndex - 1 - k] = temp;
    }
    
    return result;
}

/**
 * Helper function to print test case results
 */
void printTestCase(const char* a, const char* b, const char* expected) {
    char* result = addBinary(a, b);
    printf("Input: a = \"%s\", b = \"%s\"\n", a, b);
    printf("Output: \"%s\"\n", result);
    if (expected != NULL) {
        printf("Expected: \"%s\"\n", expected);
        if (strcmp(result, expected) == 0) {
            printf("✓ Test PASSED\n");
        } else {
            printf("✗ Test FAILED\n");
        }
    }
    printf("\n");
    free(result);
}

int main() {
    printf("Add Binary Problem\n");
    printf("==================\n\n");
    
    // Example 1: a = "11", b = "1"
    printf("Example 1:\n");
    printTestCase("11", "1", "100");
    
    // Example 2: a = "1010", b = "1011"
    printf("Example 2:\n");
    printTestCase("1010", "1011", "10101");
    
    // Additional test cases
    printf("Additional Test Cases:\n\n");
    
    // Test case 3: a = "0", b = "0"
    printf("Test Case 3:\n");
    printTestCase("0", "0", "0");
    
    // Test case 4: a = "1", b = "1"
    printf("Test Case 4:\n");
    printTestCase("1", "1", "10");
    
    // Test case 5: a = "1111", b = "1111"
    printf("Test Case 5:\n");
    printTestCase("1111", "1111", "11110");
    
    // Test case 6: a = "100", b = "110010"
    printf("Test Case 6:\n");
    printTestCase("100", "110010", "110110");
    
    // Test case 7: Different lengths
    printf("Test Case 7:\n");
    printTestCase("1", "111", "1000");
    
    return 0;
}
