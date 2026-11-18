# Binary Tree Traversals

## Problem Description

Given the root of a binary tree, return the traversal of its nodes' values.

This implementation covers:

- **Inorder traversal** (LeetCode 94)
- **Preorder traversal**
- **Postorder traversal** (LeetCode 145): recursive and iterative

## Examples

### Example 1
```
Input: root = [1,null,2,3]
Inorder Output:   [1,3,2]
Postorder Output: [3,2,1]
```

### Example 2
```
Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
Inorder Output:   [4,2,6,5,7,1,3,9,8]
Postorder Output: [4,6,7,5,2,9,8,3,1]
```

### Example 3
```
Input: root = []
Inorder Output:   []
Postorder Output: []
```

### Example 4
```
Input: root = [1]
Inorder Output:   [1]
Postorder Output: [1]
```

## Constraints

- Number of nodes is in the range `[0, 100]`
- `-100 <= Node.val <= 100`

## Solution Approach

This solution uses **depth-first traversal (DFS)**. All three traversals have a recursive version, and postorder also has an iterative one.

- **Inorder**: Left -> Root -> Right
- **Preorder**: Root -> Left -> Right
- **Postorder**: Left -> Right -> Root

Each traversal visits every node exactly once.

### Iterative Postorder (LeetCode 145 follow-up)

`postorderTraversalIterative` avoids recursion by using an explicit stack and a
`lastVisited` pointer:

1. Go left as far as possible, pushing each node onto the stack.
2. Look at the node on top of the stack. If it has a right child that hasn't
   been visited yet, go there next.
3. Otherwise both subtrees are done: add the node to the output, pop it, and
   set `lastVisited` to it.

`lastVisited` tells you whether you're coming back to a node from its left
subtree (right side still pending) or from its right subtree (node is ready to
be added).

Another common approach is a modified preorder (Root -> Right -> Left) followed
by reversing the result. It's simpler, but it doesn't visit nodes in true
postorder.

### Complexity

- **Time Complexity**: `O(n)` for each traversal
- **Space Complexity**: `O(h)` (`h` = tree height), for the recursion stack in
  the recursive versions and the explicit stack in the iterative version

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

### Debug Build
```bash
make debug
```

This creates a debug build with:
- Debugging symbols (`-g`)
- No optimization (`-O0`) for easier debugging
- Debug flag (`-DDEBUG`) if needed

### Run Debug Build
```bash
make debug-run
```

### Debug with GDB
```bash
make debug
gdb build/Debug/binary_tree_traversals
```

In GDB, you can:
- Set breakpoints: `break inorderTraversal` or `break binary_tree_traversals.c:65`
- Run: `run`
- Step through: `next` or `step`
- Print variables: `print root->val` or `print *returnSize`
- Continue: `continue`
- Quit: `quit`

### Debug in VS Code / Cursor
1. Open `tree/binary_tree_traversals/binary_tree_traversals.c`
2. Set breakpoints where needed
3. Press `F5` or open **Run and Debug**
4. Select **Debug binary_tree_traversals**
