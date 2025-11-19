#include <stdio.h>
#include <string.h>

/**
 * Get the integer value of a Roman numeral character
 * 
 * @param c: Roman numeral character (I, V, X, L, C, D, M)
 * @return: Integer value of the character, 0 if invalid
 */
int getValue(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

/**
 * Convert a Roman numeral string to an integer
 * 
 * Roman numerals are usually written largest to smallest from left to right.
 * However, there are six instances where subtraction is used:
 * - I can be placed before V (5) and X (10) to make 4 and 9
 * - X can be placed before L (50) and C (100) to make 40 and 90
 * - C can be placed before D (500) and M (1000) to make 400 and 900
 * 
 * @param s: Roman numeral string (guaranteed to be valid)
 * @return: Integer value of the Roman numeral
 */
int romanToInt(char *s) {
    int result = 0;
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        int current = getValue(s[i]);
        
        // Check if we need to subtract (current value is less than next value)
        if (i + 1 < len) {
            int next = getValue(s[i + 1]);
            
            // If current value is less than next, subtract current from next
            if (current < next) {
                result += (next - current);
                i++; // Skip the next character as we've already processed it
                continue;
            }
        }
        
        // Otherwise, add the current value
        result += current;
    }
    
    return result;
}

/**
 * Test function with the provided examples
 */
int main() {
    // Example 1: s = "III"
    printf("Example 1:\n");
    char *s1 = "III";
    int result1 = romanToInt(s1);
    printf("Input: s = \"%s\"\n", s1);
    printf("Output: %d\n", result1);
    printf("Explanation: %s = %d.\n\n", s1, result1);
    
    // Example 2: s = "LVIII"
    printf("Example 2:\n");
    char *s2 = "LVIII";
    int result2 = romanToInt(s2);
    printf("Input: s = \"%s\"\n", s2);
    printf("Output: %d\n", result2);
    printf("Explanation: L = 50, V = 5, III = 3.\n\n");
    
    // Example 3: s = "MCMXCIV"
    printf("Example 3:\n");
    char *s3 = "MCMXCIV";
    int result3 = romanToInt(s3);
    printf("Input: s = \"%s\"\n", s3);
    printf("Output: %d\n", result3);
    printf("Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.\n\n");
    
    // Additional test cases
    printf("Additional test cases:\n");
    printf("s = \"I\": %d\n", romanToInt("I"));
    printf("s = \"IV\": %d\n", romanToInt("IV"));
    printf("s = \"IX\": %d\n", romanToInt("IX"));
    printf("s = \"XL\": %d\n", romanToInt("XL"));
    printf("s = \"XC\": %d\n", romanToInt("XC"));
    printf("s = \"CD\": %d\n", romanToInt("CD"));
    printf("s = \"CM\": %d\n", romanToInt("CM"));
    printf("s = \"MMMCMXCIX\": %d\n", romanToInt("MMMCMXCIX")); // 3999
    printf("s = \"XIV\": %d\n", romanToInt("XIV")); // 14
    printf("s = \"XXVII\": %d\n", romanToInt("XXVII")); // 27
    
    return 0;
}

