# Length of Last Word

## Problem Description

Given a string `s` consisting of words and spaces, return the length of the last word in the string.

A word is a maximal substring consisting of non-space characters only.

## Examples

### Example 1
```
Input: s = "Hello World"
Output: 5
Explanation: The last word is "World" with length 5.
```

### Example 2
```
Input: s = "   fly me   to   the moon  "
Output: 4
Explanation: The last word is "moon" with length 4.
```

### Example 3
```
Input: s = "luffy is still joyboy"
Output: 6
Explanation: The last word is "joyboy" with length 6.
```

## Constraints

- `1 <= s.length <= 10^4`
- `s` consists of only English letters and spaces `' '`.
- There will be at least one word in `s`.

## Solution Approach

### Algorithm

The solution uses a **reverse traversal** approach:

1. **Start from the end**: Begin at the last character of the string
2. **Skip trailing spaces**: Move backwards while encountering spaces
3. **Count the last word**: Once we find a non-space character, count all consecutive non-space characters until we hit a space or the beginning of the string

### Implementation Details

```c
int lengthOfLastWord(char *s) {
    int length = 0;
    int i = strlen(s) - 1;
    
    // Skip trailing spaces
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    
    // Count characters of the last word
    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }
    
    return length;
}
```

### Complexity Analysis

- **Time Complexity**: O(n) in the worst case, where n is the length of the string. However, the algorithm is often more efficient because:
  - If there are trailing spaces, we skip them quickly
  - We only traverse backwards until we find the last word
  - Best case: O(1) if the last word is at the end with no trailing spaces
  - Average case: O(k) where k is the length of the last word plus trailing spaces

- **Space Complexity**: O(1) - only using a few integer variables, no additional data structures

### Why This Approach?

1. **Efficient**: We don't need to process the entire string. Starting from the end allows us to stop as soon as we've counted the last word.

2. **Handles edge cases**: 
   - Trailing spaces are automatically skipped
   - Works with single words
   - Works with strings that have multiple spaces between words

3. **Simple and readable**: The logic is straightforward and easy to understand.

## Alternative Approaches

### Approach 2: Forward Traversal with State Tracking
- Traverse from the beginning, track the current word length
- Reset when encountering a space
- More complex and requires processing the entire string

### Approach 3: Using String Functions
- Use `strtok` or similar functions to split words
- Less efficient due to string manipulation overhead

**The reverse traversal approach is optimal for this problem.**

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./length_of_last_word
```

### Clean build artifacts
```bash
make clean
```

### Rebuild everything
```bash
make rebuild
```

## Test Cases

The program includes the following test cases:

1. **Example 1**: `"Hello World"` → 5
2. **Example 2**: `"   fly me   to   the moon  "` → 4
3. **Example 3**: `"luffy is still joyboy"` → 6
4. **Single word**: `"Hello"` → 5
5. **Single character**: `"a"` → 1
6. **Trailing spaces**: `"test    "` → 4

## Notes

- The solution handles all edge cases mentioned in the constraints
- The algorithm is optimal in terms of both time and space complexity
- No additional memory allocation is required

