#include <stdio.h>

/**
 * Number of 1 Bits (LeetCode 191)
 *
 * Given a positive integer n, return the number of set bits in its binary
 * representation (also known as the Hamming weight).
 *
 * Algorithm (Brian Kernighan's trick):
 * n & (n - 1) clears the lowest set bit of n. Repeat until n becomes 0;
 * the number of iterations equals the number of set bits.
 *
 *     n       = 1011 0100
 *     n - 1   = 1011 0011
 *     n & n-1 = 1011 0000   (lowest 1 removed)
 *
 * The value is treated as unsigned so the trick is well-defined for every
 * bit pattern.
 *
 * Time Complexity:  O(k), where k is the number of set bits (at most 32)
 * Space Complexity: O(1)
 *
 * @param n: Positive integer, 1 <= n <= 2^31 - 1
 * @return: Number of 1 bits in n
 */
int hammingWeight(int n) {
    unsigned int x = (unsigned int)n;
    int count = 0;

    while (x != 0) {
        x &= x - 1;
        count++;
    }
    return count;
}

int main(void) {
    struct {
        int input;
        int expected;
    } tests[] = {
        {1, 1},
        {2, 1},
        {11, 3},          /* 1011 */
        {128, 1},         /* 1000 0000 */
        {255, 8},
        {2147483645, 30}, /* 0111 ... 1101 */
        {2147483647, 31}, /* INT_MAX: 31 ones */
    };
    int numTests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < numTests; i++) {
        int result = hammingWeight(tests[i].input);
        int ok = (result == tests[i].expected);
        passed += ok;
        printf("[%s] Input: %d => Output: %d (expected %d)\n",
               ok ? "PASS" : "FAIL", tests[i].input, result, tests[i].expected);
    }

    printf("\n%d/%d tests passed\n", passed, numTests);
    return passed == numTests ? 0 : 1;
}
