# Search Insert Position Problem

## Problem Description

Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with **O(log n)** runtime complexity.

**Constraints:**
- `1 <= nums.length <= 104`
- `-104 <= nums[i] <= 104`
- `nums` contains distinct values sorted in ascending order
- `-104 <= target <= 104`

## Examples

### Example 1:
```
Input: nums = [1,3,5,6], target = 5
Output: 2
Explanation: 5 is found at index 2.
```

### Example 2:
```
Input: nums = [1,3,5,6], target = 2
Output: 1
Explanation: 2 is not found. If it were inserted, it would be at index 1.
```

### Example 3:
```
Input: nums = [1,3,5,6], target = 7
Output: 4
Explanation: 7 is not found. If it were inserted, it would be at index 4.
```

## Solution Approach

### Method: Binary Search

**Algorithm:**
1. Use binary search to find the target or determine the insertion position
2. Initialize `left = 0` and `right = numsSize - 1`
3. While `left <= right`:
   - Calculate `mid = left + (right - left) / 2`
   - If `nums[mid] == target`, return `mid` (target found)
   - If `nums[mid] < target`, search in the right half: `left = mid + 1`
   - If `nums[mid] > target`, search in the left half: `right = mid - 1`
4. If target is not found, `left` will point to the insertion position
5. Return `left`

**Time Complexity:** O(log n) - where n is the length of the array
- Each iteration eliminates half of the search space
- Maximum number of iterations is log₂(n)

**Space Complexity:** O(1) - only using a few variables
- No additional data structures required
- Constant space regardless of input size

**Key Insight:**
When the binary search loop ends (`left > right`), the `left` pointer will always point to the correct insertion position. This is because:
- If target is smaller than all elements, `left` remains at 0
- If target is larger than all elements, `left` ends at `numsSize`
- If target is between elements, `left` points to the position where it should be inserted

**Advantages:**
- Optimal time complexity O(log n)
- Simple and elegant implementation
- Handles both search and insertion position in one algorithm
- Constant space complexity

**Disadvantages:**
- Requires the array to be sorted (which is given in the problem)

## Questions & Analysis

### 1. Why does binary search work for this problem?
Binary search works because the array is sorted. We can eliminate half of the search space in each iteration, making it O(log n). When the target is not found, the `left` pointer naturally points to the insertion position.

### 2. Why does `left` point to the insertion position?
When the binary search loop ends:
- If `nums[mid] < target`, we set `left = mid + 1`, meaning the target should be to the right of `mid`
- If `nums[mid] > target`, we set `right = mid - 1`, but `left` stays at the position where target should be
- When `left > right`, `left` is at the first position where `nums[left] >= target` (or `numsSize` if target is larger than all elements)

### 3. What if the target is found?
If the target is found at index `mid`, we immediately return `mid`. This is the correct index.

### 4. What if the target is smaller than all elements?
If target is smaller than `nums[0]`, `left` will remain at 0, which is the correct insertion position.

### 5. What if the target is larger than all elements?
If target is larger than `nums[numsSize-1]`, `left` will end at `numsSize`, which is the correct insertion position (after the last element).

### 6. Edge Cases to Consider:
- [x] Target found at first position
- [x] Target found at last position
- [x] Target found in middle
- [x] Target not found, should be inserted at beginning
- [x] Target not found, should be inserted at end
- [x] Target not found, should be inserted in middle
- [x] Single element array, target found
- [x] Single element array, target not found (smaller)
- [x] Single element array, target not found (larger)

## Testing

### Building the Program

```bash
make
```

### Running Tests

```bash
make run
# or
./search_insert_position
```

### Expected Output

```
Example 1:
Input: nums = [1,3,5,6], target = 5
Output: 2
Explanation: 5 is found at index 2.

Example 2:
Input: nums = [1,3,5,6], target = 2
Output: 1
Explanation: 2 is not found. If it were inserted, it would be at index 1.

Example 3:
Input: nums = [1,3,5,6], target = 7
Output: 4
Explanation: 7 is not found. If it were inserted, it would be at index 4.

Additional Test Cases:
...
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: Empty array (edge case)
int nums[] = {};
int result = searchInsert(nums, 0, 5);
// Expected: 0

// Test case: Target between two elements
int nums[] = {1, 3, 5, 7};
int result = searchInsert(nums, 4, 4);
// Expected: 2

// Test case: Duplicate values (though problem states distinct)
int nums[] = {1, 2, 3, 4, 5};
int result = searchInsert(nums, 5, 3);
// Expected: 2
```

### Test Cases Checklist

- [x] Target found at index 2 (Example 1)
- [x] Target not found, insert at index 1 (Example 2)
- [x] Target not found, insert at index 4 (Example 3)
- [x] Target smaller than all elements
- [x] Target larger than all elements
- [x] Target at first position (found)
- [x] Target at last position (found)
- [x] Single element array, target found
- [x] Single element array, target not found (smaller)
- [x] Single element array, target not found (larger)
- [x] Target in middle (not found)

### Performance Testing

To test performance:

1. **Time the execution:**
```bash
time ./search_insert_position
```

2. **Test with different array sizes:**
   - Small (10 elements): Very fast (log₂(10) ≈ 3-4 iterations)
   - Medium (100 elements): Fast (log₂(100) ≈ 6-7 iterations)
   - Large (10,000 elements): Still fast (log₂(10,000) ≈ 13-14 iterations)

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./search_insert_position
```

### Clean Build Artifacts

```bash
make clean
```

## Function Signature

```c
int searchInsert(int* nums, int numsSize, int target);
```

**Parameters:**
- `nums`: Pointer to the sorted array of distinct integers
- `numsSize`: Size of the array
- `target`: Target value to search for or insert

**Returns:**
- `int`: Index where target is found, or index where it should be inserted

**Note:** The function does not modify the array. It only returns the index.

## Implementation Details

### Step-by-Step Example: Searching for 2 in [1,3,5,6]

1. **Input:** nums = [1,3,5,6], target = 2
2. **Initialize:** left = 0, right = 3
3. **Iteration 1:**
   - mid = 0 + (3-0)/2 = 1
   - nums[1] = 3 > target (2)
   - Search left: right = 1 - 1 = 0
4. **Iteration 2:**
   - mid = 0 + (0-0)/2 = 0
   - nums[0] = 1 < target (2)
   - Search right: left = 0 + 1 = 1
5. **Loop ends:** left = 1, right = 0 (left > right)
6. **Return:** 1 (insertion position)

### Step-by-Step Example: Searching for 5 in [1,3,5,6]

1. **Input:** nums = [1,3,5,6], target = 5
2. **Initialize:** left = 0, right = 3
3. **Iteration 1:**
   - mid = 0 + (3-0)/2 = 1
   - nums[1] = 3 < target (5)
   - Search right: left = 1 + 1 = 2
4. **Iteration 2:**
   - mid = 2 + (3-2)/2 = 2
   - nums[2] = 5 == target (5)
   - **Return:** 2 (target found)

### Step-by-Step Example: Searching for 7 in [1,3,5,6]

1. **Input:** nums = [1,3,5,6], target = 7
2. **Initialize:** left = 0, right = 3
3. **Iteration 1:**
   - mid = 0 + (3-0)/2 = 1
   - nums[1] = 3 < target (7)
   - Search right: left = 1 + 1 = 2
4. **Iteration 2:**
   - mid = 2 + (3-2)/2 = 2
   - nums[2] = 5 < target (7)
   - Search right: left = 2 + 1 = 3
5. **Iteration 3:**
   - mid = 3 + (3-3)/2 = 3
   - nums[3] = 6 < target (7)
   - Search right: left = 3 + 1 = 4
6. **Loop ends:** left = 4, right = 3 (left > right)
7. **Return:** 4 (insertion position)

## Visual Representation

### Example: Searching for 2 in [1,3,5,6]

```
Initial: [1, 3, 5, 6], target = 2
         ↑           ↑
        left       right

Step 1:  [1, 3, 5, 6]  (mid=1, nums[1]=3 > 2, go left)
         ↑  ↑        ↑
      left mid    right

Step 2:  [1, 3, 5, 6]  (mid=0, nums[0]=1 < 2, go right)
         ↑  ↑
      left/mid right

Step 3:  [1, 3, 5, 6]  (left > right, return left = 1)
            ↑  ↑
         right left

Result: Insert at index 1
```

### Example: Searching for 5 in [1,3,5,6]

```
Initial: [1, 3, 5, 6], target = 5
         ↑           ↑
        left       right

Step 1:  [1, 3, 5, 6]  (mid=1, nums[1]=3 < 5, go right)
         ↑  ↑        ↑
      left mid    right

Step 2:  [1, 3, 5, 6]  (mid=2, nums[2]=5 == 5, found!)
               ↑
              mid

Result: Found at index 2
```

## Additional Resources

- [LeetCode Search Insert Position Problem](https://leetcode.com/problems/search-insert-position/)
- Binary search algorithm
- Time complexity analysis
- Array manipulation techniques

