# Longest Common Prefix

## Problem Statement

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

### Examples

**Example 1:**
- Input: `strs = ["flower","flow","flight"]`
- Output: `"fl"`

**Example 2:**
- Input: `strs = ["dog","racecar","car"]`
- Output: `""`
- Explanation: There is no common prefix among the input strings.

### Constraints

- `1 <= strs.length <= 200`
- `0 <= strs[i].length <= 200`
- `strs[i]` consists of only lowercase English letters if it is non-empty

## Solution Approach

### Horizontal Scanning
This solution uses the **horizontal scanning** approach:

1. **Find the minimum length**: Determine the shortest string length to avoid going out of bounds
2. **Compare character by character**: For each position (0 to minLen), check if all strings have the same character at that position
3. **Stop at first mismatch**: If any string has a different character at a position, return the prefix found so far
4. **Return the common prefix**: If all positions match, return the entire minimum length prefix

### Algorithm Details

```
longestCommonPrefix(strs, strsSize):
    1. Find the minimum length among all strings
    2. For each position i from 0 to minLen:
        a. Get the character at position i from the first string
        b. Check if this character exists at position i in all other strings
        c. If any mismatch found, return prefix[0:i]
    3. If all positions match, return the entire minimum length prefix
```

### Complexity Analysis

- **Time Complexity**: O(m × n)
  - m = length of the shortest string
  - n = number of strings
  - We potentially compare each character in the shortest string with all other strings

- **Space Complexity**: O(m)
  - We allocate memory for the result string (at most the length of the shortest string)

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

## Test Cases

The program includes the following test cases:

1. **Example 1**: `["flower","flow","flight"]` → `"fl"`
2. **Example 2**: `["dog","racecar","car"]` → `""`
3. **Single string**: `["hello"]` → `"hello"`
4. **All identical strings**: `["abc","abc","abc"]` → `"abc"`
5. **Empty string in array**: `["","ab","cd"]` → `""`
6. **Long common prefix**: `["interspecies","interstellar","interstate"]` → `"inters"`
7. **No common prefix**: `["ab","ba"]` → `""`

## Key Points

- The function allocates memory for the result which must be freed by the caller
- The algorithm handles edge cases like single strings, empty strings, and arrays with no common prefix
- The approach is efficient with linear time complexity relative to the total number of characters examined
