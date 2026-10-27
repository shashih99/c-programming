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
 * Return true if the tree has a root-to-leaf path whose values sum to targetSum.
 *
 * DFS: subtract the current node value from the remaining sum. At a leaf,
 * check whether the remaining sum equals the leaf value.
 *
 * Time Complexity: O(n) where n is the number of nodes
 * Space Complexity: O(h) recursion stack (h = tree height)
 */
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return false;
    }

    /* Leaf: path is valid only if remaining sum equals this node's value */
    if (root->left == NULL && root->right == NULL) {
        return root->val == targetSum;
    }

    int remaining = targetSum - root->val;
    return hasPathSum(root->left, remaining) || hasPathSum(root->right, remaining);
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
void runTest(const char* label, struct TreeNode* root, int targetSum, bool expected) {
    bool result = hasPathSum(root, targetSum);
    printf("%s\n", label);
    printf("Output: %s\n", result ? "true" : "false");
    printf("Expected: %s\n", expected ? "true" : "false");
    printf("%s\n\n", result == expected ? "PASS" : "FAIL");
}

int main() {
    printf("Path Sum (LeetCode 112)\n");
    printf("=======================\n\n");

    /* Example 1: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
     * Built manually because LeetCode's compact level-order has holes that
     * do not map cleanly to the 2*i+1 / 2*i+2 index formula. */
    struct TreeNode* tree1 = createNode(5);
    tree1->left = createNode(4);
    tree1->right = createNode(8);
    tree1->left->left = createNode(11);
    tree1->right->left = createNode(13);
    tree1->right->right = createNode(4);
    tree1->left->left->left = createNode(7);
    tree1->left->left->right = createNode(2);
    tree1->right->right->right = createNode(1);
    runTest(
        "Example 1:\nInput: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22",
        tree1, 22, true);
    freeTree(tree1);

    /* Example 2: root = [1,2,3], targetSum = 5 */
    int values2[] = {1, 2, 3};
    bool nulls2[] = {false, false, false};
    struct TreeNode* tree2 = buildTreeFromLevelOrder(values2, nulls2, 3, 0);
    runTest("Example 2:\nInput: root = [1,2,3], targetSum = 5", tree2, 5, false);
    freeTree(tree2);

    /* Example 3: empty tree */
    runTest("Example 3:\nInput: root = [], targetSum = 0", NULL, 0, false);

    /* Edge case: single node matching target */
    struct TreeNode* tree4 = createNode(1);
    runTest("Edge case:\nInput: root = [1], targetSum = 1", tree4, 1, true);
    freeTree(tree4);

    /* Edge case: single node not matching target */
    struct TreeNode* tree5 = createNode(1);
    runTest("Edge case:\nInput: root = [1], targetSum = 0", tree5, 0, false);
    freeTree(tree5);

    return 0;
}
