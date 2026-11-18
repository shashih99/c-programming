# Linked List Cycle

## Problem Description

Given `head`, the head of a linked list, determine if the linked list has a cycle in it.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer. Internally, `pos` is used to denote the index of the node that tail's `next` pointer is connected to. **Note that `pos` is not passed as a parameter.**

Return `true` if there is a cycle in the linked list. Otherwise, return `false`.

## Examples

### Example 1
```
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 1st node (0-indexed).
```

### Example 2
```
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where the tail connects to the 0th node.
```

### Example 3
```
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
```

## Constraints

- The number of nodes in the list is in the range `[0, 10^4]`.
- `-10^5 <= Node.val <= 10^5`
- `pos` is `-1` or a valid index in the linked list.

**Follow up:** Can you solve it using `O(1)` (i.e. constant) memory?

## Solution Approach

### Algorithm

The solution uses **Floyd's cycle detection (tortoise and hare)**:

1. **Two pointers**: `slow` and `fast` both start at `head`.
2. **Different speeds**: each iteration, `slow` moves 1 node and `fast` moves 2.
3. **No cycle**: `fast` eventually hits `NULL` → return `false`.
4. **Cycle**: both pointers get trapped in the loop. Inside it, `fast` closes the gap to `slow` by exactly one node per step, so it can't skip over `slow` — they must meet → return `true`.

### Implementation Details

```c
bool hasCycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
```

### Walkthrough (Example 1: `[3,2,0,-4]`, `pos = 1`)

The list is `3 → 2 → 0 → -4 → (back to 2)`.

| Step | slow | fast | Meet? |
|------|------|------|-------|
| 0    | 3    | 3    | start |
| 1    | 2    | 0    | no    |
| 2    | 0    | 2    | no    |
| 3    | -4   | -4   | **yes → true** |

### Complexity Analysis

- **Time Complexity**: O(n) — `slow` reaches the cycle within n steps, then `fast` catches it within one lap
- **Space Complexity**: O(1) — only two pointers

## Alternative Approaches

### Hash Set of Visited Nodes
- Walk the list, storing each node's address; seeing an address twice means a cycle
- **Space**: O(n) — doesn't satisfy the follow-up, and C has no built-in hash set

**Floyd's algorithm meets the O(1) memory follow-up.**

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./linked_list_cycle
```

### Debug build
```bash
make debug
make debug-run
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

The program checks each result against the expected value and prints PASS/FAIL:

1. **Example 1**: `[3,2,0,-4]`, pos `1` → `true`
2. **Example 2**: `[1,2]`, pos `0` → `true`
3. **Example 3**: `[1]`, pos `-1` → `false`
4. **Empty list**: `[]` → `false`
5. **Self loop**: `[7]`, pos `0` → `true`
6. **Two nodes, no cycle**: `[1,2]` → `false`
7. **Odd length, no cycle**: `[1,2,3,4,5]` → `false`
8. **Tail self loop**: `[1,2,3,4,5]`, pos `4` → `true`
9. **Duplicate values**: `[1,1,1,1]` → `false`

## Notes

- Compare **node pointers**, not values — duplicate values (test 9) don't indicate a cycle
- The loop guard checks both `fast` and `fast->next` so `fast->next->next` never dereferences `NULL`
- Check for a meeting **after** moving, otherwise `slow == fast` is trivially true at the start
- In the test harness, nodes are allocated as one array so a cyclic list can be freed with a single `free()` (walking a cyclic list to free it would loop forever)
