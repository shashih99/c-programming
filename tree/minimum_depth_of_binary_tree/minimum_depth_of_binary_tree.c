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
 * Find the minimum depth of a binary tree.
 *
 * Minimum depth is the number of nodes along the shortest path from the
 * root down to the nearest leaf node.
 *
 * Important: if a node has only one child, we must continue down that
 * child. A missing child is not a leaf.
 *
 * Time Complexity: O(n) where n is the number of nodes
 * Space Complexity: O(h) recursion stack (h = tree height)
 */
int minDepth(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    /* Leaf node */
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    /* Only right subtree exists */
    if (root->left == NULL) {
        return 1 + minDepth(root->right);
    }

    /* Only left subtree exists */
    if (root->right == NULL) {
        return 1 + minDepth(root->left);
    }

    int leftDepth = minDepth(root->left);
    int rightDepth = minDepth(root->right);
    return 1 + (leftDepth < rightDepth ? leftDepth : rightDepth);
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
void runTest(const char* label, struct TreeNode* root, int expected) {
    int result = minDepth(root);
    printf("%s\n", label);
    printf("Output: %d\n", result);
    printf("Expected: %d\n", expected);
    printf("%s\n\n", result == expected ? "PASS" : "FAIL");
}

int main() {
    printf("Minimum Depth of Binary Tree (LeetCode 111)\n");
    printf("=============================================\n\n");

    /* Example 1: root = [3,9,20,null,null,15,7] */
    int values1[] = {3, 9, 20, 0, 0, 15, 7};
    bool nulls1[] = {false, false, false, true, true, false, false};
    struct TreeNode* tree1 = buildTreeFromLevelOrder(values1, nulls1, 7, 0);
    runTest("Example 1:\nInput: root = [3,9,20,null,null,15,7]", tree1, 2);
    freeTree(tree1);

    /* Example 2: root = [2,null,3,null,4,null,5,null,6]
     * Compact level-order; build manually. */
    struct TreeNode* tree2 = createNode(2);
    tree2->right = createNode(3);
    tree2->right->right = createNode(4);
    tree2->right->right->right = createNode(5);
    tree2->right->right->right->right = createNode(6);
    runTest("Example 2:\nInput: root = [2,null,3,null,4,null,5,null,6]", tree2, 5);
    freeTree(tree2);

    /* Edge case: empty tree */
    runTest("Edge case:\nInput: root = []", NULL, 0);

    /* Edge case: single node */
    struct TreeNode* tree4 = createNode(1);
    runTest("Edge case:\nInput: root = [1]", tree4, 1);
    freeTree(tree4);

    /* Extra: left-skewed path is shorter */
    /* root = [1,2,3,4] -> min depth is 2 (1->3) */
    int values5[] = {1, 2, 3, 4};
    bool nulls5[] = {false, false, false, false};
    struct TreeNode* tree5 = buildTreeFromLevelOrder(values5, nulls5, 4, 0);
    runTest("Extra:\nInput: root = [1,2,3,4]", tree5, 2);
    freeTree(tree5);

    return 0;
}
