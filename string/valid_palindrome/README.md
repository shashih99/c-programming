# Valid Palindrome

## Problem Description

A phrase is a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

## Examples

### Example 1
```
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.
```

### Example 2
```
Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.
```

### Example 3
```
Input: s = " "
Output: true
Explanation: s is an empty string "" after removing non-alphanumeric characters.
Since an empty string reads the same forward and backward, it is a palindrome.
```

## Constraints

- `1 <= s.length <= 2 * 10^5`
- `s` consists only of printable ASCII characters.

## Solution Approach

### Algorithm

The solution uses **two pointers moving inward**, without building a cleaned copy of the string:

1. **Start at both ends**: `left = 0`, `right = strlen(s) - 1`.
2. **Skip junk**: Advance `left` and retreat `right` past any character that is not a letter or digit (`isalnum`).
3. **Compare**: Lowercase both characters (`tolower`) and compare. A mismatch means the string is not a palindrome.
4. **Move inward**: `left++`, `right--`, and repeat while `left < right`.

If the pointers meet without a mismatch, the string is a palindrome.

### Implementation Details

```c
bool isPalindrome(char* s) {
    int left = 0;
    int right = (int)strlen(s) - 1;

    while (left < right) {
        while (left < right && !isalnum((unsigned char)s[left])) left++;
        while (left < right && !isalnum((unsigned char)s[right])) right--;

        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

### Walkthrough (Example 2: `"race a car"`)

| left | right | s[left] | s[right] | Result |
|------|-------|---------|----------|--------|
| 0    | 9     | r       | r        | match  |
| 1    | 8     | a       | a        | match  |
| 2    | 7     | c       | c        | match  |
| 3    | 5     | e       | a        | **mismatch → false** (index 6 is a space, skipped) |

### Complexity Analysis

- **Time Complexity**: O(n) — each character is visited at most once by either pointer
- **Space Complexity**: O(1) — only two indices

## Alternative Approaches

### Clean Then Compare
- Build a new string with only lowercase alphanumerics, then check it against its reverse
- **Space**: O(n) for the cleaned copy — simpler but uses extra memory

**The two-pointer approach is optimal and avoids any allocation.**

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or
./valid_palindrome
```

### Debug build
```bash
make debug
make debug-run
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

The program checks each result against the expected value and prints PASS/FAIL:

1. **Example 1**: `"A man, a plan, a canal: Panama"` → `true`
2. **Example 2**: `"race a car"` → `false`
3. **Example 3**: `" "` → `true`
4. **Digit vs letter**: `"0P"` → `false`
5. **Only punctuation**: `".,!?"` → `true`
6. **Single char**: `"a"` → `true`
7. **Mixed case**: `"No 'x' in Nixon"` → `true`
8. **Digits**: `"12-3-21"` → `true`
9. **Near miss**: `"ab_a b"` → `false`

## Notes

- Digits are alphanumeric, so `"0P"` is **not** a palindrome — a common pitfall
- Characters are cast to `unsigned char` before calling `isalnum`/`tolower`, since passing a negative `char` to `<ctype.h>` functions is undefined behavior
- The `left < right` guard inside the skip loops prevents running past each other on strings like `" "`
