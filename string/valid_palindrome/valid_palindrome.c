#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/**
 * 125. Valid Palindrome
 *
 * A phrase is a palindrome if, after converting all uppercase letters into
 * lowercase letters and removing all non-alphanumeric characters, it reads the
 * same forward and backward. Alphanumeric characters include letters and
 * numbers.
 *
 * Given a string s, return true if it is a palindrome, or false otherwise.
 *
 * Algorithm (two pointers, in place):
 * 1. Start one pointer at the beginning and one at the end.
 * 2. Move each pointer inward past any non-alphanumeric characters.
 * 3. Compare the two characters case-insensitively; a mismatch means false.
 * 4. Step both pointers inward and repeat until they meet.
 *
 * Time Complexity: O(n) - each character is visited at most once
 * Space Complexity: O(1) - no cleaned copy of the string is built
 *
 * @param s: The input string (printable ASCII)
 * @return: true if s is a palindrome after cleaning, false otherwise
 */
bool isPalindrome(char* s) {
    int left = 0;
    int right = (int)strlen(s) - 1;

    while (left < right) {
        // Skip characters that are not letters or digits
        // (cast to unsigned char: passing a negative char to ctype is undefined)
        while (left < right && !isalnum((unsigned char)s[left])) {
            left++;
        }
        while (left < right && !isalnum((unsigned char)s[right])) {
            right--;
        }

        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

/**
 * Run one test case and report PASS/FAIL against the expected result
 */
void runTest(const char* name, char* s, bool expected) {
    bool result = isPalindrome(s);
    printf("%s:\n", name);
    printf("Input: s = \"%s\"\n", s);
    printf("Output: %s (expected %s) %s\n\n",
           result ? "true" : "false",
           expected ? "true" : "false",
           result == expected ? "PASS" : "FAIL");
}

int main() {
    printf("Valid Palindrome\n");
    printf("================\n\n");

    // Example 1: "amanaplanacanalpanama" -> true
    char s1[] = "A man, a plan, a canal: Panama";
    runTest("Example 1", s1, true);

    // Example 2: "raceacar" -> false
    char s2[] = "race a car";
    runTest("Example 2", s2, false);

    // Example 3: only a space -> empty after cleaning -> true
    char s3[] = " ";
    runTest("Example 3", s3, true);

    printf("Additional Test Cases:\n\n");

    // Digits count as alphanumeric: "0p" -> '0' != 'p'
    char s4[] = "0P";
    runTest("Test Case 4 (digit vs letter)", s4, false);

    // Only punctuation -> empty -> true
    char s5[] = ".,!?";
    runTest("Test Case 5 (only punctuation)", s5, true);

    // Single character
    char s6[] = "a";
    runTest("Test Case 6 (single char)", s6, true);

    // Mixed case and digits
    char s7[] = "No 'x' in Nixon";
    runTest("Test Case 7 (mixed case)", s7, true);

    // Numeric palindrome with separators
    char s8[] = "12-3-21";
    runTest("Test Case 8 (digits)", s8, true);

    // Almost a palindrome
    char s9[] = "ab_a b";
    runTest("Test Case 9 (near miss)", s9, false);

    return 0;
}
