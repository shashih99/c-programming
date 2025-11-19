#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Find the longest common prefix string amongst an array of strings
 * 
 * The algorithm compares characters at each position across all strings:
 * - Start from position 0
 * - Check if all strings have the same character at this position
 * - If they do, move to the next position
 * - If they don't, return the prefix found so far
 * - If any string ends, return the prefix found so far
 * 
 * Time Complexity: O(m * n) where m is the length of shortest string and n is number of strings
 * Space Complexity: O(m) for the result string
 * 
 * @param strs: Array of strings
 * @param strsSize: Number of strings in the array
 * @return: Longest common prefix (must be freed by caller)
 */
char* longestCommonPrefix(char** strs, int strsSize) {
    // Handle edge case: empty array
    if (strsSize == 0) {
        char *result = (char *)malloc(1);
        result[0] = '\0';
        return result;
    }
    
    // Find the minimum length among all strings
    int minLen = strlen(strs[0]);
    for (int i = 1; i < strsSize; i++) {
        int len = strlen(strs[i]);
        if (len < minLen) {
            minLen = len;
        }
    }
    
    // Allocate memory for the result (minLen + 1 for null terminator)
    char *result = (char *)malloc(minLen + 1);
    
    // Compare characters at each position
    for (int i = 0; i < minLen; i++) {
        char ch = strs[0][i];
        
        // Check if this character matches in all strings
        int match = 1;
        for (int j = 1; j < strsSize; j++) {
            if (strs[j][i] != ch) {
                match = 0;
                break;
            }
        }
        
        // If character doesn't match, we've found the end of common prefix
        if (!match) {
            result[i] = '\0';
            return result;
        }
        
        // Character matches in all strings, add it to result
        result[i] = ch;
    }
    
    // All characters up to minLen are common
    result[minLen] = '\0';
    return result;
}

/**
 * Test function with the provided examples
 */
int main() {
    // Example 1: strs = ["flower","flow","flight"]
    printf("Example 1:\n");
    char *strs1[] = {"flower", "flow", "flight"};
    int size1 = 3;
    char *result1 = longestCommonPrefix(strs1, size1);
    printf("Input: strs = [\"flower\",\"flow\",\"flight\"]\n");
    printf("Output: \"%s\"\n\n", result1);
    free(result1);
    
    // Example 2: strs = ["dog","racecar","car"]
    printf("Example 2:\n");
    char *strs2[] = {"dog", "racecar", "car"};
    int size2 = 3;
    char *result2 = longestCommonPrefix(strs2, size2);
    printf("Input: strs = [\"dog\",\"racecar\",\"car\"]\n");
    printf("Output: \"%s\"\n", result2);
    printf("Explanation: There is no common prefix among the input strings.\n\n");
    free(result2);
    
    // Additional test cases
    printf("Additional test cases:\n");
    
    // Test case 1: Single string
    char *strs3[] = {"hello"};
    char *result3 = longestCommonPrefix(strs3, 1);
    printf("strs = [\"hello\"]: \"%s\"\n", result3);
    free(result3);
    
    // Test case 2: All strings are the same
    char *strs4[] = {"abc", "abc", "abc"};
    char *result4 = longestCommonPrefix(strs4, 3);
    printf("strs = [\"abc\",\"abc\",\"abc\"]: \"%s\"\n", result4);
    free(result4);
    
    // Test case 3: Empty strings
    char *strs5[] = {"", "ab", "cd"};
    char *result5 = longestCommonPrefix(strs5, 3);
    printf("strs = [\"\",\"ab\",\"cd\"]: \"%s\"\n", result5);
    free(result5);
    
    // Test case 4: Two strings with common prefix
    char *strs6[] = {"interspecies", "interstellar", "interstate"};
    char *result6 = longestCommonPrefix(strs6, 3);
    printf("strs = [\"interspecies\",\"interstellar\",\"interstate\"]: \"%s\"\n", result6);
    free(result6);
    
    // Test case 5: No common prefix except empty
    char *strs7[] = {"ab", "ba"};
    char *result7 = longestCommonPrefix(strs7, 2);
    printf("strs = [\"ab\",\"ba\"]: \"%s\"\n", result7);
    free(result7);
    
    return 0;
}
