#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Excel Sheet Column Title (LeetCode 168)
 *
 * Given an integer columnNumber, return its corresponding column title as it
 * appears in an Excel sheet.
 *
 *   1 -> A, 2 -> B, ..., 26 -> Z, 27 -> AA, 28 -> AB, ...
 *
 * Algorithm:
 * The title is a base-26 number whose digits run from 1 ('A') to 26 ('Z'),
 * with no zero digit. Subtracting 1 before each step shifts the digit into
 * the usual 0..25 range:
 *     columnNumber--
 *     letter       = 'A' + columnNumber % 26
 *     columnNumber = columnNumber / 26
 * Letters come out least significant first, so they are written into the
 * buffer from right to left (no reverse step needed).
 *
 * Time Complexity:  O(log26 n)
 * Space Complexity: O(1) besides the result (at most 7 letters for INT_MAX)
 *
 * @param columnNumber: Column number, 1 <= columnNumber <= 2^31 - 1
 * @return: Column title (caller must free this memory)
 */
char* convertToTitle(int columnNumber) {
    char buffer[8];           /* 7 letters max ("FXSHRXW") + '\0' */
    int pos = 7;
    buffer[pos] = '\0';

    while (columnNumber > 0) {
        columnNumber--;
        buffer[--pos] = 'A' + columnNumber % 26;
        columnNumber /= 26;
    }

    char* result = malloc(8 - pos);
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, buffer + pos);
    return result;
}

int main(void) {
    struct {
        int input;
        const char* expected;
    } tests[] = {
        {1, "A"},
        {26, "Z"},
        {27, "AA"},
        {28, "AB"},
        {52, "AZ"},
        {701, "ZY"},
        {702, "ZZ"},
        {703, "AAA"},
        {2147483647, "FXSHRXW"},  /* largest valid input (INT_MAX) */
    };
    int numTests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < numTests; i++) {
        char* result = convertToTitle(tests[i].input);
        int ok = (result != NULL && strcmp(result, tests[i].expected) == 0);
        passed += ok;
        printf("[%s] Input: %d => Output: \"%s\" (expected \"%s\")\n",
               ok ? "PASS" : "FAIL", tests[i].input,
               result ? result : "(null)", tests[i].expected);
        free(result);
    }

    printf("\n%d/%d tests passed\n", passed, numTests);
    return passed == numTests ? 0 : 1;
}
