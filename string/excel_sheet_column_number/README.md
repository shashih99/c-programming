# Excel Sheet Column Number

LeetCode 171: https://leetcode.com/problems/excel-sheet-column-number/

## Problem Statement

Given a string `columnTitle` that represents the column title as it appears in an Excel sheet, return its corresponding column number.

```
A  -> 1
B  -> 2
...
Z  -> 26
AA -> 27
AB -> 28
...
```

### Examples

- Input: `"A"` → Output: `1`
- Input: `"AB"` → Output: `28`
- Input: `"ZY"` → Output: `701`

### Constraints

- `1 <= columnTitle.length <= 7`
- `columnTitle` consists only of uppercase English letters.
- `columnTitle` is in the range `["A", "FXSHRXW"]`.

## Solution Approach

### Base-26 Conversion

The title is a base-26 number with digits `A=1 … Z=26`. There is no zero digit. Read it left to right like an ordinary number:

```
result = 0
for each char c:
    result = result * 26 + (c - 'A' + 1)
```

### Complexity

- **Time**: O(n)
- **Space**: O(1)

The largest input `"FXSHRXW"` equals `2147483647` (`INT_MAX`), so an `int` never overflows.

## Example Walkthrough: `"ZY"`

```
'Z': result = 0  * 26 + 26 = 26
'Y': result = 26 * 26 + 25 = 701 ✓
```

## Building and Running

```bash
make        # compile
make run    # run test cases
make clean  # remove build artifacts
```
