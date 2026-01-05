#include <stdio.h>
#include <string.h>

/**
 * Length of Last Word
 * 
 * Given a string s consisting of words and spaces, return the length of the last word in the string.
 * A word is a maximal substring consisting of non-space characters only.
 * 
 * Algorithm:
 * 1. Start from the end of the string
 * 2. Skip all trailing spaces
 * 3. Count characters until we encounter a space or reach the beginning
 * 
 * Time Complexity: O(n) worst case, but often better if there are trailing spaces
 *                  where n is the length of the string
 * Space Complexity: O(1) - only using a few variables
 * 
 * @param s: The input string (null-terminated)
 * @return: The length of the last word
 */
int lengthOfLastWord(char *s) {
    int length = 0;
    int i = strlen(s) - 1;
    
    // Skip trailing spaces
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    
    // Count characters of the last word
    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }
    
    return length;
}

int main() {
    printf("Length of Last Word Problem\n");
    printf("============================\n\n");

    // Example 1: s = "Hello World"
    printf("Example 1:\n");
    char *s1 = "Hello World";
    int result1 = lengthOfLastWord(s1);
    printf("Input: s = \"%s\"\n", s1);
    printf("Output: %d\n", result1);
    printf("Explanation: The last word is \"World\" with length 5.\n\n");
    
    // Example 2: s = "   fly me   to   the moon  "
    printf("Example 2:\n");
    char *s2 = "   fly me   to   the moon  ";
    int result2 = lengthOfLastWord(s2);
    printf("Input: s = \"%s\"\n", s2);
    printf("Output: %d\n", result2);
    printf("Explanation: The last word is \"moon\" with length 4.\n\n");
    
    // Example 3: s = "luffy is still joyboy"
    printf("Example 3:\n");
    char *s3 = "luffy is still joyboy";
    int result3 = lengthOfLastWord(s3);
    printf("Input: s = \"%s\"\n", s3);
    printf("Output: %d\n", result3);
    printf("Explanation: The last word is \"joyboy\" with length 6.\n\n");
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    
    // Single word
    char *s4 = "Hello";
    int result4 = lengthOfLastWord(s4);
    printf("Input: \"%s\" -> Output: %d\n", s4, result4);
    
    // Single character
    char *s5 = "a";
    int result5 = lengthOfLastWord(s5);
    printf("Input: \"%s\" -> Output: %d\n", s5, result5);
    
    // Word with trailing spaces
    char *s6 = "test    ";
    int result6 = lengthOfLastWord(s6);
    printf("Input: \"%s\" -> Output: %d\n", s6, result6);
    
    return 0;
}