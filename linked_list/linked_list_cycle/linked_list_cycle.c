#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * 141. Linked List Cycle
 *
 * Given head, the head of a linked list, determine if the linked list has a
 * cycle in it. There is a cycle if some node can be reached again by
 * continuously following the next pointer.
 *
 * Algorithm (Floyd's tortoise and hare):
 * 1. Start two pointers at head: slow moves 1 step, fast moves 2 steps.
 * 2. If there is no cycle, fast reaches NULL and we return false.
 * 3. If there is a cycle, both pointers end up looping inside it. Each step
 *    fast gains exactly one node on slow, so it must land on slow eventually
 *    (it can never "jump over" it).
 *
 * Time Complexity: O(n) - slow enters the cycle within n steps, and fast
 *                  catches it within one more lap
 * Space Complexity: O(1) - only two pointers, no visited set
 *
 * @param head: Head of the linked list (can be NULL)
 * @return: true if the list contains a cycle, false otherwise
 */
bool hasCycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    // fast checks both fast and fast->next so fast->next->next is safe
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

/**
 * Build a list from vals[0..n-1]. If pos >= 0, link the tail back to the
 * node at index pos (this mirrors how LeetCode describes the input).
 * Nodes are allocated as one array so cleanup is a single free(), regardless
 * of whether the list loops.
 */
struct ListNode* buildList(const int* vals, int n, int pos) {
    if (n == 0) {
        return NULL;
    }

    struct ListNode* nodes = malloc(sizeof(struct ListNode) * n);
    if (nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        nodes[i].val = vals[i];
        nodes[i].next = (i + 1 < n) ? &nodes[i + 1] : NULL;
    }
    if (pos >= 0) {
        nodes[n - 1].next = &nodes[pos];
    }

    return nodes;
}

/**
 * Run one test case and report PASS/FAIL against the expected result
 */
void runTest(const char* name, const int* vals, int n, int pos, bool expected) {
    struct ListNode* head = buildList(vals, n, pos);
    bool result = hasCycle(head);

    printf("%s:\n", name);
    printf("Input: head = [");
    for (int i = 0; i < n; i++) {
        printf("%d%s", vals[i], i + 1 < n ? "," : "");
    }
    printf("], pos = %d\n", pos);
    printf("Output: %s (expected %s) %s\n\n",
           result ? "true" : "false",
           expected ? "true" : "false",
           result == expected ? "PASS" : "FAIL");

    free(head);  // nodes were allocated as one block
}

int main() {
    printf("Linked List Cycle\n");
    printf("=================\n\n");

    // Example 1: tail connects to node index 1
    int v1[] = {3, 2, 0, -4};
    runTest("Example 1", v1, 4, 1, true);

    // Example 2: tail connects to node index 0
    int v2[] = {1, 2};
    runTest("Example 2", v2, 2, 0, true);

    // Example 3: single node, no cycle
    int v3[] = {1};
    runTest("Example 3", v3, 1, -1, false);

    printf("Additional Test Cases:\n\n");

    // Empty list
    runTest("Test Case 4 (empty list)", NULL, 0, -1, false);

    // Single node pointing to itself
    int v5[] = {7};
    runTest("Test Case 5 (self loop)", v5, 1, 0, true);

    // Two nodes, no cycle
    int v6[] = {1, 2};
    runTest("Test Case 6 (two nodes, no cycle)", v6, 2, -1, false);

    // Odd length, no cycle
    int v7[] = {1, 2, 3, 4, 5};
    runTest("Test Case 7 (odd length, no cycle)", v7, 5, -1, false);

    // Tail points to itself (cycle of length 1 at the end)
    int v8[] = {1, 2, 3, 4, 5};
    runTest("Test Case 8 (tail self loop)", v8, 5, 4, true);

    // Duplicate values must not fool the check (compares nodes, not values)
    int v9[] = {1, 1, 1, 1};
    runTest("Test Case 9 (duplicate values, no cycle)", v9, 4, -1, false);

    return 0;
}
