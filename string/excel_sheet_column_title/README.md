# Excel Sheet Column Title

LeetCode 168: https://leetcode.com/problems/excel-sheet-column-title/

## Problem Statement

Given an integer `columnNumber`, return its corresponding column title as it appears in an Excel sheet.

```
1  -> A
2  -> B
...
26 -> Z
27 -> AA
28 -> AB
...
```

### Examples

- Input: `1` → Output: `"A"`
- Input: `28` → Output: `"AB"`
- Input: `701` → Output: `"ZY"`

### Constraints

- `1 <= columnNumber <= 2^31 - 1`

## Solution Approach

### Base-26 Conversion With No Zero Digit

This is the reverse of [Excel Sheet Column Number](../excel_sheet_column_number/). The digits are `A=1 … Z=26`, so there is no zero. A plain `n % 26` would give `0` for `Z`. Subtracting 1 before each step moves the digit into the range `0..25`, which maps directly to `'A'..'Z'`:

```
while n > 0:
    n = n - 1
    letter = 'A' + n % 26
    n = n / 26
```

Letters come out least significant first, so they are written into a buffer from right to left. That avoids a separate reverse step.

### Complexity

- **Time**: O(log₂₆ n)
- **Space**: O(1) extra. The result is at most 7 letters, since `INT_MAX` is `"FXSHRXW"`.

The returned string is allocated with `malloc` and the caller must `free` it.

## Example Walkthrough: `701`

```
n = 701 → n-1 = 700, 700 % 26 = 24 → 'Y', n = 700 / 26 = 26
n = 26  → n-1 = 25,  25 % 26  = 25 → 'Z', n = 25 / 26  = 0
Result (read right to left): "ZY" ✓
```

## Building and Running

```bash
make        # compile
make run    # run test cases
make clean  # remove build artifacts
```
