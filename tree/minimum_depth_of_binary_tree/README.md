# Minimum Depth of Binary Tree

## Problem Description

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

**Note:** A leaf is a node with no children.

## Examples

### Example 1
```
Input: root = [3,9,20,null,null,15,7]
Output: 2
```

### Example 2
```
Input: root = [2,null,3,null,4,null,5,null,6]
Output: 5
```

## Constraints

- The number of nodes in the tree is in the range `[0, 10^5]`
- `-1000 <= Node.val <= 1000`

## Solution Approach

Use **recursive DFS** to compute the shortest root-to-leaf path:

1. If the node is `NULL`, depth is `0`.
2. If the node is a leaf (no children), depth is `1`.
3. If only one child exists, recurse only on that child (a missing child is not a leaf).
4. If both children exist, take `1 + min(leftDepth, rightDepth)`.

### Complexity

- **Time Complexity**: `O(n)` where `n` is the number of nodes
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
./minimum_depth_of_binary_tree
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
gdb build/Debug/minimum_depth_of_binary_tree
```

In GDB, you can:
- Set breakpoints: `break minDepth` or `break minimum_depth_of_binary_tree.c:75`
- Run: `run`
- Step through: `next` or `step`
- Print variables: `print root->val` or `print leftDepth`
- Continue: `continue`
- Quit: `quit`

### Debug in VS Code / Cursor
1. Open `tree/minimum_depth_of_binary_tree/minimum_depth_of_binary_tree.c`
2. Set breakpoints where needed
3. Select **Debug current program** in **Run and Debug**
4. Press `F5` (runs `make debug`, then starts gdb on the generated binary)
