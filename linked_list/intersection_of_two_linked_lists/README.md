# Intersection of Two Linked Lists

## Problem Description

Given the heads of two singly linked lists `headA` and `headB`, return *the node at which the two lists intersect*. If the two linked lists have no intersection at all, return `null`.

For example, the following two linked lists begin to intersect at node `c1`:

```
A:      a1 → a2 ↘
                  c1 → c2 → c3
B: b1 → b2 → b3 ↗
```

The test cases are generated such that there are no cycles anywhere in the entire linked structure.

**Note** that the linked lists must **retain their original structure** after the function returns.

### Custom Judge

The inputs to the judge are given as follows (your program is **not** given these inputs):

- `intersectVal` - The value of the node where the intersection occurs. This is `0` if there is no intersected node.
- `listA` - The first linked list.
- `listB` - The second linked list.
- `skipA` - The number of nodes to skip ahead in `listA` (starting from the head) to get to the intersected node.
- `skipB` - The number of nodes to skip ahead in `listB` (starting from the head) to get to the intersected node.

The judge then builds the linked structure from these inputs and passes the two heads, `headA` and `headB`, to your program. If you return the intersected node, your solution is accepted.

## Examples

### Example 1
```
Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
Output: Intersected at '8'
Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5].
There are 2 nodes before the intersected node in A; there are 3 nodes before the intersected node in B.
Note that the intersected node's value is not 1 because the nodes with value 1 in A and B
(2nd node in A and 3rd node in B) are different node references.
```

### Example 2
```
Input: intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Intersected at '2'
```

### Example 3
```
Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: No intersection
Explanation: The two lists do not intersect, so return null.
```

## Constraints

- The number of nodes of `listA` is `m`; of `listB` is `n`.
- `1 <= m, n <= 3 * 10^4`
- `1 <= Node.val <= 10^5`
- `0 <= skipA <= m`, `0 <= skipB <= n`
- `intersectVal` is `0` if `listA` and `listB` do not intersect.
- `intersectVal == listA[skipA] == listB[skipB]` if `listA` and `listB` intersect.

**Follow up:** Could you write a solution that runs in `O(m + n)` time and uses only `O(1)` memory?

## Solution Approach

### Key Insight

Intersection means **the same node in memory**, not the same value. Once two singly linked lists share a node, they share every node after it (each node has only one `next`), so the shape is always a **Y**, never an X.

Split the lengths as:

- `A = a + c` (a nodes only in A, then c shared nodes)
- `B = b + c` (b nodes only in B, then the same c shared nodes)

The only problem is that `a != b`, so walking both lists in step doesn't line them up at the join.

### Algorithm (two pointers that switch lists)

1. `pA` starts at `headA`, `pB` starts at `headB`.
2. Move both one step at a time.
3. When `pA` runs off the end of A, send it to `headB`. When `pB` runs off the end of B, send it to `headA`.
4. Stop when `pA == pB`.

After switching, `pA` has walked `a + c + b` and `pB` has walked `b + c + a`, **the same distance**, so they land on the first shared node at the same moment.

If the lists don't intersect (`c = 0`), both pointers become `NULL` at the same time after `a + b` steps. `NULL == NULL` ends the loop, and we return `NULL`.

### Implementation Details

```c
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *pA = headA;
    struct ListNode *pB = headB;

    while (pA != pB) {
        pA = (pA == NULL) ? headB : pA->next;
        pB = (pB == NULL) ? headA : pB->next;
    }

    return pA;
}
```

### Walkthrough (Example 2: A = `[1,9,1,2,4]`, B = `[3,2,4]`, shared tail `2 → 4`)

Here a = 3, b = 1, c = 2. Both pointers reach the join after `a + c + 1 + b` = `b + c + 1 + a` = 7 moves (the `+1` is the step onto `NULL` before switching).

| Step | pA        | pB        | Equal? |
|------|-----------|-----------|--------|
| 0    | A:1       | B:3       | no     |
| 1    | A:9       | 2 (shared)| no     |
| 2    | A:1       | 4 (shared)| no     |
| 3    | 2 (shared)| NULL      | no     |
| 4    | 4 (shared)| A:1       | no     |
| 5    | NULL      | A:9       | no     |
| 6    | B:3       | A:1       | no     |
| 7    | **2**     | **2**     | **yes → return node 2** |

Note step 3: `pA` is on the shared `2` while `pB` is on `NULL`. They are not equal, so the loop continues. Only after both have switched do they line up.

### Complexity Analysis

- **Time Complexity**: O(m + n) — each pointer walks at most `m + n + 1` steps
- **Space Complexity**: O(1) — two pointers, and the lists are never modified

## Alternative Approaches

### Length Difference
- Count both lengths, advance the longer list's head by `|m - n|`, then walk both together until they meet
- Also O(m + n) time and O(1) space; does the same alignment explicitly, at the cost of more code

### Hash Set of Visited Nodes
- Store every node address of A, then walk B and return the first address already in the set
- **Space**: O(m) — fails the follow-up, and C has no built-in hash set

### Brute Force
- For every node of A, scan all of B for the same address
- **Time**: O(m · n)

**The switching two-pointer approach meets the follow-up with the least code.**

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./intersection_of_two_linked_lists
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

The test harness builds the lists the way the LeetCode judge does (from `listA`, `listB`, `skipA`, `skipB`), and checks the result by **pointer**, printing PASS/FAIL:

1. **Example 1**: `[4,1,8,4,5]` / `[5,6,1,8,4,5]` → `8` (the earlier `1`s are different nodes)
2. **Example 2**: `[1,9,1,2,4]` / `[3,2,4]` → `2`
3. **Example 3**: `[2,6,4]` / `[1,5]` → no intersection
4. **Same list**: both heads are the same node → that head
5. **B is a suffix of A**: `headB` itself is the intersection
6. **Share only the tail**: last node only → `9`
7. **Equal values, different nodes**: `[5]` / `[5]` → no intersection
8. **Very different lengths, no intersection**: `[1..7]` / `[8]`
9. **Very different lengths, intersect at tail**: `[1..7]` / `[8,7]` → `7`

## Notes

- Compare **node pointers**, never `val` — test 7 and Example 1 exist to catch value comparisons
- Switch on `pA == NULL`, not `pA->next == NULL`. Letting each pointer step onto `NULL` once is what makes the no-intersection case end with both on `NULL` together; switching early would loop forever when there's no intersection
- The lists are never modified, satisfying "retain their original structure"
- In the test harness, A is one allocation and B's own prefix is another, so cleanup is two `free()` calls and the shared tail is freed once
