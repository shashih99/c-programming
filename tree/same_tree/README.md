# Same Tree

## Problem Description

Given the roots of two binary trees `p` and `q`, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

## Examples

### Example 1
```
Input: p = [1,2,3], q = [1,2,3]
Output: true
```

### Example 2
```
Input: p = [1,2], q = [1,null,2]
Output: false
```

### Example 3
```
Input: p = [1,2,1], q = [1,1,2]
Output: false
```

## Constraints

- The number of nodes in both trees is in the range `[0, 100]`
- `-10^4 <= Node.val <= 10^4`

## Solution Approach

Use **recursive DFS** to compare both trees in parallel:

1. If both nodes are `NULL`, they match.
2. If only one is `NULL`, they do not match.
3. If values differ, they do not match.
4. Otherwise, recurse on left and right subtrees.

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
./same_tree
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
gdb build/Debug/same_tree
```

In GDB, you can:
- Set breakpoints: `break isSameTree` or `break same_tree.c:65`
- Run: `run`
- Step through: `next` or `step`
- Print variables: `print p->val` or `print q->val`
- Continue: `continue`
- Quit: `quit`

### Debug in VS Code / Cursor
1. Open `tree/same_tree/same_tree.c`
2. Set breakpoints where needed
3. Press `F5` or open **Run and Debug**
4. Select **Debug same_tree**
