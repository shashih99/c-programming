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
 * Inorder traversal: Left -> Root -> Right
 * Time Complexity: O(n)
 * Space Complexity: O(h) recursion stack
 */
void inorderTraversalHelper(struct TreeNode* root, int* result, int* returnSize) {
    if (root == NULL) {
        return;
    }
    inorderTraversalHelper(root->left, result, returnSize);
    result[(*returnSize)++] = root->val;
    inorderTraversalHelper(root->right, result, returnSize);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * 100);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 0;
    inorderTraversalHelper(root, result, returnSize);
    return result;
}

/**
 * Preorder traversal: Root -> Left -> Right
 */
void preorderTraversalHelper(struct TreeNode* root, int* result, int* returnSize) {
    if (root == NULL) {
        return;
    }
    result[(*returnSize)++] = root->val;
    preorderTraversalHelper(root->left, result, returnSize);
    preorderTraversalHelper(root->right, result, returnSize);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * 100);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 0;
    preorderTraversalHelper(root, result, returnSize);
    return result;
}

/**
 * Postorder traversal: Left -> Right -> Root
 */
void postorderTraversalHelper(struct TreeNode* root, int* result, int* returnSize) {
    if (root == NULL) {
        return;
    }
    postorderTraversalHelper(root->left, result, returnSize);
    postorderTraversalHelper(root->right, result, returnSize);
    result[(*returnSize)++] = root->val;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * 100);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 0;
    postorderTraversalHelper(root, result, returnSize);
    return result;
}

/**
 * Iterative postorder traversal (LeetCode 145 follow-up): Left -> Right -> Root
 *
 * Uses one explicit stack plus a `lastVisited` pointer:
 * - Walk left as far as possible, pushing nodes.
 * - Peek the top. If it has a right child we haven't visited yet, go right.
 * - Otherwise both subtrees are done: emit the node, pop it, mark it visited.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(h) for the stack
 */
int* postorderTraversalIterative(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(sizeof(int) * 100);
    struct TreeNode** stack = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 100);
    *returnSize = 0;
    if (result == NULL || stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(result);
        free(stack);
        return NULL;
    }

    int top = -1;
    struct TreeNode* current = root;
    struct TreeNode* lastVisited = NULL;

    while (current != NULL || top >= 0) {
        if (current != NULL) {
            stack[++top] = current;
            current = current->left;
        } else {
            struct TreeNode* peek = stack[top];
            if (peek->right != NULL && peek->right != lastVisited) {
                current = peek->right;
            } else {
                result[(*returnSize)++] = peek->val;
                lastVisited = peek;
                top--;
            }
        }
    }

    free(stack);
    return result;
}

/**
 * Helper function to print an integer array.
 */
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(",");
        }
    }
    printf("]");
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
 * Run and print all three traversals for one tree.
 */
void runTraversals(struct TreeNode* root) {
    int inorderSize = 0;
    int preorderSize = 0;
    int postorderSize = 0;
    int postorderIterSize = 0;

    int* inorder = inorderTraversal(root, &inorderSize);
    int* preorder = preorderTraversal(root, &preorderSize);
    int* postorder = postorderTraversal(root, &postorderSize);
    int* postorderIter = postorderTraversalIterative(root, &postorderIterSize);

    printf("Inorder Output:   ");
    printArray(inorder, inorderSize);
    printf("\n");

    printf("Preorder Output:  ");
    printArray(preorder, preorderSize);
    printf("\n");

    printf("Postorder Output: ");
    printArray(postorder, postorderSize);
    printf("\n");

    printf("Postorder (iter): ");
    printArray(postorderIter, postorderIterSize);
    printf("\n");

    free(inorder);
    free(preorder);
    free(postorder);
    free(postorderIter);
}

int main() {
    printf("Binary Tree Traversals (Inorder, Preorder, Postorder)\n");
    printf("=====================================================\n\n");

    /* Example 1: root = [1,null,2,3] */
    printf("Example 1:\n");
    printf("Input: root = [1,null,2,3]\n");
    int values1[] = {1, 0, 2, 0, 0, 3, 0};
    bool nulls1[] = {false, true, false, true, true, false, true};
    struct TreeNode* tree1 = buildTreeFromLevelOrder(values1, nulls1, 7, 0);
    runTraversals(tree1);
    printf("Expected Inorder: [1,3,2]\n");
    printf("Expected Postorder: [3,2,1]\n\n");
    freeTree(tree1);

    /* Example 2: root = [1,2,3,4,5,null,8,null,null,6,7,9] */
    printf("Example 2:\n");
    printf("Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]\n");
    /* Build Example 2 manually because the input uses compact level-order notation. */
    struct TreeNode* tree2 = createNode(1);
    tree2->left = createNode(2);
    tree2->right = createNode(3);
    tree2->left->left = createNode(4);
    tree2->left->right = createNode(5);
    tree2->left->right->left = createNode(6);
    tree2->left->right->right = createNode(7);
    tree2->right->right = createNode(8);
    tree2->right->right->left = createNode(9);
    runTraversals(tree2);
    printf("Expected Inorder: [4,2,6,5,7,1,3,9,8]\n");
    printf("Expected Postorder: [4,6,7,5,2,9,8,3,1]\n\n");
    freeTree(tree2);

    /* Example 3: root = [] */
    printf("Example 3:\n");
    printf("Input: root = []\n");
    struct TreeNode* tree3 = NULL;
    runTraversals(tree3);
    printf("Expected Inorder: []\n");
    printf("Expected Postorder: []\n\n");

    /* Example 4: root = [1] */
    printf("Example 4:\n");
    printf("Input: root = [1]\n");
    int values4[] = {1};
    bool nulls4[] = {false};
    struct TreeNode* tree4 = buildTreeFromLevelOrder(values4, nulls4, 1, 0);
    runTraversals(tree4);
    printf("Expected Inorder: [1]\n");
    printf("Expected Postorder: [1]\n\n");
    freeTree(tree4);

    return 0;
}
