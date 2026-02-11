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
 * Remove Duplicates from Sorted List
 *
 * Given the head of a sorted linked list, delete all duplicates such that
 * each element appears only once. Return the linked list sorted as well.
 *
 * Algorithm: Single-Pass Traversal
 *
 * Since the list is sorted, all duplicates appear consecutively. We traverse
 * once and skip any node whose value equals the previous node's value.
 *
 * Time Complexity: O(n) - single pass through the list
 * Space Complexity: O(1) - only using pointers
 *
 * @param head: Head of the sorted linked list (can be NULL)
 * @return: Head of the list with duplicates removed
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (head == NULL) {
        return NULL;
    }

    struct ListNode* current = head;

    while (current->next != NULL) {
        if (current->val == current->next->val) {
            /* Duplicate found - skip the next node and free it */
            struct ListNode* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }

    return head;
}

/**
 * Helper function to create a new ListNode
 */
struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    node->val = val;
    node->next = NULL;
    return node;
}

/**
 * Helper function to create a linked list from an array
 */
struct ListNode* createList(int* arr, int size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }

    struct ListNode* head = createNode(arr[0]);
    struct ListNode* current = head;

    for (int i = 1; i < size; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }

    return head;
}

/**
 * Helper function to print a linked list
 */
void printList(struct ListNode* head) {
    if (head == NULL) {
        printf("[]");
        return;
    }

    printf("[");
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d", current->val);
        if (current->next != NULL) {
            printf(",");
        }
        current = current->next;
    }
    printf("]");
}

/**
 * Helper function to free a linked list
 */
void freeList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        struct ListNode* next = current->next;
        free(current);
        current = next;
    }
}

/**
 * Test function with the provided examples
 */
int main() {
    printf("Remove Duplicates from Sorted List\n");
    printf("==================================\n\n");

    /* Example 1: [1,1,2] -> [1,2] */
    printf("Example 1:\n");
    int arr1[] = {1, 1, 2};
    struct ListNode* list1 = createList(arr1, 3);
    printf("Input: head = ");
    printList(list1);
    printf("\n");

    struct ListNode* result1 = deleteDuplicates(list1);
    printf("Output: ");
    printList(result1);
    printf("\n\n");
    freeList(result1);

    /* Example 2: [1,1,2,3,3] -> [1,2,3] */
    printf("Example 2:\n");
    int arr2[] = {1, 1, 2, 3, 3};
    struct ListNode* list2 = createList(arr2, 5);
    printf("Input: head = ");
    printList(list2);
    printf("\n");

    struct ListNode* result2 = deleteDuplicates(list2);
    printf("Output: ");
    printList(result2);
    printf("\n\n");
    freeList(result2);

    /* Additional test cases */
    printf("Additional Test Cases:\n\n");

    /* Edge case: empty list */
    printf("Test 1: Empty list\n");
    struct ListNode* list3 = NULL;
    printf("Input: head = ");
    printList(list3);
    printf("\n");
    struct ListNode* result3 = deleteDuplicates(list3);
    printf("Output: ");
    printList(result3);
    printf("\n\n");

    /* Edge case: single node */
    printf("Test 2: Single node [1]\n");
    int arr4[] = {1};
    struct ListNode* list4 = createList(arr4, 1);
    printf("Input: head = ");
    printList(list4);
    printf("\n");
    struct ListNode* result4 = deleteDuplicates(list4);
    printf("Output: ");
    printList(result4);
    printf("\n\n");
    freeList(result4);

    /* All duplicates */
    printf("Test 3: All duplicates [1,1,1]\n");
    int arr5[] = {1, 1, 1};
    struct ListNode* list5 = createList(arr5, 3);
    printf("Input: head = ");
    printList(list5);
    printf("\n");
    struct ListNode* result5 = deleteDuplicates(list5);
    printf("Output: ");
    printList(result5);
    printf("\n\n");
    freeList(result5);

    /* No duplicates */
    printf("Test 4: No duplicates [1,2,3]\n");
    int arr6[] = {1, 2, 3};
    struct ListNode* list6 = createList(arr6, 3);
    printf("Input: head = ");
    printList(list6);
    printf("\n");
    struct ListNode* result6 = deleteDuplicates(list6);
    printf("Output: ");
    printList(result6);
    printf("\n\n");
    freeList(result6);

    return 0;
}
