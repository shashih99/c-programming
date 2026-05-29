# Palindrome Number Problem

## Problem Description

Given an integer `x`, return `true` if `x` is a palindrome, and `false` otherwise.

A palindrome reads the same from left to right and from right to left.

**Constraints:**
- `-2³¹ <= x <= 2³¹ - 1`

## Examples

### Example 1:
```
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.
```

### Example 2:
```
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
```

### Example 3:
```
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
```

## Solution Approach

### Method: Reverse and Compare (Current Implementation)

**Algorithm:**
1. Check if the number is negative - if so, return `false` immediately
2. Check if the number ends with 0 (except 0 itself) - if so, return `false`
3. Reverse the entire number
4. Compare the reversed number with the original number
5. Return `true` if they match, `false` otherwise

**Time Complexity:** O(log₁₀(n)) - where n is the input number
- The number of digits in n is approximately log₁₀(n)
- We iterate through each digit once to reverse the number

**Space Complexity:** O(1) - only using a few variables (original, reversed)

**Advantages:**
- Simple and intuitive approach
- Easy to understand and implement
- Constant space complexity
- Handles all edge cases correctly

**Disadvantages:**
- Reverses the entire number (could optimize to reverse only half)
- Uses `long` type to prevent overflow (requires larger data type)

### Alternative Method: Reverse Half (Optimized)

**Algorithm:**
1. Handle edge cases (negative, ends with 0 except 0)
2. Reverse only the second half of the number
3. Compare the first half with the reversed second half
4. This avoids potential overflow issues and is slightly more efficient

**Time Complexity:** O(log₁₀(n)) - same as current method
**Space Complexity:** O(1) - same as current method

**Advantages:**
- Only processes half the digits
- Avoids overflow issues (no need for `long`)
- Slightly more efficient

**Disadvantages:**
- More complex logic to handle odd/even digit counts
- Requires careful handling of edge cases

**Optimized Implementation (Pseudo-code):**
```c
bool isPalindrome(int x) {
    if (x < 0 || (x != 0 && x % 10 == 0)) {
        return false;
    }
    
    int reversed = 0;
    while (x > reversed) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }
    
    // For even digits: x == reversed
    // For odd digits: x == reversed / 10 (middle digit doesn't matter)
    return x == reversed || x == reversed / 10;
}
```

## Questions & Analysis

### 1. Why are negative numbers not palindromes?
When a negative number is reversed, the negative sign doesn't move. For example, -121 reversed becomes 121-, which is not the same as -121. Therefore, negative numbers cannot be palindromes.

### 2. Why are numbers ending in 0 (except 0) not palindromes?
A number ending in 0, when reversed, would start with 0 (e.g., 10 becomes 01). However, in standard integer representation, leading zeros are not allowed, so 01 is just 1, which is different from 10. The only exception is 0 itself, which is a palindrome.

### 3. Can we convert to string?
Yes, converting to string and comparing is another approach, but it requires:
- Additional memory for the string
- String manipulation functions
- More overhead

The integer reversal approach is more efficient and doesn't require string operations.

### 4. How do we handle overflow?
In the current implementation, we use `long` type for the reversed number to prevent overflow. For example, if we're reversing a large number like 2147483647 (INT_MAX), the reversed number would be 7463847412, which exceeds `int` range but fits in `long`.

### 5. Edge Cases to Consider:
- [x] Negative numbers (e.g., -121)
- [x] Zero (0)
- [x] Single digit numbers (e.g., 1, 5, 9)
- [x] Numbers ending in 0 (e.g., 10, 20, 100)
- [x] Even-digit palindromes (e.g., 1221)
- [x] Odd-digit palindromes (e.g., 12321)
- [x] Large numbers (e.g., INT_MAX)
- [x] Non-palindrome numbers (e.g., 123)

## Testing

### Building the Program

```bash
make
```

### Running Tests

```bash
make run
# or
./palindrome
```

### Expected Output

```
Example 1:
Input: x = 121
Output: true
Explanation: 121 reads as 121 from left to right and from right to left.

Example 2:
Input: x = -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:
Input: x = 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Additional test cases:
x = 0: true
x = 1: true
x = 1221: true
x = 12321: true
x = 123: false
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: Large palindrome
int x4 = 1234321;
bool result4 = isPalindrome(x4);
// Expected: true

// Test case: Large non-palindrome
int x5 = 1234567;
bool result5 = isPalindrome(x5);
// Expected: false

// Test case: INT_MAX
int x6 = 2147483647;
bool result6 = isPalindrome(x6);
// Expected: false

// Test case: Negative palindrome-looking number
int x7 = -12321;
bool result7 = isPalindrome(x7);
// Expected: false
```

### Test Cases Checklist

- [x] Basic palindrome (Example 1: 121)
- [x] Negative number (Example 2: -121)
- [x] Number ending in 0 (Example 3: 10)
- [x] Zero (0)
- [x] Single digit numbers (1, 5, 9)
- [x] Even-digit palindromes (1221, 1001)
- [x] Odd-digit palindromes (12321, 1234321)
- [x] Non-palindrome numbers (123, 1234)
- [ ] Large numbers (INT_MAX, INT_MIN)
- [ ] Numbers with many digits

### Performance Testing

To test performance:

1. **Time the execution:**
```bash
time ./palindrome
```

2. **Test with different number sizes:**
   - Small (1-3 digits): Very fast
   - Medium (4-6 digits): Fast
   - Large (7-10 digits): Still fast (logarithmic complexity)

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./palindrome
```

### Clean Build Artifacts

```bash
make clean
```

## Function Signature

```c
bool isPalindrome(int x);
```

**Parameters:**
- `x`: Integer to check for palindrome property

**Returns:**
- `true` if `x` is a palindrome
- `false` otherwise

## Algorithm Details

### Step-by-Step Example: Checking 121

1. **Input:** x = 121
2. **Check negative:** 121 >= 0 ✓
3. **Check ends with 0:** 121 % 10 = 1 ≠ 0 ✓
4. **Reverse:**
   - original = 121
   - reversed = 0
   - Iteration 1: reversed = 0 * 10 + 1 = 1, x = 12
   - Iteration 2: reversed = 1 * 10 + 2 = 12, x = 1
   - Iteration 3: reversed = 12 * 10 + 1 = 121, x = 0
5. **Compare:** original (121) == reversed (121) ✓
6. **Return:** true

### Step-by-Step Example: Checking -121

1. **Input:** x = -121
2. **Check negative:** -121 < 0 → return false immediately

### Step-by-Step Example: Checking 10

1. **Input:** x = 10
2. **Check negative:** 10 >= 0 ✓
3. **Check ends with 0:** 10 != 0 && 10 % 10 == 0 → return false immediately

## Additional Resources

- [LeetCode Palindrome Number Problem](https://leetcode.com/problems/palindrome-number/)
- Integer reversal techniques
- Time complexity analysis
- Overflow handling in C

