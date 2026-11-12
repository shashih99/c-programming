# Best Time to Buy and Sell Stock

## Problem Description

You are given an array `prices` where `prices[i]` is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return `0`.

## Examples

### Example 1
```
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
```

### Example 2
```
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
```

## Constraints

- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^4`

## Solution Approach

### Algorithm

The solution uses a **single pass while tracking the running minimum**:

1. **Track the cheapest buy so far**: `minPrice` holds the lowest price seen up to the current day.
2. **Check selling today**: If we sell on day `i`, the best profit is `prices[i] - minPrice`.
3. **Keep the best**: Update `best` whenever today's profit beats it.
4. **Update the minimum**: If today's price is lower than `minPrice`, it becomes the new buy candidate.

Because `minPrice` only ever comes from earlier days, the "buy before sell" rule is satisfied automatically.

### Implementation Details

```c
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int minPrice = prices[0];
    int best = 0;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else {
            int profit = prices[i] - minPrice;
            if (profit > best) {
                best = profit;
            }
        }
    }

    return best;
}
```

### Walkthrough (Example 1)

| Day | Price | minPrice | Profit if sold today | best |
|-----|-------|----------|----------------------|------|
| 1   | 7     | 7        | -                    | 0    |
| 2   | 1     | 1        | -                    | 0    |
| 3   | 5     | 1        | 4                    | 4    |
| 4   | 3     | 1        | 2                    | 4    |
| 5   | 6     | 1        | 5                    | 5    |
| 6   | 4     | 1        | 3                    | 5    |

### Complexity Analysis

- **Time Complexity**: O(n) — each price is visited once
- **Space Complexity**: O(1) — only two integer variables

## Alternative Approaches

### Brute Force
- Try every pair `(i, j)` with `i < j` and take the max of `prices[j] - prices[i]`
- **Time**: O(n²) — too slow for `n = 10^5`

### Kadane's Algorithm on Daily Differences
- Build `diff[i] = prices[i] - prices[i-1]` and find the maximum subarray sum (floored at 0)
- Same O(n)/O(1) complexity, but less direct than tracking the minimum

**The running-minimum approach is optimal and the simplest to reason about.**

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./buy_and_sell_stock
```

### Debug build
```bash
make debug
make debug-run
```

### Clean build artifacts
```bash
make clean
```

### Rebuild everything
```bash
make rebuild
```

## Test Cases

The program checks each result against the expected value and prints PASS/FAIL:

1. **Example 1**: `[7,1,5,3,6,4]` → `5`
2. **Example 2**: `[7,6,4,3,1]` → `0`
3. **Single day**: `[5]` → `0`
4. **Strictly increasing**: `[1,2,3,4,5]` → `4`
5. **Minimum after a peak**: `[2,4,1,3,4]` → `3`
6. **All equal**: `[3,3,3,3]` → `0`
7. **Bounds**: `[0,10000]` → `10000`

## Notes

- Profit never goes negative because `best` starts at 0
- Max profit is at most 10^4, so `int` cannot overflow
