# Merge Sorted Array

## Problem Description

You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, and two integers `m` and `n`, representing the number of elements in `nums1` and `nums2` respectively.

Merge `nums1` and `nums2` into a single array sorted in non-decreasing order.

The final sorted array should **not** be returned by the function, but instead be stored inside the array `nums1`. To accommodate this, `nums1` has a length of `m + n`, where the first `m` elements denote the elements that should be merged, and the last `n` elements are set to 0 and should be ignored. `nums2` has a length of `n`.

## Examples

### Example 1
```
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
```

### Example 2
```
Input: nums1 = [1], m = 1, nums2 = [], n = 0
Output: [1]
Explanation: The arrays we are merging are [1] and [].
The result of the merge is [1].
```

### Example 3
```
Input: nums1 = [0], m = 0, nums2 = [1], n = 1
Output: [1]
Explanation: The arrays we are merging are [] and [1].
The result of the merge is [1].
Note that because m = 0, there are no elements in nums1.
```

## Constraints

- `nums1.length == m + n`
- `nums2.length == n`
- `0 <= m, n <= 200`
- `1 <= m + n <= 200`
- `-10^9 <= nums1[i], nums2[j] <= 10^9`

## Solution Approach

### Algorithm: Three-Pointer Merge from the End

The key insight is to **merge from the end** of `nums1` rather than the beginning. This avoids overwriting elements in `nums1` that we haven't yet read.

1. **Pointers**:
   - `i` = m - 1 (last valid element in nums1)
   - `j` = n - 1 (last element in nums2)
   - `k` = m + n - 1 (position to write in nums1)

2. **Merge loop**: While both `i >= 0` and `j >= 0`:
   - Compare `nums1[i]` and `nums2[j]`
   - Place the larger value at `nums1[k]`
   - Decrement the appropriate pointers and `k`

3. **Remaining elements**:
   - If `nums2` has remaining elements (j >= 0), copy them to `nums1`
   - If `nums1` has remaining elements (i >= 0), they are already in place—no action needed

### Why Merge from the End?

If we merged from the beginning, we would overwrite `nums1` elements before reading them. By starting at the end, we write into the "empty" slot (the trailing zeros) first, and we never overwrite unread data.

### Complexity Analysis

- **Time Complexity**: O(m + n) — each element is examined at most once
- **Space Complexity**: O(1) — in-place merge, no extra allocation

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./merge_sorted_array
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

The program includes:

1. **Example 1**: [1,2,3] + [2,5,6] → [1,2,2,3,5,6]
2. **Example 2**: [1] + [] → [1]
3. **Example 3**: [] + [1] → [1]
4. **Empty nums1**: [] + [1,2] → [1,2]
5. **Empty nums2**: [1,2,3] + [] → [1,2,3]
6. **nums2 all larger**: [1,2,3] + [4,5,6] → [1,2,3,4,5,6]
7. **Interleaved**: [1,3,5] + [2,4,6] → [1,2,3,4,5,6]
