# Remove Duplicates from Sorted List

## Problem Statement

Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.

### Examples

**Example 1:**
- Input: `head = [1,1,2]`
- Output: `[1,2]`
- Explanation: The duplicate `1` is removed.

**Example 2:**
- Input: `head = [1,1,2,3,3]`
- Output: `[1,2,3]`
- Explanation: Duplicate `1` and duplicate `3` are removed.

### Constraints

- The number of nodes in the list is in the range [0, 300]
- `-100 <= Node.val <= 100`
- The list is guaranteed to be sorted in ascending order

## Solution Approach

### Method: Single-Pass Traversal

Since the list is **sorted**, all duplicate values appear consecutively. We can remove duplicates in a single pass by comparing each node with its successor.

**Algorithm:**
1. Handle edge case: if `head` is NULL, return NULL
2. Traverse the list with a `current` pointer
3. At each step, compare `current->val` with `current->next->val`
4. If they are equal, skip the duplicate by setting `current->next = current->next->next` (and free the duplicate node)
5. If they differ, advance `current` to the next node
6. Return the head

**Time Complexity:** O(n)
- Single pass through the list
- Each node is visited at most once

**Space Complexity:** O(1)
- Only using a few pointers
- No additional data structures

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

### Debug Build
```bash
make debug
```

### Run Debug Build
```bash
make debug-run
```

## Test Cases

The program includes the following test cases:

1. **Example 1**: `[1,1,2]` → `[1,2]`
2. **Example 2**: `[1,1,2,3,3]` → `[1,2,3]`
3. **Edge case**: `[]` → `[]`
4. **Edge case**: `[1]` → `[1]`
5. **All duplicates**: `[1,1,1]` → `[1]`
6. **No duplicates**: `[1,2,3]` → `[1,2,3]`

## Function Signature

```c
struct ListNode* deleteDuplicates(struct ListNode* head);
```

**Parameters:**
- `head`: Head of the sorted linked list (can be NULL)

**Returns:**
- Head of the linked list with duplicates removed
- Returns `NULL` if the input list is empty

**Data Structure:**
```c
struct ListNode {
    int val;
    struct ListNode *next;
};
```

## Additional Resources

- [LeetCode Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)
- Linked list traversal
- In-place modification
