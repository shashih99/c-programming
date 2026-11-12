#include <stdio.h>
#include <stdlib.h>

/**
 * 121. Best Time to Buy and Sell Stock
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the ith day. You want to maximize your profit by choosing a single day to
 * buy one stock and choosing a different day in the future to sell that stock.
 *
 * Return the maximum profit you can achieve from this transaction. If you
 * cannot achieve any profit, return 0.
 *
 * Algorithm (one pass, track running minimum):
 * 1. Keep the lowest price seen so far (best day to have bought).
 * 2. For each day, the best profit if selling today is prices[i] - minPrice.
 * 3. Keep the maximum of those profits.
 *
 * Time Complexity: O(n) - single pass over the array
 * Space Complexity: O(1) - two variables
 *
 * @param prices: The array of daily stock prices
 * @param pricesSize: Number of days
 * @return: Maximum profit achievable, or 0 if no profit is possible
 */
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int minPrice = prices[0];
    int best = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] < minPrice) {
            // New lowest price: better day to buy
            minPrice = prices[i];
        } else {
            // Profit if we sell today having bought at minPrice
            int profit = prices[i] - minPrice;
            if (profit > best) {
                best = profit;
            }
        }
    }

    return best;
}

/**
 * Helper function to print an array
 */
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]");
}

/**
 * Run one test case and report PASS/FAIL against the expected result
 */
void runTest(const char* name, int* prices, int size, int expected) {
    int result = maxProfit(prices, size);
    printf("%s:\n", name);
    printf("Input: prices = ");
    printArray(prices, size);
    printf("\nOutput: %d (expected %d) %s\n\n", result, expected,
           result == expected ? "PASS" : "FAIL");
}

int main() {
    printf("Best Time to Buy and Sell Stock\n");
    printf("===============================\n\n");

    // Example 1: buy at 1 (day 2), sell at 6 (day 5) -> 5
    int prices1[] = {7, 1, 5, 3, 6, 4};
    runTest("Example 1", prices1, sizeof(prices1) / sizeof(prices1[0]), 5);

    // Example 2: prices only decrease -> 0
    int prices2[] = {7, 6, 4, 3, 1};
    runTest("Example 2", prices2, sizeof(prices2) / sizeof(prices2[0]), 0);

    printf("Additional Test Cases:\n\n");

    // Single day: cannot sell on a different day -> 0
    int prices3[] = {5};
    runTest("Test Case 3 (single day)", prices3, 1, 0);

    // Strictly increasing: buy first, sell last -> 4
    int prices4[] = {1, 2, 3, 4, 5};
    runTest("Test Case 4 (increasing)", prices4, sizeof(prices4) / sizeof(prices4[0]), 4);

    // Minimum comes after an earlier peak -> buy at 1, sell at 4
    int prices5[] = {2, 4, 1, 3, 4};
    runTest("Test Case 5 (later minimum)", prices5, sizeof(prices5) / sizeof(prices5[0]), 3);

    // All equal -> 0
    int prices6[] = {3, 3, 3, 3};
    runTest("Test Case 6 (all equal)", prices6, sizeof(prices6) / sizeof(prices6[0]), 0);

    // Price of zero and maximum price
    int prices7[] = {0, 10000};
    runTest("Test Case 7 (bounds)", prices7, 2, 10000);

    return 0;
}
