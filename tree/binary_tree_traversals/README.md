# Binary Tree Traversals

## Problem Description

Given the root of a binary tree, return the **inorder traversal** of its nodes' values.

Additionally, this implementation also includes:

- **Preorder traversal**
- **Postorder traversal**

## Examples

### Example 1
```
Input: root = [1,null,2,3]
Inorder Output: [1,3,2]
```

### Example 2
```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Inorder Output: [4,2,6,5,7,1,3,9,8]
```

### Example 3
```
Input: root = []
Inorder Output: []
```

### Example 4
```
Input: root = [1]
Inorder Output: [1]
```

## Constraints

- Number of nodes is in the range `[0, 100]`
- `-100 <= Node.val <= 100`

## Solution Approach

This solution uses **depth-first traversal (DFS)** with recursion.

- **Inorder**: Left -> Root -> Right
- **Preorder**: Root -> Left -> Right
- **Postorder**: Left -> Right -> Root

Each traversal visits every node exactly once.

### Complexity

- **Time Complexity**: `O(n)` for each traversal
- **Space Complexity**: `O(h)` recursion stack (`h` = tree height)

## Build and Run

### Build
```bash
make
```

### Run
```bash
make run
# or
./binary_tree_traversals
```

### Clean
```bash
make clean
```

### Rebuild
```bash
make rebuild
```
