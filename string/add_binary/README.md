# Add Binary

## Problem Statement

Given two binary strings `a` and `b`, return their sum as a binary string.

### Examples

**Example 1:**
- Input: `a = "11"`, `b = "1"`
- Output: `"100"`
- Explanation: `11` (3 in decimal) + `1` (1 in decimal) = `100` (4 in decimal)

**Example 2:**
- Input: `a = "1010"`, `b = "1011"`
- Output: `"10101"`
- Explanation: `1010` (10 in decimal) + `1011` (11 in decimal) = `10101` (21 in decimal)

### Constraints

- `1 <= a.length, b.length <= 10^4`
- `a` and `b` consist only of `'0'` or `'1'` characters.
- Each string does not contain leading zeros except for the zero itself.

## Solution Approach

### Right-to-Left Addition with Carry

This solution processes both binary strings from right to left (least significant bit first), similar to how we add numbers manually:

1. **Initialize pointers**: Start from the rightmost (least significant) bit of both strings
2. **Add bits with carry**: 
   - Add corresponding bits from both strings along with any carry from previous addition
   - Calculate the result bit: `sum % 2`
   - Calculate the carry: `sum / 2`
3. **Handle different lengths**: Continue processing until both strings are exhausted
4. **Handle final carry**: If there's a carry after processing all bits, add it to the result
5. **Reverse result**: Since we built the result from right to left, reverse it to get the correct order

### Algorithm Details

```
addBinary(a, b):
    1. Initialize i = lenA - 1, j = lenB - 1, carry = 0
    2. Allocate result array of size max(lenA, lenB) + 2
    3. While i >= 0 OR j >= 0 OR carry > 0:
       a. sum = carry
       b. If i >= 0: sum += a[i], i--
       c. If j >= 0: sum += b[j], j--
       d. result[index++] = (sum % 2) + '0'
       e. carry = sum / 2
    4. Reverse the result array
    5. Return result
```

### Complexity Analysis

- **Time Complexity**: O(max(m, n))
  - We traverse both strings once from right to left
  - The reversal step takes O(max(m, n)) time
  - Overall: O(max(m, n)) where m and n are lengths of strings a and b

- **Space Complexity**: O(max(m, n))
  - We allocate memory for the result string
  - The result can be at most max(m, n) + 1 characters long (if there's a carry)

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

## Test Cases

The program includes the following test cases:

1. **Example 1**: `a = "11"`, `b = "1"` → `"100"`
2. **Example 2**: `a = "1010"`, `b = "1011"` → `"10101"`
3. **Both zeros**: `a = "0"`, `b = "0"` → `"0"`
4. **Single bit addition**: `a = "1"`, `b = "1"` → `"10"`
5. **All ones**: `a = "1111"`, `b = "1111"` → `"11110"`
6. **Different lengths**: `a = "100"`, `b = "110010"` → `"110110"`
7. **Very different lengths**: `a = "1"`, `b = "111"` → `"1000"`

## Key Points

- The function returns a dynamically allocated string that the caller must free
- The algorithm handles strings of different lengths gracefully
- Carry propagation is handled correctly for all cases
- The result is built from right to left and then reversed
- Edge cases like both strings being "0" are handled correctly
- The solution is efficient with O(max(m, n)) time and space complexity

## Example Walkthrough

Let's trace through Example 1: `a = "11"`, `b = "1"`

```
Step 1: i=1 (pointing to '1' in "11"), j=0 (pointing to '1' in "1")
        sum = 0 + 1 + 1 = 2
        result[0] = '0', carry = 1

Step 2: i=0 (pointing to '1' in "11"), j=-1 (done with "1")
        sum = 1 + 1 + 0 = 2
        result[1] = '0', carry = 1

Step 3: i=-1 (done with "11"), j=-1, carry=1
        sum = 1
        result[2] = '1', carry = 0

Result before reverse: "001"
Result after reverse: "100" ✓
```
