# Plus One

## Problem Description

You are given a large integer represented as an integer array `digits`, where each `digits[i]` is the ith digit of the integer. The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

Increment the large integer by one and return the resulting array of digits.

## Examples

### Example 1
```
Input: digits = [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Incrementing by one gives 123 + 1 = 124.
Thus, the result should be [1,2,4].
```

### Example 2
```
Input: digits = [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
Incrementing by one gives 4321 + 1 = 4322.
Thus, the result should be [4,3,2,2].
```

### Example 3
```
Input: digits = [9]
Output: [1,0]
Explanation: The array represents the integer 9.
Incrementing by one gives 9 + 1 = 10.
Thus, the result should be [1,0].
```

## Constraints

- `1 <= digits.length <= 100`
- `0 <= digits[i] <= 9`
- `digits` does not contain any leading 0's.

## Solution Approach

### Algorithm

The solution uses a **right-to-left traversal with carry propagation**:

1. **Start from the rightmost digit**: Begin at the least significant digit (last element)
2. **Add 1**: Increment the rightmost digit by 1
3. **Handle carry**: If a digit becomes 10:
   - Set it to 0
   - Carry over 1 to the next digit (left)
   - Continue until no carry remains
4. **Handle overflow**: If the leftmost digit becomes 10 (all digits were 9):
   - Create a new array with size + 1
   - Set the first digit to 1 and all others to 0

### Implementation Details

```c
int* plusOne(int* digits, int digitsSize, int* returnSize) {
    // Start from the rightmost digit
    int i = digitsSize - 1;
    
    // Add 1 to the rightmost digit
    digits[i] += 1;
    
    // Handle carry propagation
    while (i > 0 && digits[i] == 10) {
        digits[i] = 0;
        digits[i - 1] += 1;
        i--;
    }
    
    // Check if we need a new array (all digits were 9)
    if (digits[0] == 10) {
        // All digits were 9, need a new array with size + 1
        int* result = (int*)malloc((digitsSize + 1) * sizeof(int));
        result[0] = 1;
        for (int j = 1; j <= digitsSize; j++) {
            result[j] = 0;
        }
        *returnSize = digitsSize + 1;
        return result;
    }
    
    // No new array needed, return the modified input array
    *returnSize = digitsSize;
    return digits;
}
```

### Complexity Analysis

- **Time Complexity**: O(n) where n is the number of digits
  - In the worst case, we traverse the entire array once
  - Best case: O(1) if the rightmost digit is not 9
  - Average case: O(k) where k is the number of trailing 9's

- **Space Complexity**: 
  - O(1) for in-place modification when no overflow occurs
  - O(n) when all digits are 9 and a new array is needed

### Why This Approach?

1. **Efficient**: We only process digits that need to be changed (from right to left)
2. **Handles edge cases**: 
   - Single digit arrays
   - Arrays with all 9's (overflow case)
   - Arrays with trailing 9's
3. **Simple logic**: The carry propagation is straightforward and easy to understand
4. **Optimal**: This is the most efficient approach for this problem

## Alternative Approaches

### Approach 2: Convert to Integer, Add, Convert Back
- Convert array to integer, add 1, convert back
- **Problem**: Integer overflow for large numbers (constraint allows up to 100 digits)
- **Not feasible** for this problem

### Approach 3: Recursive Approach
- Recursively handle carry from right to left
- More complex and uses additional stack space
- **Not recommended** for this problem

**The right-to-left traversal with carry propagation is optimal for this problem.**

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./plus_one
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

The program includes the following test cases:

1. **Example 1**: `[1,2,3]` → `[1,2,4]`
2. **Example 2**: `[4,3,2,1]` → `[4,3,2,2]`
3. **Example 3**: `[9]` → `[1,0]`
4. **All 9's**: `[9,9,9]` → `[1,0,0,0]`
5. **Trailing 9's**: `[1,9,9]` → `[2,0,0]`
6. **Single 0**: `[0]` → `[1]`

## Notes

- The solution handles all edge cases mentioned in the constraints
- The algorithm is optimal in terms of both time and space complexity
- Memory is only allocated when necessary (overflow case)
- The solution modifies the input array in-place when possible

