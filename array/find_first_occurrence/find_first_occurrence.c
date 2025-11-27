#include <stdio.h>
#include <string.h>

/**
 * Find the index of the first occurrence of needle in haystack
 * 
 * Algorithm:
 * 1. Iterate through each possible starting position in haystack
 * 2. For each position, check if needle matches starting from that position
 * 3. Return the first matching index, or -1 if not found
 * 
 * Time Complexity: O(n * m) where n is haystack length and m is needle length
 * Space Complexity: O(1) - only using a few variables
 * 
 * @param haystack: The string to search in
 * @param needle: The string to search for
 * @return: Index of first occurrence of needle in haystack, or -1 if not found
 */
int strStr(char* haystack, char* needle) {
    int haystackLen = strlen(haystack);
    int needleLen = strlen(needle);
    
    // Edge case: if needle is empty, return 0
    if (needleLen == 0) {
        return 0;
    }
    
    // Edge case: if needle is longer than haystack, it can't be found
    if (needleLen > haystackLen) {
        return -1;
    }
    
    // Try each possible starting position in haystack
    for (int i = 0; i <= haystackLen - needleLen; i++) {
        int j = 0;
        // Check if needle matches starting from position i
        while (j < needleLen && haystack[i + j] == needle[j]) {
            j++;
        }
        // If we matched all characters of needle, return the starting index
        if (j == needleLen) {
            return i;
        }
    }
    
    // Needle not found
    return -1;
}

/**
 * Test function with the provided examples
 */
int main() {
    printf("Find First Occurrence Problem\n");
    printf("==============================\n\n");
    
    // Example 1: haystack = "sadbutsad", needle = "sad"
    printf("Example 1:\n");
    char haystack1[] = "sadbutsad";
    char needle1[] = "sad";
    int result1 = strStr(haystack1, needle1);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack1, needle1);
    printf("Output: %d\n", result1);
    printf("Explanation: \"%s\" occurs at index %d and 6. The first occurrence is at index %d, so we return %d.\n\n", 
           needle1, result1, result1, result1);
    
    // Example 2: haystack = "leetcode", needle = "leeto"
    printf("Example 2:\n");
    char haystack2[] = "leetcode";
    char needle2[] = "leeto";
    int result2 = strStr(haystack2, needle2);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack2, needle2);
    printf("Output: %d\n", result2);
    printf("Explanation: \"%s\" did not occur in \"%s\", so we return %d.\n\n", 
           needle2, haystack2, result2);
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    printf("=====================\n\n");
    
    // Test 1: Needle at the beginning
    printf("Test 1: Needle at the beginning\n");
    char haystack3[] = "hello";
    char needle3[] = "he";
    int result3 = strStr(haystack3, needle3);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack3, needle3);
    printf("Output: %d\n\n", result3);
    
    // Test 2: Needle at the end
    printf("Test 2: Needle at the end\n");
    char haystack4[] = "hello";
    char needle4[] = "lo";
    int result4 = strStr(haystack4, needle4);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack4, needle4);
    printf("Output: %d\n\n", result4);
    
    // Test 3: Needle in the middle
    printf("Test 3: Needle in the middle\n");
    char haystack5[] = "hello";
    char needle5[] = "ll";
    int result5 = strStr(haystack5, needle5);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack5, needle5);
    printf("Output: %d\n\n", result5);
    
    // Test 4: Single character match
    printf("Test 4: Single character match\n");
    char haystack6[] = "a";
    char needle6[] = "a";
    int result6 = strStr(haystack6, needle6);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack6, needle6);
    printf("Output: %d\n\n", result6);
    
    // Test 5: Empty needle (edge case)
    printf("Test 5: Empty needle\n");
    char haystack7[] = "hello";
    char needle7[] = "";
    int result7 = strStr(haystack7, needle7);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack7, needle7);
    printf("Output: %d\n\n", result7);
    
    // Test 6: Needle longer than haystack
    printf("Test 6: Needle longer than haystack\n");
    char haystack8[] = "hi";
    char needle8[] = "hello";
    int result8 = strStr(haystack8, needle8);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack8, needle8);
    printf("Output: %d\n\n", result8);
    
    // Test 7: Multiple occurrences (should return first)
    printf("Test 7: Multiple occurrences\n");
    char haystack9[] = "mississippi";
    char needle9[] = "issi";
    int result9 = strStr(haystack9, needle9);
    printf("Input: haystack = \"%s\", needle = \"%s\"\n", haystack9, needle9);
    printf("Output: %d\n", result9);
    printf("Explanation: \"%s\" occurs at index %d and 4. The first occurrence is at index %d.\n\n", 
           needle9, result9, result9);
    
    return 0;
}

