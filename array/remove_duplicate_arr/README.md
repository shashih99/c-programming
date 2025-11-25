# Remove Duplicates from Sorted Array

## Problem Statement

Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates **in-place** such that each unique element appears only **once**. The **relative order** of the elements should be kept the **same**.

Consider the number of unique elements in `nums` to be `k`. After removing duplicates, return the number of unique elements `k`.

The first `k` elements of `nums` should contain the unique numbers in sorted order. The remaining elements beyond index `k - 1` can be ignored.

### Custom Judge

The judge will test your solution with the following code:

```c
int[] nums = [...]; // Input array
int[] expectedNums = [...]; // The expected answer with correct length

int k = removeDuplicates(nums); // Calls your implementation

assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
```

If all assertions pass, then your solution will be accepted.

### Examples

**Example 1:**
- Input: `nums = [1,1,2]`
- Output: `k = 2, nums = [1,2,_]`
- Explanation: Your function should return `k = 2`, with the first two elements of `nums` being `1` and `2` respectively. It does not matter what you leave beyond the returned `k` (hence they are underscores).

**Example 2:**
- Input: `nums = [0,0,1,1,1,2,2,3,3,4]`
- Output: `k = 5, nums = [0,1,2,3,4,_,_,_,_,_]`
- Explanation: Your function should return `k = 5`, with the first five elements of `nums` being `0, 1, 2, 3, and 4` respectively. It does not matter what you leave beyond the returned `k` (hence they are underscores).

### Constraints

- `1 <= nums.length <= 3 * 10^4`
- `-100 <= nums[i] <= 100`
- `nums` is sorted in **non-decreasing order**

## Solution Approach

### Two-Pointer Technique

This solution uses the **two-pointer technique**:

1. **Initialize pointers**: 
   - `write` pointer starts at index 1 (first element is always unique)
   - `read` pointer starts at index 1 to scan through the array

2. **Compare and write**:
   - Since the array is sorted, duplicates will be adjacent
   - Compare the current element (`nums[read]`) with the last written unique element (`nums[write - 1]`)
   - If they are different, write the current element to position `write` and increment `write`
   - If they are the same (duplicate), skip it (don't increment `write`)

3. **Return count**: The `write` pointer represents the number of unique elements

### Algorithm Details

```
removeDuplicates(nums, numsSize):
    1. If numsSize == 0, return 0
    2. Initialize write = 1 (first element is always unique)
    3. For read from 1 to numsSize - 1:
       a. If nums[read] != nums[write - 1]:
          - nums[write] = nums[read]
          - write++
       b. Else: skip (duplicate)
    4. Return write
```

### Complexity Analysis

- **Time Complexity**: O(n)
  - We traverse the array once with the `read` pointer
  - Each element is examined exactly once

- **Space Complexity**: O(1)
  - We only use a few extra variables (`write`, `read`)
  - The array is modified in-place, no additional data structures are used

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

1. **Example 1**: `[1,1,2]` → `k = 2, [1,2]`
2. **Example 2**: `[0,0,1,1,1,2,2,3,3,4]` → `k = 5, [0,1,2,3,4]`
3. **Single element**: `[1]` → `k = 1, [1]`
4. **All duplicates**: `[1,1,1,1,1]` → `k = 1, [1]`
5. **No duplicates**: `[1,2,3,4,5]` → `k = 5, [1,2,3,4,5]`
6. **Empty array**: `[]` → `k = 0, []`
7. **Negative numbers**: `[-5,-5,-3,-3,-1,0,0,2,2]` → `k = 5, [-5,-3,-1,0,2]`
8. **Large array**: `[1,1,2,2,2,3,3,3,3,4,4,5,5,5,5,5]` → `k = 5, [1,2,3,4,5]`

## Key Points

- The function modifies the array **in-place** - no new array is created
- The first element is always unique, so we start writing from index 1
- Since the array is sorted, duplicates are always adjacent
- The algorithm is efficient with O(n) time and O(1) space complexity
- The solution handles edge cases like empty arrays, single elements, and all duplicates

