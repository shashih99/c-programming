#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * 160. Intersection of Two Linked Lists
 *
 * Given the heads of two singly linked lists headA and headB, return the node
 * at which the two lists intersect. If the two lists have no intersection at
 * all, return NULL. The lists must keep their original structure.
 *
 * "Intersect" means the same node in memory, not the same value: once the
 * lists meet they share every node after that point (a Y shape).
 *
 * Algorithm (two pointers that switch lists):
 * 1. Let A = a + c nodes and B = b + c nodes, where c is the shared tail.
 * 2. Walk pA along A and pB along B. When a pointer runs off the end, send
 *    it to the head of the *other* list.
 * 3. After switching, pA has walked a + c + b and pB has walked b + c + a,
 *    the same distance, so they arrive at the first shared node together.
 * 4. If there is no shared tail (c = 0), both reach NULL at the same time
 *    after a + b steps, and the loop ends with NULL.
 *
 * Time Complexity: O(m + n) - each pointer walks at most both lists once
 * Space Complexity: O(1) - only two pointers, no hash set of visited nodes
 *
 * @param headA: Head of the first list (can be NULL)
 * @param headB: Head of the second list (can be NULL)
 * @return: The first shared node, or NULL if the lists don't intersect
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *pA = headA;
    struct ListNode *pB = headB;

    // Compare node addresses, not values. Ends when they meet or both are NULL.
    while (pA != pB) {
        pA = (pA == NULL) ? headB : pA->next;
        pB = (pB == NULL) ? headA : pB->next;
    }

    return pA;
}

/**
 * Allocate n nodes as one block, chained in order, with the last node's next
 * set to tail. Returns NULL when n == 0.
 */
static struct ListNode* buildChain(const int* vals, int n, struct ListNode* tail) {
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
        nodes[i].next = (i + 1 < n) ? &nodes[i + 1] : tail;
    }

    return nodes;
}

static void printArray(const int* vals, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d%s", vals[i], i + 1 < n ? "," : "");
    }
    printf("]");
}

/**
 * Run one test case the way LeetCode describes the input: listA is built in
 * full, then listB's first skipB nodes are built separately and their tail is
 * linked to listA's node at index skipA. If skipA == lenA (and skipB == lenB)
 * the lists don't intersect.
 *
 * The expected answer is the join node itself (or NULL), so PASS/FAIL is a
 * pointer comparison, exactly what LeetCode checks.
 */
void runTest(const char* name,
             const int* a, int lenA,
             const int* b, int lenB,
             int skipA, int skipB) {
    struct ListNode* headA = buildChain(a, lenA, NULL);

    struct ListNode* join = NULL;
    if (skipA < lenA) {
        join = &headA[skipA];
    }
    struct ListNode* prefixB = buildChain(b, skipB, join);
    struct ListNode* headB = (skipB > 0) ? prefixB : join;

    struct ListNode* expected = join;
    struct ListNode* result = getIntersectionNode(headA, headB);

    printf("%s:\n", name);
    printf("Input: listA = ");
    printArray(a, lenA);
    printf(", listB = ");
    printArray(b, lenB);
    printf(", skipA = %d, skipB = %d\n", skipA, skipB);

    if (result == NULL) {
        printf("Output: No intersection");
    } else {
        printf("Output: Intersected at '%d'", result->val);
    }
    if (expected == NULL) {
        printf(" (expected No intersection)");
    } else {
        printf(" (expected '%d')", expected->val);
    }
    printf(" %s\n\n", result == expected ? "PASS" : "FAIL");

    free(prefixB);  // B's own nodes, one block (free(NULL) is fine)
    free(headA);    // A's nodes, including the shared tail
}

int main() {
    printf("Intersection of Two Linked Lists\n");
    printf("================================\n\n");

    // Example 1: intersect at the 8 node; note the 1s before it are
    // different nodes, so they must not count as the intersection
    int a1[] = {4, 1, 8, 4, 5};
    int b1[] = {5, 6, 1, 8, 4, 5};
    runTest("Example 1", a1, 5, b1, 6, 2, 3);

    // Example 2: intersect at the 2 node
    int a2[] = {1, 9, 1, 2, 4};
    int b2[] = {3, 2, 4};
    runTest("Example 2", a2, 5, b2, 3, 3, 1);

    // Example 3: no intersection
    int a3[] = {2, 6, 4};
    int b3[] = {1, 5};
    runTest("Example 3", a3, 3, b3, 2, 3, 2);

    printf("Additional Test Cases:\n\n");

    // Both lists are the same list: intersect at the head
    int a4[] = {1, 2, 3};
    runTest("Test Case 4 (same list)", a4, 3, a4, 3, 0, 0);

    // B is just a suffix of A: B's head is the intersection
    int a5[] = {1, 2, 3, 4};
    int b5[] = {3, 4};
    runTest("Test Case 5 (B is a suffix of A)", a5, 4, b5, 2, 2, 0);

    // Only the last node is shared
    int a6[] = {1, 2, 3, 9};
    int b6[] = {7, 9};
    runTest("Test Case 6 (share only the tail)", a6, 4, b6, 2, 3, 1);

    // Single nodes, not shared, same value: values must not fool it
    int a7[] = {5};
    int b7[] = {5};
    runTest("Test Case 7 (equal values, different nodes)", a7, 1, b7, 1, 1, 1);

    // Very different lengths, no intersection
    int a8[] = {1, 2, 3, 4, 5, 6, 7};
    int b8[] = {8};
    runTest("Test Case 8 (different lengths, no intersection)", a8, 7, b8, 1, 7, 1);

    // Very different lengths, with intersection
    int a9[] = {1, 2, 3, 4, 5, 6, 7};
    int b9[] = {8, 7};
    runTest("Test Case 9 (different lengths, intersect at tail)", a9, 7, b9, 2, 6, 1);

    return 0;
}
