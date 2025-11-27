# Find First Occurrence Problem

## Problem Description

Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

**Constraints:**
- `1 <= haystack.length, needle.length <= 10^4`
- `haystack` and `needle` consist of only lowercase English characters.

## Examples

### Example 1:
```
Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6. The first occurrence is at index 0, so we return 0.
```

### Example 2:
```
Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.
```

## Solution Approach

### Algorithm:
1. Iterate through each possible starting position in `haystack`
2. For each position, check if `needle` matches starting from that position
3. Return the first matching index, or `-1` if not found

### Time Complexity:
- **O(n × m)** where `n` is the length of `haystack` and `m` is the length of `needle`
- In the worst case, we check every position in `haystack` and compare up to `m` characters for each position

### Space Complexity:
- **O(1)** - only using a few variables, no additional data structures

## Implementation Details

The solution uses a simple sliding window approach:
- For each starting position `i` in `haystack` (from 0 to `haystackLen - needleLen`)
- Check if `needle` matches the substring starting at position `i`
- If all characters match, return `i`
- If no match is found after checking all positions, return `-1`

### Edge Cases Handled:
1. **Empty needle**: Returns 0 (empty string is considered to be at index 0)
2. **Needle longer than haystack**: Returns -1 immediately
3. **Single character match**: Works correctly
4. **Multiple occurrences**: Returns the index of the first occurrence

## Building and Running

### Using Makefile:
```bash
# Build the executable
make

# Run the program
make run

# Clean build artifacts
make clean

# Rebuild everything
make rebuild
```

### Manual compilation:
```bash
gcc -Wall -Wextra -std=c11 -O2 find_first_occurrence.c -o find_first_occurrence
./find_first_occurrence
```

## Testing

The program includes comprehensive test cases:
- Example 1: Basic case with multiple occurrences
- Example 2: Case where needle is not found
- Additional tests for edge cases:
  - Needle at the beginning
  - Needle at the end
  - Needle in the middle
  - Single character match
  - Empty needle
  - Needle longer than haystack
  - Multiple occurrences

## Notes

- This problem is essentially implementing the `strstr()` function from the C standard library
- For production code, you might want to use the optimized `strstr()` function or implement more efficient algorithms like KMP (Knuth-Morris-Pratt) or Boyer-Moore for better performance on large strings
- The current implementation is straightforward and easy to understand, making it suitable for learning purposes

