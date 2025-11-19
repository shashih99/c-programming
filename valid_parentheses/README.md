# Valid Parentheses Problem

## Problem Description

Given a string `s` containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.

## Examples

### Example 1:
```
Input: s = "()"
Output: true
```

### Example 2:
```
Input: s = "()[]{}"
Output: true
```

### Example 3:
```
Input: s = "(]"
Output: false
```

### Example 4:
```
Input: s = "([])"
Output: true
```

### Example 5:
```
Input: s = "([)]"
Output: false
```

## Constraints

- `1 <= s.length <= 10^4`
- `s` consists of parentheses only `'()[]{}'`.

## Solution Approaches

### Method 1: Stack-Based Approach (Current Implementation)

**Algorithm:**
- Use a stack to keep track of opening brackets
- Iterate through each character in the string
- If it's an opening bracket `(`, `[`, or `{`, push it onto the stack
- If it's a closing bracket `)`, `]`, or `}`, check if:
  - The stack is empty (no matching opening bracket) → return false
  - The top of the stack matches the closing bracket type → pop from stack
  - The top doesn't match → return false
- After processing all characters, if the stack is empty, return true; otherwise false

**Time Complexity:** O(n) - where n is the length of the string
- Single pass through the string
- Stack operations (push/pop) are O(1)

**Space Complexity:** O(n) - worst case when all characters are opening brackets
- Stack can grow up to n elements

**Advantages:**
- Simple and intuitive
- Optimal time complexity
- Handles all edge cases correctly

**Disadvantages:**
- Requires additional memory for the stack
- Space complexity is O(n) in worst case

### Method 2: Counter-Based Approach (Limited Use)

**Note:** This approach only works for a single type of parentheses (e.g., only `()`). It cannot handle mixed types like `()[]{}` because it doesn't track the order of different bracket types.

**Algorithm (for single type only):**
- Use a counter for opening brackets
- Increment on `(`, decrement on `)`
- Counter must never go negative
- Counter must be zero at the end

**Time Complexity:** O(n)
**Space Complexity:** O(1)

**Limitation:** Cannot solve the general problem with multiple bracket types.

## Questions & Analysis

### 1. Why do we need a stack?
A stack is perfect for this problem because we need to match the most recently opened bracket with the current closing bracket. This follows the Last-In-First-Out (LIFO) principle.

### 2. What happens if we have only opening brackets?
Example: `"((("`
- All characters are pushed onto the stack
- No closing brackets to match
- Stack is not empty at the end
- Result: **false**

### 3. What happens if we have only closing brackets?
Example: `")))"`
- Stack is empty when we encounter the first `)`
- Cannot match closing bracket
- Result: **false** (immediately)

### 4. What happens with nested brackets?
Example: `"([{}])"`
- Process: `(` → `[` → `{` → `}` (matches `{`) → `]` (matches `[`) → `)` (matches `(`)
- Stack becomes empty
- Result: **true**

### 5. What happens with interleaved brackets?
Example: `"([)]"`
- Process: `(` → `[` → `)` (tries to match, but top is `[`, not `(`)
- Mismatch detected
- Result: **false**

### 6. Edge Cases to Consider:
- Empty string (should return true or false? - depends on problem definition)
- Single character (always false)
- All opening brackets
- All closing brackets
- Alternating brackets: `"()()()"`
- Deeply nested brackets
- Maximum length string (10^4 characters)

## Testing

### Building the Program

```bash
make
```

### Running Tests

```bash
make run
# or
./valid_parentheses
```

### Expected Output

```
Example 1:
Input: s = "()"
Output: true

Example 2:
Input: s = "()[]{}"
Output: true

Example 3:
Input: s = "(]"
Output: false

Example 4:
Input: s = "([])"
Output: true

Example 5:
Input: s = "([)]"
Output: false
```

### Manual Testing

You can modify the `main()` function to test additional cases:

```c
// Test case: Empty string
bool result = isValid("", 0);
// Expected: true (or false, depending on definition)

// Test case: Single character
bool result = isValid("(", 1);
// Expected: false

// Test case: All opening brackets
bool result = isValid("(((", 3);
// Expected: false

// Test case: All closing brackets
bool result = isValid(")))", 3);
// Expected: false

// Test case: Alternating valid brackets
bool result = isValid("()()()", 6);
// Expected: true

// Test case: Deeply nested
bool result = isValid("((((()))))", 10);
// Expected: true
```

### Test Cases Checklist

- [x] Basic case with single pair (Example 1)
- [x] Multiple types of brackets (Example 2)
- [x] Mismatched bracket types (Example 3)
- [x] Nested brackets (Example 4)
- [x] Interleaved brackets (Example 5)
- [ ] Empty string
- [ ] Single character
- [ ] All opening brackets
- [ ] All closing brackets
- [ ] Alternating valid brackets
- [ ] Deeply nested brackets
- [ ] Maximum length string

### Performance Testing

To test performance:

1. **Time the execution:**
```bash
time ./valid_parentheses
```

2. **Test with different string sizes:**
   - Small (10 characters): Fast
   - Medium (1000 characters): Fast
   - Large (10,000 characters): Still fast (O(n) algorithm)

3. **Memory profiling:**
```bash
valgrind --leak-check=full ./valid_parentheses
```

### Clean Build Artifacts

```bash
make clean
```

## Function Signature

```c
bool isValid(char* s, int sLength);
```

**Parameters:**
- `s`: Pointer to the input string
- `sLength`: Length of the string

**Returns:**
- `true` if the string is valid
- `false` otherwise

**Note:** The function assumes the string is null-terminated and `sLength` matches the actual string length.

## Implementation Details

### Stack Implementation

The current implementation uses an array-based stack:

```c
#define MAX_STACK_SIZE 10000  // Based on constraint: s.length <= 10^4

char stack[MAX_STACK_SIZE];
int top = -1;
```

**Stack Operations:**
- `push(char c)`: Add character to top of stack
- `pop()`: Remove and return top character
- `isEmpty()`: Check if stack is empty
- `peek()`: Return top character without removing

### Character Matching

The function uses a helper function to check if brackets match:

```c
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
```

## Memory Management

**Important:** The current implementation uses a fixed-size stack array. For strings up to 10^4 characters, this is sufficient. If you need a dynamic stack, you would need to:

1. Use `malloc()` to allocate stack memory
2. Reallocate if stack grows beyond initial size
3. Free memory when done

Example dynamic stack (not implemented):
```c
char* stack = malloc(sLength * sizeof(char));
// ... use stack ...
free(stack);
```

## Additional Resources

- [LeetCode Valid Parentheses Problem](https://leetcode.com/problems/valid-parentheses/)
- Stack data structure
- Time complexity analysis
- Space-time tradeoffs

