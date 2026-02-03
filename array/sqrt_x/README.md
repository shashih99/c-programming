# Sqrt(x)

## Problem Statement

Given a non-negative integer `x`, return the square root of `x` rounded down to the nearest integer. The returned integer should be non-negative as well.

You must not use any built-in exponent function or operator.

For example, do not use `pow(x, 0.5)` in c++ or `x ** 0.5` in python.

### Examples

**Example 1:**
- Input: `x = 4`
- Output: `2`
- Explanation: The square root of 4 is 2, so we return 2.

**Example 2:**
- Input: `x = 8`
- Output: `2`
- Explanation: The square root of 8 is 2.82842..., and since we round it down to the nearest integer, 2 is returned.

### Constraints

- `0 <= x <= 2^31 - 1`

## Solution Approach

### Method: Binary Search

Since we cannot use built-in exponent functions, we use binary search to find the square root. The key insight is that the square root of `x` must be in the range `[0, x]` (or more efficiently `[0, x/2]` for `x >= 2`).

**Algorithm:**
1. Handle edge cases: if `x < 2`, return `x` (since sqrt(0) = 0 and sqrt(1) = 1)
2. Initialize search range: `left = 1`, `right = x / 2`
3. Use binary search:
   - Calculate `mid = left + (right - left) / 2`
   - Calculate `square = mid * mid` (use `long long` to avoid integer overflow)
   - If `square == x`, return `mid` (perfect square found)
   - If `square < x`, update `answer = mid` and search right: `left = mid + 1`
   - If `square > x`, search left: `right = mid - 1`
4. Return the last valid `answer` (the largest integer whose square is <= x)

**Time Complexity:** O(log x)
- Binary search reduces the search space by half in each iteration
- Maximum number of iterations is log₂(x)

**Space Complexity:** O(1)
- Only using a few variables
- Constant space regardless of input size

**Key Insights:**
- We search for the largest integer `mid` such that `mid * mid <= x`
- Using `long long` for the square calculation prevents integer overflow when `mid` is large
- For `x >= 2`, the square root is at most `x / 2`, so we can optimize the search range
- We track the `answer` variable to remember the last valid square root candidate

## Building and Running

### Compile
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
```

### Debug Build
```bash
make debug
```

This creates a debug build with:
- Debugging symbols (`-g`)
- No optimization (`-O0`) for easier debugging
- Debug flag (`-DDEBUG`) if needed

### Run Debug Build
```bash
make debug-run
```

### Debug with GDB
```bash
make debug
gdb build/Debug/sqrt_x
```

In GDB, you can:
- Set breakpoints: `break mySqrt` or `break sqrt_x.c:30`
- Run: `run`
- Step through: `next` or `step`
- Print variables: `print mid` or `print square`
- Continue: `continue`
- Quit: `quit`

## Test Cases

The program includes the following test cases:

1. **Example 1**: `x = 4` → `2`
2. **Example 2**: `x = 8` → `2`
3. **Edge case**: `x = 0` → `0`
4. **Edge case**: `x = 1` → `1`
5. **Perfect square**: `x = 16` → `4`
6. **Non-square**: `x = 27` → `5` (since 5² = 25 < 27 < 36 = 6²)
7. **Large value**: `x = 2147395599` → `46339`

## Key Points

- The function uses binary search to avoid using built-in exponent functions
- Integer overflow is prevented by using `long long` for square calculations
- The algorithm efficiently handles both perfect squares and non-squares
- Edge cases (0 and 1) are handled explicitly
- The solution is optimal with O(log x) time complexity

## Example Walkthrough

Let's trace through Example 2: `x = 8`

```
Step 1: left = 1, right = 4
        mid = 1 + (4-1)/2 = 2
        square = 2 * 2 = 4 < 8
        answer = 2, left = 3

Step 2: left = 3, right = 4
        mid = 3 + (4-3)/2 = 3
        square = 3 * 3 = 9 > 8
        right = 2

Step 3: left = 3, right = 2 (left > right, exit loop)
        Return answer = 2 ✓
```

Let's trace through Example 1: `x = 4`

```
Step 1: left = 1, right = 2
        mid = 1 + (2-1)/2 = 1
        square = 1 * 1 = 1 < 4
        answer = 1, left = 2

Step 2: left = 2, right = 2
        mid = 2 + (2-2)/2 = 2
        square = 2 * 2 = 4 == 4
        Return mid = 2 ✓
```

## Implementation Details

### Overflow Prevention

When calculating `mid * mid`, we use `long long` to prevent integer overflow:

```c
long long square = (long long)mid * mid;
```

This is crucial because for large values of `x` (up to 2³¹ - 1), `mid` can be large enough that `mid * mid` exceeds the range of `int`.

### Search Range Optimization

For `x >= 2`, we know that the square root is at most `x / 2`:
- For `x = 4`, sqrt(4) = 2 = 4/2
- For `x = 9`, sqrt(9) = 3 < 9/2 = 4.5
- For `x = 16`, sqrt(16) = 4 = 16/2

This optimization reduces the search space and improves efficiency.

### Tracking the Answer

We maintain an `answer` variable to track the largest integer whose square is less than or equal to `x`. This is necessary because when we find that `mid * mid < x`, we know `mid` is a valid candidate, but there might be a larger valid candidate to the right.

## Function Signature

```c
int mySqrt(int x);
```

**Parameters:**
- `x`: Non-negative integer (0 <= x <= 2³¹ - 1)

**Returns:**
- `int`: The floor of the square root of `x`

## Additional Resources

- [LeetCode Sqrt(x) Problem](https://leetcode.com/problems/sqrtx/)
- Binary search algorithm
- Integer overflow prevention
- Time complexity analysis
