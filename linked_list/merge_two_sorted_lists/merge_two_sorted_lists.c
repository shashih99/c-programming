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
 * Merge two sorted linked lists into one sorted list
 * 
 * Algorithm:
 * 1. Use a dummy node to simplify the merge process
 * 2. Compare nodes from both lists
 * 3. Attach the smaller node to the result
 * 4. Move the pointer forward
 * 5. When one list is exhausted, attach the remaining nodes
 * 
 * Time Complexity: O(n + m) where n and m are the lengths of the two lists
 * Space Complexity: O(1) - only using a few pointers
 * 
 * @param list1: Head of the first sorted linked list
 * @param list2: Head of the second sorted linked list
 * @return: Head of the merged sorted linked list
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    // Create a dummy node to simplify the merge process
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;
    
    // Merge while both lists have nodes
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
    
    // Attach remaining nodes from either list
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }
    
    // Return the head of the merged list (skip dummy node)
    return dummy.next;
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
    printf("Merge Two Sorted Lists Problem\n");
    printf("==============================\n\n");
    
    // Example 1: list1 = [1,2,4], list2 = [1,3,4]
    printf("Example 1:\n");
    int arr1[] = {1, 2, 4};
    int arr2[] = {1, 3, 4};
    struct ListNode* list1 = createList(arr1, 3);
    struct ListNode* list2 = createList(arr2, 3);
    
    printf("Input: list1 = ");
    printList(list1);
    printf(", list2 = ");
    printList(list2);
    printf("\n");
    
    struct ListNode* merged1 = mergeTwoLists(list1, list2);
    printf("Output: ");
    printList(merged1);
    printf("\n\n");
    
    freeList(merged1);
    
    // Example 2: list1 = [], list2 = []
    printf("Example 2:\n");
    struct ListNode* list3 = NULL;
    struct ListNode* list4 = NULL;
    
    printf("Input: list1 = ");
    printList(list3);
    printf(", list2 = ");
    printList(list4);
    printf("\n");
    
    struct ListNode* merged2 = mergeTwoLists(list3, list4);
    printf("Output: ");
    printList(merged2);
    printf("\n\n");
    
    // Example 3: list1 = [], list2 = [0]
    printf("Example 3:\n");
    struct ListNode* list5 = NULL;
    int arr3[] = {0};
    struct ListNode* list6 = createList(arr3, 1);
    
    printf("Input: list1 = ");
    printList(list5);
    printf(", list2 = ");
    printList(list6);
    printf("\n");
    
    struct ListNode* merged3 = mergeTwoLists(list5, list6);
    printf("Output: ");
    printList(merged3);
    printf("\n\n");
    
    freeList(merged3);
    
    // Additional test cases
    printf("Additional Test Cases:\n");
    printf("=====================\n\n");
    
    // Test: list1 = [1,3,5], list2 = [2,4,6]
    printf("Test 1: Different ranges\n");
    int arr4[] = {1, 3, 5};
    int arr5[] = {2, 4, 6};
    struct ListNode* list7 = createList(arr4, 3);
    struct ListNode* list8 = createList(arr5, 3);
    
    printf("Input: list1 = ");
    printList(list7);
    printf(", list2 = ");
    printList(list8);
    printf("\n");
    
    struct ListNode* merged4 = mergeTwoLists(list7, list8);
    printf("Output: ");
    printList(merged4);
    printf("\n\n");
    
    freeList(merged4);
    
    // Test: list1 = [1,2,3], list2 = [4,5,6]
    printf("Test 2: No overlap\n");
    int arr6[] = {1, 2, 3};
    int arr7[] = {4, 5, 6};
    struct ListNode* list9 = createList(arr6, 3);
    struct ListNode* list10 = createList(arr7, 3);
    
    printf("Input: list1 = ");
    printList(list9);
    printf(", list2 = ");
    printList(list10);
    printf("\n");
    
    struct ListNode* merged5 = mergeTwoLists(list9, list10);
    printf("Output: ");
    printList(merged5);
    printf("\n\n");
    
    freeList(merged5);
    
    // Test: list1 = [1], list2 = [1,2,3,4,5]
    printf("Test 3: One list much longer\n");
    int arr8[] = {1};
    int arr9[] = {1, 2, 3, 4, 5};
    struct ListNode* list11 = createList(arr8, 1);
    struct ListNode* list12 = createList(arr9, 5);
    
    printf("Input: list1 = ");
    printList(list11);
    printf(", list2 = ");
    printList(list12);
    printf("\n");
    
    struct ListNode* merged6 = mergeTwoLists(list11, list12);
    printf("Output: ");
    printList(merged6);
    printf("\n\n");
    
    freeList(merged6);
    
    // Test: list1 = [-10,-5,0], list2 = [-8,-3,7]
    printf("Test 4: Negative numbers\n");
    int arr10[] = {-10, -5, 0};
    int arr11[] = {-8, -3, 7};
    struct ListNode* list13 = createList(arr10, 3);
    struct ListNode* list14 = createList(arr11, 3);
    
    printf("Input: list1 = ");
    printList(list13);
    printf(", list2 = ");
    printList(list14);
    printf("\n");
    
    struct ListNode* merged7 = mergeTwoLists(list13, list14);
    printf("Output: ");
    printList(merged7);
    printf("\n\n");
    
    freeList(merged7);
    
    return 0;
}

