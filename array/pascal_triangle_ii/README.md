# Pascal's Triangle II

## Problem Description

Given an integer `rowIndex`, return the `rowIndex`-th (0-indexed) row of Pascal's triangle.

In Pascal's triangle, each number is the sum of the two numbers directly above it:

```
    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1
```

## Examples

### Example 1
```
Input: rowIndex = 3
Output: [1,3,3,1]
```

### Example 2
```
Input: rowIndex = 0
Output: [1]
```

### Example 3
```
Input: rowIndex = 1
Output: [1,1]
```

## Constraints

- `0 <= rowIndex <= 33`

## Solution Approach

Build a single row in place using O(rowIndex) space:

1. Allocate an array of size `rowIndex + 1`, initialized to zeros; set `row[0] = 1`.
2. For each row `i` from `1` to `rowIndex`, update from right to left:
   - `row[j] += row[j - 1]` for `j = i .. 1`
3. Updating right-to-left reuses previous values without overwriting ones still needed.

### Complexity

- **Time Complexity**: `O(rowIndex^2)`
- **Space Complexity**: `O(rowIndex)` for the returned row

## Build and Run

### Build
```bash
make
```

### Run
```bash
make run
# or
./pascal_triangle_ii
```

### Clean
```bash
make clean
```

### Rebuild
```bash
make rebuild
```

### Debug Build
```bash
make debug
```

### Run Debug Build
```bash
make debug-run
```

### Debug in VS Code / Cursor
1. Open `pascal_triangle_ii.c`
2. Select **Debug current program**
3. Press `F5`
