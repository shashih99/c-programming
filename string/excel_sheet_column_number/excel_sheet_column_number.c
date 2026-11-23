#include <stdio.h>

/**
 * Excel Sheet Column Number (LeetCode 171)
 *
 * Given a string columnTitle that represents the column title as it appears
 * in an Excel sheet, return its corresponding column number.
 *
 *   A -> 1, B -> 2, ..., Z -> 26, AA -> 27, AB -> 28, ...
 *
 * Algorithm:
 * The title is a base-26 number whose digits run from 1 ('A') to 26 ('Z')
 * (there is no zero digit). Scan left to right, and for each character:
 *     result = result * 26 + (c - 'A' + 1)
 *
 * Time Complexity:  O(n), where n is the length of columnTitle
 * Space Complexity: O(1)
 *
 * Constraints: 1 <= length <= 7, uppercase letters only, and the
 * answer fits in the range [1, "FXSHRXW"] = [1, 2^31 - 1], so int is enough.
 *
 * @param columnTitle: Column title such as "A", "AB", "ZY"
 * @return: The column number
 */
int titleToNumber(const char* columnTitle) {
    int result = 0;
    while (*columnTitle) {
        result = result * 26 + (*columnTitle - 'A' + 1);
        columnTitle++;
    }
    return result;
}

int main(void) {
    struct {
        const char* input;
        int expected;
    } tests[] = {
        {"A", 1},
        {"Z", 26},
        {"AA", 27},
        {"AB", 28},
        {"AZ", 52},
        {"ZY", 701},
        {"ZZ", 702},
        {"AAA", 703},
        {"FXSHRXW", 2147483647},  /* largest valid input (INT_MAX) */
    };
    int numTests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < numTests; i++) {
        int result = titleToNumber(tests[i].input);
        int ok = (result == tests[i].expected);
        passed += ok;
        printf("[%s] Input: \"%s\" => Output: %d (expected %d)\n",
               ok ? "PASS" : "FAIL", tests[i].input, result, tests[i].expected);
    }

    printf("\n%d/%d tests passed\n", passed, numTests);
    return passed == numTests ? 0 : 1;
}
