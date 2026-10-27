# Path Sum

## Problem Description

Given the root of a binary tree and an integer `targetSum`, return `true` if the tree has a root-to-leaf path such that adding up all the values along the path equals `targetSum`.

A leaf is a node with no children.

## Examples

### Example 1
```
Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path 5 -> 4 -> 11 -> 2 sums to 22.
```

### Example 2
```
Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: Paths are (1 -> 2) = 3 and (1 -> 3) = 4; neither equals 5.
```

### Example 3
```
Input: root = [], targetSum = 0
Output: false
Explanation: The tree is empty, so there are no root-to-leaf paths.
```

## Constraints

- The number of nodes in the tree is in the range `[0, 5000]`
- `-1000 <= Node.val <= 1000`
- `-1000 <= targetSum <= 1000`

## Solution Approach

Use **recursive DFS**, subtracting each node's value from the remaining target:

1. If the node is `NULL`, return `false` (empty tree has no path).
2. If the node is a leaf, return whether `node->val == targetSum`.
3. Otherwise, recurse on left and right with `targetSum - node->val`; return true if either side succeeds.

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
./path_sum
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
gdb build/Debug/path_sum
```

In GDB, you can:
- Set breakpoints: `break hasPathSum` or `break path_sum.c:70`
- Run: `run`
- Step through: `next` or `step`
- Print variables: `print root->val` or `print remaining`
- Continue: `continue`
- Quit: `quit`

### Debug in VS Code / Cursor
1. Open `path_sum.c`
2. Set breakpoints where needed
3. Select **Debug current program** in **Run and Debug**
4. Press `F5` (runs `make debug`, then starts gdb on the generated binary)
