# Merge Two Sorted Lists Problem

## Problem Description

You are given the heads of two sorted linked lists `list1` and `list2`.

Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.

Return the head of the merged linked list.

**Constraints:**
- The number of nodes in both lists is in the range [0, 50]
- -100 <= Node.val <= 100
- Both `list1` and `list2` are sorted in non-decreasing order

## Examples

### Example 1:
```
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]
```

### Example 2:
```
Input: list1 = [], list2 = []
Output: []
```

### Example 3:
```
Input: list1 = [], list2 = [0]
Output: [0]
```

## Solution Approach

### Algorithm: Two-Pointer Merge

**Strategy:**
1. Use a dummy node to simplify the merge process and avoid special cases
2. Maintain a tail pointer to track the end of the merged list
3. Compare nodes from both lists
4. Attach the smaller node to the result and move forward
5. When one list is exhausted, attach the remaining nodes from the other list

**Key Insight:**
- Since both lists are already sorted, we can merge them in a single pass
- The dummy node technique eliminates the need to handle the first node separately
- We don't need to create new nodes - we can reuse existing nodes by adjusting pointers

**Time Complexity:** O(n + m)
- Where n is the length of `list1` and m is the length of `list2`
- We visit each node exactly once

**Space Complexity:** O(1)
- Only using a few pointers (dummy node, tail, and temporary pointers)
- No additional data structures or recursion stack

**Advantages:**
- Optimal time and space complexity
- In-place merging (reuses existing nodes)
- Simple and elegant solution
- Handles all edge cases naturally

**Disadvantages:**
- Modifies the original lists (though this is expected behavior)
- Requires understanding of pointer manipulation

## Implementation Details

### Dummy Node Technique

The dummy node is a common pattern in linked list problems that simplifies edge case handling:

```c
struct ListNode dummy;
struct ListNode* tail = &dummy;
dummy.next = NULL;
```

**Why use a dummy node?**
- Eliminates the need to check if the result list is empty
- Provides a consistent starting point
- Simplifies the code by removing special cases
- Makes it easier to build the list incrementally

### Merge Process

```c
while (list1 != NULL && list2 != NULL) {
    if (list1->val <= list2->val) {
        tail->next = list1;
        list1 = list1->next;
    } else {
        tail->next = list2;
        list2 = list2->next;
    }
    tail = tail->next;
}
```

**Step-by-step:**
1. Compare the current nodes from both lists
2. Attach the smaller node to the tail
3. Move the pointer of the list we took from forward
4. Move the tail pointer forward
5. Repeat until one list is exhausted

### Handling Remaining Nodes

```c
if (list1 != NULL) {
    tail->next = list1;
} else {
    tail->next = list2;
}
```

Since the remaining nodes are already sorted and connected, we can simply attach the entire remaining portion at once.

## Questions & Analysis

### 1. Why do we use `<=` instead of `<` in the comparison?
We use `<=` to maintain stability. When values are equal, we prefer the node from `list1` first. This ensures consistent behavior and matches the expected output in examples.

### 2. What happens to the original lists?
The original lists are modified during the merge process. The nodes are reused by adjusting their `next` pointers. If you need to preserve the original lists, you would need to create copies of the nodes.

### 3. Can we solve this recursively?
Yes, here's a recursive approach:

```c
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    
    if (list1->val <= list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}
```

**Recursive vs Iterative:**
- **Recursive:** More elegant, but uses O(n + m) space for the call stack
- **Iterative:** More efficient space-wise (O(1)), preferred for production code

### 4. What if the lists have different lengths?
The algorithm handles this naturally. When the shorter list is exhausted, the remaining nodes from the longer list are attached in one operation. Since they're already sorted, no further processing is needed.

### 5. Edge Cases to Consider:
- Both lists empty → Returns `NULL` (empty list)
- One list empty → Returns the other list
- Lists with different lengths → Handled automatically
- Lists with duplicate values → Handled correctly
- Lists with negative numbers → Works as expected (within constraint range)
- Single node lists → Works correctly

### 6. Memory Management
**Important:** The function reuses existing nodes, so:
- The caller should not free the original lists after merging
- Only the merged list should be freed
- If you need to preserve original lists, create copies first

## Testing

### Building the Program

```bash
gcc -Wall -Wextra -std=c11 -O2 merge_two_sorted_lists.c -o merge_two_sorted_lists
```

Or if you have a Makefile:

```bash
make
```

### Running Tests

```bash
./merge_two_sorted_lists
```

### Expected Output

```
Merge Two Sorted Lists Problem
==============================

Example 1:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Example 2:
Input: list1 = [], list2 = []
Output: []

Example 3:
Input: list1 = [], list2 = [0]
Output: [0]

Additional Test Cases:
=====================

Test 1: Different ranges
Input: list1 = [1,3,5], list2 = [2,4,6]
Output: [1,2,3,4,5,6]

Test 2: No overlap
Input: list1 = [1,2,3], list2 = [4,5,6]
Output: [1,2,3,4,5,6]

Test 3: One list much longer
Input: list1 = [1], list2 = [1,2,3,4,5]
Output: [1,1,2,3,4,5]

Test 4: Negative numbers
Input: list1 = [-10,-5,0], list2 = [-8,-3,7]
Output: [-10,-8,-5,-3,0,7]
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: Lists with many duplicates
int arr1[] = {1, 1, 1, 2, 2, 3};
int arr2[] = {1, 1, 2, 2, 2, 4};
struct ListNode* list1 = createList(arr1, 6);
struct ListNode* list2 = createList(arr2, 6);
struct ListNode* merged = mergeTwoLists(list1, list2);
printList(merged);  // Expected: [1,1,1,1,1,2,2,2,2,2,3,4]
freeList(merged);

// Test case: One list is much longer
int arr3[] = {1};
int arr4[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
struct ListNode* list3 = createList(arr3, 1);
struct ListNode* list4 = createList(arr4, 9);
struct ListNode* merged2 = mergeTwoLists(list3, list4);
printList(merged2);
freeList(merged2);
```

### Test Cases Checklist

- [x] Basic case with overlapping values (Example 1)
- [x] Both lists empty (Example 2)
- [x] One list empty (Example 3)
- [x] Different ranges, no overlap
- [x] Lists with different lengths
- [x] Negative numbers
- [ ] Lists with many duplicates
- [ ] Single node lists
- [ ] Maximum constraint values (50 nodes, val = 100)
- [ ] Minimum constraint values (val = -100)

### Performance Testing

To analyze performance:

1. **Time the execution:**
```bash
time ./merge_two_sorted_lists
```

2. **Test with maximum size lists:**
   - Create two lists with 50 nodes each
   - Verify the merge completes quickly

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./merge_two_sorted_lists
```

## Function Signature

```c
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2);
```

**Parameters:**
- `list1`: Head of the first sorted linked list (can be NULL)
- `list2`: Head of the second sorted linked list (can be NULL)

**Returns:**
- Head of the merged sorted linked list
- Returns `NULL` if both input lists are empty
- The returned list reuses nodes from the input lists

**Data Structure:**
```c
struct ListNode {
    int val;
    struct ListNode *next;
};
```

## Memory Management

**Important Notes:**
- The function reuses existing nodes from the input lists
- Do NOT free the original lists after calling this function
- Only free the merged list returned by the function
- If you need to preserve the original lists, create copies first

**Example:**
```c
struct ListNode* list1 = createList(arr1, size1);
struct ListNode* list2 = createList(arr2, size2);

// Merge the lists
struct ListNode* merged = mergeTwoLists(list1, list2);

// Use the merged list
printList(merged);

// Free only the merged list (don't free list1 or list2 separately)
freeList(merged);
```

## Alternative Approaches

### Recursive Solution

```c
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // Base cases
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    
    // Recursive case
    if (list1->val <= list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}
```

**Trade-offs:**
- **Pros:** More elegant, fewer lines of code
- **Cons:** Uses O(n + m) space for recursion stack, risk of stack overflow for large lists

### When to Use Each Approach:
- **Use Iterative (current):** Production code, large lists, memory-constrained environments
- **Use Recursive:** Small lists, code clarity is priority, educational purposes

## Additional Resources

- [LeetCode Merge Two Sorted Lists Problem](https://leetcode.com/problems/merge-two-sorted-lists/)
- Linked list data structure fundamentals
- Two-pointer technique
- Dummy node pattern in linked lists
- Time and space complexity analysis

## Related Problems

- Merge k Sorted Lists
- Merge Sorted Array
- Sort List
- Reverse Linked List

