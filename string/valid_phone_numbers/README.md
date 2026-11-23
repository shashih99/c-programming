# Valid Phone Numbers

## Problem Description

Given a text file `file.txt` that contains a list of phone numbers (one per line), write a one-liner bash script to print all valid phone numbers.

You may assume that a valid phone number must appear in one of the following two formats: `(xxx) xxx-xxxx` or `xxx-xxx-xxxx`. (`x` means a digit)

You may also assume each line in the text file must not contain leading or trailing white spaces.

## Example

Assume that `file.txt` has the following content:
```
987-123-4567
123 456 7890
(123) 456-7890
```

Your script should output the following valid phone numbers:
```
987-123-4567
(123) 456-7890
```

## Solution Approach

LeetCode runs this as a **Bash** problem, so the submitted answer is [solution.sh](solution.sh). The C program implements the same check by hand to show what the regex is doing.

### Bash (LeetCode submission)

```bash
grep -E '^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$' file.txt
```

- `^` and `$` anchor the match to the **whole line**, so `123-456-78901` or a trailing space are rejected
- `([0-9]{3}-|\([0-9]{3}\) )` is the only part that differs between the formats: `xxx-` or `(xxx) `
- `[0-9]{3}-[0-9]{4}` is the shared tail `xxx-xxxx`

### C (template matching)

1. **Describe each format as a template**: `"ddd-ddd-dddd"` and `"(ddd) ddd-dddd"`, where `d` means "any digit" and every other character must match literally.
2. **Match**: walk the line and the template together; fail on a non-digit where `d` is expected, on a literal mismatch, or if the lengths differ.
3. **Filter the file**: read with `getline`, strip the newline, print lines matching either template.

```c
static bool matchesFormat(const char* s, const char* fmt) {
    for (; *fmt; s++, fmt++) {
        if (*s == '\0') return false;
        if (*fmt == 'd') {
            if (!isdigit((unsigned char)*s)) return false;
        } else if (*s != *fmt) {
            return false;
        }
    }
    return *s == '\0';
}
```

### Complexity Analysis

- **Time Complexity**: O(N) — N is the total number of characters in the file; each line is compared against two fixed-length templates
- **Space Complexity**: O(L) — L is the longest line (the `getline` buffer)

## Alternative Approaches

### `sed` / `awk`
```bash
sed -n -E '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/p' file.txt
awk '/^([0-9]{3}-|\([0-9]{3}\) )[0-9]{3}-[0-9]{4}$/' file.txt
```

### POSIX `<regex.h>` in C
- `regcomp` the same ERE and `regexec` each line
- Shorter, but hides the logic; the template approach is O(1) extra space and needs no regex engine

## Building and Running

### Build the program
```bash
make
```

### Run the program
```bash
make run
# or, with a different input file
./valid_phone_numbers other.txt
```

### Run the Bash solution
```bash
./solution.sh            # reads file.txt
./solution.sh other.txt
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

## Test Cases

The program first prints the valid numbers from `file.txt`, then checks single lines and prints PASS/FAIL:

1. **Dashes**: `987-123-4567` → valid
2. **Spaces**: `123 456 7890` → invalid
3. **Parentheses**: `(123) 456-7890` → valid
4. **Missing space after `)`**: `(123)456-7890` → invalid
5. **Mixed formats**: `(123)-456-7890` → invalid
6. **Too short**: `123-45-6789` → invalid
7. **Too long**: `123-456-78901` → invalid
8. **Trailing space**: `123-456-7890 ` → invalid
9. **Leading space**: ` 123-456-7890` → invalid
10. **Letter instead of digit**: `12a-456-7890` → invalid
11. **No separators**: `1234567890` → invalid
12. **Empty line**: `""` → invalid

## Notes

- Forgetting the `^…$` anchors is the most common mistake: `grep` would then accept `0123-456-7890` because it *contains* a valid number
- In ERE, `(` groups and `\(` is a literal parenthesis — the reverse of basic `grep` (BRE)
- `[0-9]` is safer than `\d`, which `grep -E` does not support
