#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Helper function to create a new tree node.
 */
struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Build a binary tree from level-order arrays.
 *
 * values[i] holds node value at index i.
 * isNull[i] == true means the entry is null.
 *
 * For an index i:
 * left child index  = 2*i + 1
 * right child index = 2*i + 2
 */
struct TreeNode* buildTreeFromLevelOrder(const int* values, const bool* isNull, int size, int index) {
    if (index >= size || isNull[index]) {
        return NULL;
    }

    struct TreeNode* root = createNode(values[index]);
    if (root == NULL) {
        return NULL;
    }

    root->left = buildTreeFromLevelOrder(values, isNull, size, 2 * index + 1);
    root->right = buildTreeFromLevelOrder(values, isNull, size, 2 * index + 2);
    return root;
}

/**
 * Check if two binary trees are the same.
 *
 * Two trees are the same if they are structurally identical and every
 * corresponding node has the same value.
 *
 * Time Complexity: O(n) where n is the number of nodes
 * Space Complexity: O(h) recursion stack (h = tree height)
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL) {
        return true;
    }
    if (p == NULL || q == NULL) {
        return false;
    }
    if (p->val != q->val) {
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

/**
 * Helper function to free all nodes in a tree.
 */
void freeTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/**
 * Run one test case and print the result.
 */
void runTest(const char* label, struct TreeNode* p, struct TreeNode* q, bool expected) {
    bool result = isSameTree(p, q);
    printf("%s\n", label);
    printf("Output: %s\n", result ? "true" : "false");
    printf("Expected: %s\n", expected ? "true" : "false");
    printf("%s\n\n", result == expected ? "PASS" : "FAIL");
}

int main() {
    printf("Same Tree (LeetCode 100)\n");
    printf("==========================\n\n");

    /* Example 1: p = [1,2,3], q = [1,2,3] */
    int values1[] = {1, 2, 3};
    bool nulls1[] = {false, false, false};
    struct TreeNode* p1 = buildTreeFromLevelOrder(values1, nulls1, 3, 0);
    struct TreeNode* q1 = buildTreeFromLevelOrder(values1, nulls1, 3, 0);
    runTest("Example 1:\nInput: p = [1,2,3], q = [1,2,3]", p1, q1, true);
    freeTree(p1);
    freeTree(q1);

    /* Example 2: p = [1,2], q = [1,null,2] */
    int valuesP2[] = {1, 2};
    bool nullsP2[] = {false, false};
    int valuesQ2[] = {1, 0, 2};
    bool nullsQ2[] = {false, true, false};
    struct TreeNode* p2 = buildTreeFromLevelOrder(valuesP2, nullsP2, 2, 0);
    struct TreeNode* q2 = buildTreeFromLevelOrder(valuesQ2, nullsQ2, 3, 0);
    runTest("Example 2:\nInput: p = [1,2], q = [1,null,2]", p2, q2, false);
    freeTree(p2);
    freeTree(q2);

    /* Example 3: p = [1,2,1], q = [1,1,2] */
    int valuesP3[] = {1, 2, 1};
    bool nullsP3[] = {false, false, false};
    int valuesQ3[] = {1, 1, 2};
    bool nullsQ3[] = {false, false, false};
    struct TreeNode* p3 = buildTreeFromLevelOrder(valuesP3, nullsP3, 3, 0);
    struct TreeNode* q3 = buildTreeFromLevelOrder(valuesQ3, nullsQ3, 3, 0);
    runTest("Example 3:\nInput: p = [1,2,1], q = [1,1,2]", p3, q3, false);
    freeTree(p3);
    freeTree(q3);

    /* Edge case: both empty */
    runTest("Edge case:\nInput: p = [], q = []", NULL, NULL, true);

    return 0;
}
