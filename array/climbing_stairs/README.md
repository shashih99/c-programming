# Climbing Stairs

## Problem Statement

You are climbing a staircase. It takes `n` steps to reach the top.

Each time you can either climb **1** or **2** steps. In how many distinct ways can you climb to the top?

### Examples

**Example 1:**
- Input: `n = 2`
- Output: `2`
- Explanation: There are two ways to climb to the top.
  1. 1 step + 1 step
  2. 2 steps

**Example 2:**
- Input: `n = 3`
- Output: `3`
- Explanation: There are three ways to climb to the top.
  1. 1 step + 1 step + 1 step
  2. 1 step + 2 steps
  3. 2 steps + 1 step

### Constraints

- `1 <= n <= 45`

## Solution Approach

### Method: Iterative Dynamic Programming

This problem follows the **Fibonacci sequence pattern**. The key insight is:
- To reach step `n`, you can come from step `n-1` (taking 1 step) or step `n-2` (taking 2 steps)
- Therefore: `ways(n) = ways(n-1) + ways(n-2)`
- Base cases: `ways(1) = 1`, `ways(2) = 2`

Instead of using recursion (which would be O(2^n) time), we use an **iterative approach** with constant space.

**Algorithm:**
1. Handle base cases: if `n <= 2`, return `n`
2. Initialize two variables:
   - `prev2 = 1` (ways to reach step 1)
   - `prev1 = 2` (ways to reach step 2)
3. Iterate from `i = 3` to `n`:
   - `current = prev1 + prev2`
   - Update `prev2 = prev1` and `prev1 = current`
4. Return `prev1`

**Time Complexity:** O(n)
- Single pass through steps 3 to n
- Each step requires constant time operations

**Space Complexity:** O(1)
- Only using two variables (`prev2` and `prev1`) regardless of input size
- No additional data structures needed

## Visual Graphics

### 1. Staircase Visualization

#### For n = 2:
```
    Top
     │
    ┌─┘  Path 1: 1 step → 1 step
   ┌─┘   Path 2: 2 steps
  ┌─┘
 Start
```

**Paths:**
- Path 1: Start → Step 1 → Top (1+1)
- Path 2: Start → Top (2)

**Total: 2 ways**

#### For n = 3:
```
      Top
       │
      ┌─┘  Path 1: 1 step → 1 step → 1 step
     ┌─┘   Path 2: 1 step → 2 steps
    ┌─┘    Path 3: 2 steps → 1 step
   ┌─┘
  ┌─┘
 Start
```

**Paths:**
- Path 1: Start → Step 1 → Step 2 → Top (1+1+1)
- Path 2: Start → Step 1 → Top (1+2)
- Path 3: Start → Step 2 → Top (2+1)

**Total: 3 ways**

### 2. Recursive Tree Structure

The recursive relationship can be visualized as a tree:

```
                    ways(5)
                   /        \
            ways(4)          ways(3)
           /      \         /      \
      ways(3)  ways(2)  ways(2)  ways(1)
      /    \      |       |        |
  ways(2) ways(1) 2       2        1
    |       |
    2       1
```

**Note:** This recursive approach has exponential time complexity O(2^n) because many subproblems are computed multiple times. That's why we use dynamic programming!

### 3. DP Table Filling Process

The iterative DP approach builds the solution bottom-up:

| Step | Ways | Calculation | Explanation |
|------|------|-------------|-------------|
| 1    | 1    | Base case   | Only one way: take 1 step |
| 2    | 2    | Base case   | Two ways: (1+1) or (2) |
| 3    | 3    | 2 + 1 = 3   | From step 1 (2 ways) + From step 2 (1 way) |
| 4    | 5    | 3 + 2 = 5   | From step 2 (3 ways) + From step 3 (2 ways) |
| 5    | 8    | 5 + 3 = 8   | From step 3 (5 ways) + From step 4 (3 ways) |
| 6    | 13   | 8 + 5 = 13  | From step 4 (8 ways) + From step 5 (5 ways) |

**Pattern:** This is the Fibonacci sequence! (1, 2, 3, 5, 8, 13, ...)

### 4. Step-by-Step Walkthrough

#### Example 1: n = 2

```
Initialization:
  prev2 = 1  (ways to reach step 1)
  prev1 = 2  (ways to reach step 2)

Since n = 2, we return prev1 = 2 ✓
```

#### Example 2: n = 3

```
Initialization:
  prev2 = 1  (ways to reach step 1)
  prev1 = 2  (ways to reach step 2)

Iteration i = 3:
  current = prev1 + prev2 = 2 + 1 = 3
  prev2 = prev1 = 2
  prev1 = current = 3

Return prev1 = 3 ✓
```

#### Example: n = 5

```
Initialization:
  prev2 = 1  (ways to reach step 1)
  prev1 = 2  (ways to reach step 2)

Iteration i = 3:
  current = prev1 + prev2 = 2 + 1 = 3
  prev2 = prev1 = 2
  prev1 = current = 3

Iteration i = 4:
  current = prev1 + prev2 = 3 + 2 = 5
  prev2 = prev1 = 3
  prev1 = current = 5

Iteration i = 5:
  current = prev1 + prev2 = 5 + 3 = 8
  prev2 = prev1 = 5
  prev1 = current = 8

Return prev1 = 8 ✓
```

## Building and Running

### Compile
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
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
gdb build/Debug/climbing_stairs
```

In GDB, you can:
- Set breakpoints: `break climbStairs` or `break climbing_stairs.c:45`
- Run: `run`
- Step through: `next` or `step`
- Print variables: `print prev1` or `print prev2`
- Continue: `continue`
- Quit: `quit`

## Test Cases

The program includes the following test cases:

1. **Example 1**: `n = 2` → `2`
2. **Example 2**: `n = 3` → `3`
3. **Edge case**: `n = 1` → `1`
4. **Test case**: `n = 4` → `5`
5. **Test case**: `n = 5` → `8`
6. **Test case**: `n = 10` → `89`

## Key Points

- The problem follows the Fibonacci sequence pattern
- Iterative DP approach avoids exponential time complexity of recursion
- Space-optimized solution uses only O(1) extra space
- Base cases are handled explicitly (n = 1 and n = 2)
- The solution is optimal with O(n) time and O(1) space complexity

## Why This Works: Mathematical Insight

The recurrence relation `ways(n) = ways(n-1) + ways(n-2)` comes from the fact that:
- To reach step `n`, you must be at step `n-1` (then take 1 step) OR at step `n-2` (then take 2 steps)
- These are the only two ways to reach step `n` (since you can only take 1 or 2 steps at a time)
- Therefore, the total ways = ways from step `n-1` + ways from step `n-2`

This is exactly the Fibonacci recurrence relation, shifted by one position:
- Fibonacci: F(0)=0, F(1)=1, F(2)=1, F(3)=2, F(4)=3, F(5)=5, ...
- Climbing Stairs: ways(1)=1, ways(2)=2, ways(3)=3, ways(4)=5, ways(5)=8, ...

Notice: `ways(n) = F(n+1)` where F is the Fibonacci sequence!

## Function Signature

```c
int climbStairs(int n);
```

**Parameters:**
- `n`: Number of steps to reach the top (1 <= n <= 45)

**Returns:**
- `int`: Number of distinct ways to climb to the top

## Additional Resources

- [LeetCode Climbing Stairs Problem](https://leetcode.com/problems/climbing-stairs/)
- Dynamic Programming concepts
- Fibonacci sequence
- Time and space complexity analysis
