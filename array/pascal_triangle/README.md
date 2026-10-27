# Pascal's Triangle

## Problem Description

Given an integer `numRows`, return the first `numRows` of Pascal's triangle.

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
Input: numRows = 5
Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
```

### Example 2
```
Input: numRows = 1
Output: [[1]]
```

## Constraints

- `1 <= numRows <= 30`

## Solution Approach

1. Allocate a jagged 2D array: row `i` has length `i + 1`.
2. Set each row's first and last elements to `1`.
3. Fill interior values as `result[i][j] = result[i-1][j-1] + result[i-1][j]`.

### Complexity

- **Time Complexity**: `O(numRows^2)` — each cell is filled once
- **Space Complexity**: `O(numRows^2)` — store the full triangle

## Build and Run

### Build
```bash
make
```

### Run
```bash
make run
# or
./pascal_triangle
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
1. Open `pascal_triangle.c`
2. Select **Debug current program**
3. Press `F5`
