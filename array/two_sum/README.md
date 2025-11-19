# Two Sum Problem

## Problem Description

Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

**Constraints:**
- You may assume that each input would have exactly one solution
- You may not use the same element twice
- You can return the answer in any order

## Examples

### Example 1:
```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

### Example 2:
```
Input: nums = [3,2,4], target = 6
Output: [1,2]
Explanation: Because nums[1] + nums[2] == 6, we return [1, 2].
```

### Example 3:
```
Input: nums = [3,3], target = 6
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 6, we return [0, 1].
```

## Solution Approaches

### Method 1: Brute Force (Current Implementation)

**Algorithm:**
- Use nested loops to check all pairs of elements
- For each element at index `i`, check all elements at indices `j > i`
- If `nums[i] + nums[j] == target`, return the indices `[i, j]`

**Time Complexity:** O(n²) - where n is the number of elements in the array
- Outer loop runs n times
- Inner loop runs (n-1), (n-2), ..., 1 times
- Total: n(n-1)/2 = O(n²)

**Space Complexity:** O(1) - only storing the result array (excluding input)

**Advantages:**
- Simple and easy to understand
- No additional data structures needed
- Constant space complexity

**Disadvantages:**
- Slow for large arrays (quadratic time)
- Not optimal for production use

### Method 2: Hash Table (Optimized)

**Algorithm:**
- Create a hash table to store numbers and their indices
- Iterate through the array once
- For each number `nums[i]`, calculate `complement = target - nums[i]`
- Check if complement exists in the hash table
- If found, return `[complementIndex, i]`
- Otherwise, store `nums[i]` and its index `i` in the hash table

**Time Complexity:** O(n) - single pass through the array
- Hash table operations (insert, lookup) are O(1) on average

**Space Complexity:** O(n) - hash table storage for up to n elements

**Advantages:**
- Linear time complexity - much faster for large inputs
- Optimal solution for this problem

**Disadvantages:**
- Requires additional memory for hash table
- More complex implementation
- Requires hash table data structure (not built into C)

**Hash Table Implementation (Pseudo-code):**
```c
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Initialize hash table
    HashTable* ht = createHashTable();
    
    *returnSize = 2;
    int* result = malloc(2 * sizeof(int));
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int complementIndex = hashTableGet(ht, complement);
        
        if (complementIndex != -1) {
            result[0] = complementIndex;
            result[1] = i;
            freeHashTable(ht);
            return result;
        }
        
        hashTablePut(ht, nums[i], i);
    }
    
    freeHashTable(ht);
    return result;
}
```

## Questions & Analysis

### 1. Why can't we use the same element twice?
The problem states "you may not use the same element twice." This means if we have `nums = [3, 2, 4]` and `target = 6`, we cannot use `nums[0]` twice (3 + 3 = 6) because it's the same element. We must use two different indices.

### 2. What if there are multiple solutions?
The problem guarantees exactly one solution, so we don't need to handle multiple solutions. However, in a real-world scenario, you might want to return all pairs or the first pair found.

### 3. Can the array contain negative numbers?
Yes, the problem doesn't restrict the values to positive numbers. Both methods handle negative numbers correctly.

### 4. Can the array contain duplicates?
Yes, as shown in Example 3. The hash table method handles this correctly by storing the first occurrence and checking before inserting.

### 5. When should we use Method 1 vs Method 2?
- **Use Method 1 (Brute Force)** when:
  - Array size is small (< 100 elements)
  - Simplicity is more important than performance
  - Memory is extremely constrained
  
- **Use Method 2 (Hash Table)** when:
  - Array size is large (> 1000 elements)
  - Performance is critical
  - Memory is available

### 6. Edge Cases to Consider:
- Array with 2 elements (minimum case)
- Array with duplicate values
- Negative numbers in array and target
- Large array sizes
- Target is sum of first and last elements

## Testing

### Building the Program

```bash
make
```

### Running Tests

```bash
make run
# or
./two_sum
```

### Expected Output

```
Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9

Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]
Explanation: nums[1] + nums[2] = 2 + 4 = 6

Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
Explanation: nums[0] + nums[1] = 3 + 3 = 6
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: Negative numbers
int nums4[] = {-1, -2, -3, -4, -5};
int target4 = -8;
result = twoSum(nums4, 5, target4, &returnSize);
// Expected: [2,4] (nums[2] + nums[4] = -3 + -5 = -8)

// Test case: Large array
int nums5[1000];
for (int i = 0; i < 1000; i++) {
    nums5[i] = i;
}
int target5 = 1998; // 999 + 999
result = twoSum(nums5, 1000, target5, &returnSize);
// Expected: [999,999] or similar
```

### Test Cases Checklist

- [x] Basic case with positive numbers (Example 1)
- [x] Case with non-consecutive indices (Example 2)
- [x] Case with duplicate values (Example 3)
- [ ] Negative numbers in array
- [ ] Negative target value
- [ ] Large array (1000+ elements)
- [ ] Minimum array size (2 elements)
- [ ] Target is sum of first and last elements
- [ ] Memory allocation failure handling

### Performance Testing

To compare performance between methods, you can:

1. **Time the execution:**
```bash
time ./two_sum
```

2. **Test with different array sizes:**
   - Small (10 elements): Both methods are fast
   - Medium (1000 elements): Hash table is noticeably faster
   - Large (100,000 elements): Hash table is significantly faster

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./two_sum
```

### Clean Build Artifacts

```bash
make clean
```

## Function Signature

```c
int* twoSum(int* nums, int numsSize, int target, int* returnSize);
```

**Parameters:**
- `nums`: Pointer to the integer array
- `numsSize`: Size of the array
- `target`: Target sum value
- `returnSize`: Pointer to store the size of returned array (will be set to 2)

**Returns:**
- Pointer to an array of two integers (indices)
- NULL on memory allocation failure
- Caller is responsible for freeing the returned array

## Memory Management

**Important:** The function allocates memory for the result array using `malloc()`. The caller must free this memory:

```c
int* result = twoSum(nums, numsSize, target, &returnSize);
if (result != NULL) {
    // Use result
    free(result);  // Don't forget to free!
}
```

## Additional Resources

- [LeetCode Two Sum Problem](https://leetcode.com/problems/two-sum/)
- Hash table implementation in C
- Time complexity analysis
- Space-time tradeoffs

