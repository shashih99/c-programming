# Remove Element Problem

## Problem Description

Given an integer array `nums` and an integer `val`, remove all occurrences of `val` in `nums` in-place. The order of the elements may be changed. Then return the number of elements in `nums` which are not equal to `val`.

Consider the number of elements in `nums` which are not equal to `val` be `k`, to get accepted, you need to do the following things:

1. Change the array `nums` such that the first `k` elements of `nums` contain the elements which are not equal to `val`. The remaining elements of `nums` are not important as well as the size of `nums`.
2. Return `k`.

**Custom Judge:**

The judge will test your solution with the following code:

```c
int[] nums = [...]; // Input array
int val = ...; // Value to remove
int[] expectedNums = [...]; // The expected answer with correct length.
                            // It is sorted with no values equaling val.

int k = removeElement(nums, val); // Calls your implementation

assert k == expectedNums.length;
sort(nums, 0, k); // Sort the first k elements of nums
for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
}
```

If all assertions pass, then your solution will be accepted.

**Constraints:**
- `0 <= nums.length <= 100`
- `0 <= nums[i] <= 50`
- `0 <= val <= 100`

## Examples

### Example 1:
```
Input: nums = [3,2,2,3], val = 3
Output: 2, nums = [2,2,_,_]
Explanation: Your function should return k = 2, with the first two elements of nums being 2.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

### Example 2:
```
Input: nums = [0,1,2,2,3,0,4,2], val = 2
Output: 5, nums = [0,1,4,0,3,_,_,_]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
Note that the five elements can be returned in any order.
It does not matter what you leave beyond the returned k (hence they are underscores).
```

## Solution Approach

### Method: Two-Pointer Technique (Current Implementation)

**Algorithm:**
1. Use two pointers: `write` for the position to write valid elements, and `read` to scan through the array
2. Iterate through the array with the `read` pointer
3. For each element, check if it's not equal to `val`
4. If it's valid (not equal to `val`), write it to the current `write` position and increment `write`
5. If it equals `val`, skip it (don't increment `write`)
6. Return `write` as the count of valid elements (`k`)

**Time Complexity:** O(n) - where n is the length of the array
- We iterate through each element exactly once
- Each element is processed in constant time

**Space Complexity:** O(1) - only using a few pointers, modifying array in-place
- No additional data structures required
- Constant space regardless of input size

**Advantages:**
- Simple and intuitive approach
- Easy to understand and implement
- Constant space complexity
- Single pass through the array
- In-place modification (no extra memory needed)

**Disadvantages:**
- Modifies the original array (but this is required by the problem)

### Alternative Method: Two-Pointer from Both Ends (Alternative)

**Algorithm:**
1. Use two pointers: `left` starting from the beginning, `right` from the end
2. While `left <= right`:
   - If `nums[left] == val`, swap with `nums[right]` and decrement `right`
   - Otherwise, increment `left`
3. Return `left` as the count

**Time Complexity:** O(n) - same as current method
**Space Complexity:** O(1) - same as current method

**Advantages:**
- Potentially fewer writes (swaps elements to the end)
- Can be more efficient when val appears frequently

**Disadvantages:**
- More complex logic
- Doesn't preserve relative order of non-val elements
- Requires swapping operations

**Note:** The current implementation is preferred because it's simpler and preserves the relative order of valid elements (though order preservation is not required by the problem).

## Questions & Analysis

### 1. Why do we use two pointers?
We use two pointers to efficiently separate valid elements (not equal to `val`) from invalid ones. The `read` pointer scans through the array, while the `write` pointer tracks where to place the next valid element. This allows us to do the operation in a single pass with O(1) extra space.

### 2. What happens to the elements after index k?
The problem states that "the remaining elements of nums are not important as well as the size of nums." This means we don't need to clear or modify elements beyond index `k`. They can contain any values, including the original values or the removed `val`.

### 3. Does the order of elements matter?
No, the problem explicitly states "The order of the elements may be changed." This means we can rearrange the valid elements in any order. However, our implementation preserves the relative order of valid elements, which is a nice property.

### 4. What if all elements equal val?
If all elements equal `val`, then `k = 0`. The function will return 0, and the first 0 elements (i.e., no elements) will be valid. This is correct.

### 5. What if no elements equal val?
If no elements equal `val`, then `k = numsSize`. All elements remain in their original positions, and the function returns the original array size.

### 6. Edge Cases to Consider:
- [x] Empty array (numsSize = 0)
- [x] Single element matching val
- [x] Single element not matching val
- [x] All elements match val
- [x] No elements match val
- [x] Val at beginning
- [x] Val at end
- [x] Val in middle
- [x] Val appears multiple times consecutively
- [x] Val appears multiple times non-consecutively

## Testing

### Building the Program

```bash
make
```

### Running Tests

```bash
make run
# or
./remove_element
```

### Expected Output

```
Example 1:
Input: nums = [3,2,2,3], val = 3
Output: k = 2, nums = [2,2]
Explanation: Your function should return k = 2, with the first two elements of nums being 2.
It does not matter what you leave beyond the returned k (hence they are underscores).

Example 2:
Input: nums = [0,1,2,2,3,0,4,2], val = 2
Output: k = 5, nums = [0,1,3,0,4]
Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
Note that the five elements can be returned in any order.
It does not matter what you leave beyond the returned k (hence they are underscores).

Additional Test Cases:
...
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: All zeros
int nums[] = {0, 0, 0, 0};
int k = removeElement(nums, 4, 0);
// Expected: k = 0

// Test case: Mixed with val at boundaries
int nums[] = {1, 2, 3, 4, 5};
int k = removeElement(nums, 5, 1);
// Expected: k = 4, nums = [2,3,4,5,...]

// Test case: Maximum constraints
int nums[100];
// Fill with test data
int k = removeElement(nums, 100, 50);
```

### Test Cases Checklist

- [x] Basic case with val at beginning and end (Example 1)
- [x] Multiple occurrences of val (Example 2)
- [x] Single element matching val
- [x] Single element not matching val
- [x] All elements match val
- [x] No elements match val
- [x] Empty array
- [x] Val at beginning only
- [x] Val at end only
- [x] Val in middle only
- [x] Consecutive occurrences of val
- [x] Non-consecutive occurrences of val

### Performance Testing

To test performance:

1. **Time the execution:**
```bash
time ./remove_element
```

2. **Test with different array sizes:**
   - Small (10 elements): Very fast
   - Medium (50 elements): Fast
   - Large (100 elements): Still fast (O(n) algorithm)

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./remove_element
```

### Clean Build Artifacts

```bash
make clean
```

## Function Signature

```c
int removeElement(int* nums, int numsSize, int val);
```

**Parameters:**
- `nums`: Pointer to the input array (will be modified in-place)
- `numsSize`: Size of the array
- `val`: Value to remove from the array

**Returns:**
- `k`: Number of elements in `nums` which are not equal to `val`

**Note:** The function modifies the array in-place. The first `k` elements will contain all elements not equal to `val`. The order of these elements is preserved from the original array.

## Implementation Details

### Step-by-Step Example: Removing 3 from [3,2,2,3]

1. **Input:** nums = [3,2,2,3], val = 3
2. **Initialize:** write = 0, read = 0
3. **Iteration 1:** read=0, nums[0]=3
   - nums[0] == val (3), skip
   - write = 0 (unchanged)
4. **Iteration 2:** read=1, nums[1]=2
   - nums[1] != val, write nums[1] to nums[0]
   - nums = [2,2,2,3], write = 1
5. **Iteration 3:** read=2, nums[2]=2
   - nums[2] != val, write nums[2] to nums[1]
   - nums = [2,2,2,3], write = 2
6. **Iteration 4:** read=3, nums[3]=3
   - nums[3] == val (3), skip
   - write = 2 (unchanged)
7. **Return:** k = 2, nums = [2,2,2,3] (first 2 elements are valid)

### Step-by-Step Example: Removing 2 from [0,1,2,2,3,0,4,2]

1. **Input:** nums = [0,1,2,2,3,0,4,2], val = 2
2. **Initialize:** write = 0, read = 0
3. **Iteration 1:** read=0, nums[0]=0
   - nums[0] != val, write to nums[0]
   - nums = [0,1,2,2,3,0,4,2], write = 1
4. **Iteration 2:** read=1, nums[1]=1
   - nums[1] != val, write to nums[1]
   - nums = [0,1,2,2,3,0,4,2], write = 2
5. **Iteration 3:** read=2, nums[2]=2
   - nums[2] == val, skip
   - write = 2 (unchanged)
6. **Iteration 4:** read=3, nums[3]=2
   - nums[3] == val, skip
   - write = 2 (unchanged)
7. **Iteration 5:** read=4, nums[4]=3
   - nums[4] != val, write to nums[2]
   - nums = [0,1,3,2,3,0,4,2], write = 3
8. **Iteration 6:** read=5, nums[5]=0
   - nums[5] != val, write to nums[3]
   - nums = [0,1,3,0,3,0,4,2], write = 4
9. **Iteration 7:** read=6, nums[6]=4
   - nums[6] != val, write to nums[4]
   - nums = [0,1,3,0,4,0,4,2], write = 5
10. **Iteration 8:** read=7, nums[7]=2
    - nums[7] == val, skip
    - write = 5 (unchanged)
11. **Return:** k = 5, nums = [0,1,3,0,4,0,4,2] (first 5 elements are valid)

## Visual Representation

### Example: Removing 3 from [3,2,2,3]

```
Initial: [3, 2, 2, 3], val = 3
         ↑
      read/write

Step 1:  [3, 2, 2, 3]  (3 == val, skip)
         ↑  ↑
      write read

Step 2:  [2, 2, 2, 3]  (2 != val, write)
            ↑  ↑
         write read

Step 3:  [2, 2, 2, 3]  (2 != val, write)
               ↑  ↑
            write read

Step 4:  [2, 2, 2, 3]  (3 == val, skip)
                  ↑  ↑
               write read

Result: k = 2, first 2 elements = [2, 2]
```

## Additional Resources

- [LeetCode Remove Element Problem](https://leetcode.com/problems/remove-element/)
- Two-pointer technique in array problems
- In-place array modification techniques
- Time complexity analysis

