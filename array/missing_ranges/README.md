# Missing Ranges (LeetCode 163)

## Problem Description

You are given an inclusive range `[lower, upper]` and a **sorted unique** integer array `nums`, where all elements are within the inclusive range.

A number `x` is considered *missing* if `x` is in the range `[lower, upper]` and `x` is not in `nums`.

Return the **shortest sorted** list of ranges that exactly covers all the missing numbers. That is, no element of `nums` is included in any of the ranges, and each missing number is covered by one of the ranges.

**Constraints:**
- `-10^9 <= lower <= upper <= 10^9`
- `0 <= nums.length <= 100`
- `lower <= nums[i] <= upper`
- All values of `nums` are unique

## Examples

### Example 1:
```
Input: nums = [0,1,3,50,75], lower = 0, upper = 99
Output: [[2,2],[4,49],[51,74],[76,99]]
```

### Example 2:
```
Input: nums = [-1], lower = -1, upper = -1
Output: []
```

## Solution: Single Pass

Keep `next`, the smallest number not yet accounted for (starts at `lower`).
For each `nums[i]` (plus a sentinel `upper + 1` at the end):
- if `nums[i] > next`, the range `[next, nums[i] - 1]` is missing
- set `next = nums[i] + 1`

`long long` is used for `next` and the sentinel so `upper + 1` / `nums[i] + 1` can't overflow when a value equals `INT_MAX`.

**Time Complexity:** O(n)
**Space Complexity:** O(n) for the output (at most `n + 1` ranges)

## Function Signature

```c
int** findMissingRanges(int* nums, int numsSize, int lower, int upper,
                        int* returnSize, int** returnColumnSizes);
```

The caller must free each range, the outer array, and `*returnColumnSizes`.

## Edge Cases
- Empty `nums` → the whole `[lower, upper]` is one range
- No gaps → `[]`
- Values at `INT_MIN` / `INT_MAX` → no overflow thanks to `long long`

## Build & Run

```bash
make run
```

## Resources

- [LeetCode 163. Missing Ranges](https://leetcode.com/problems/missing-ranges/) (Premium)
