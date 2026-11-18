# Read N Characters Given Read4 (LeetCode 157)

## Problem Statement

You have a file you can only read through a given API:

```c
int read4(char *buf4);
```

`read4` reads up to **4** consecutive characters from the file into `buf4`
and returns how many it actually read (0–4). It keeps its own file pointer,
so each call continues where the last one stopped. A return value below 4
means the end of the file was reached.

Implement:

```c
int read(char *buf, int n);
```

It reads up to `n` characters into `buf` and returns how many it read.
On LeetCode, `read` is called **only once** per test case. The follow-up
problem 158 allows multiple calls.

### Examples

| file           | n  | output | buf             |
|----------------|----|--------|-----------------|
| `"abc"`        | 4  | 3      | `"abc"`         |
| `"abcde"`      | 5  | 5      | `"abcde"`       |
| `"abcdABCD1234"` | 12 | 12   | `"abcdABCD1234"`|
| `"leetcode"`   | 5  | 5      | `"leetc"`       |

### Constraints

- `1 <= file.length <= 500`
- `1 <= n <= 1000`

## Solution Approach

Call `read4` into a temporary 4-char buffer, then copy that chunk into
`buf`, copying no more than the `n - total` characters still needed.

```
total = 0
while total < n:
    got = read4(buf4)
    if got == 0: break              # EOF
    take = min(got, n - total)      # don't overflow n
    copy buf4[0..take) -> buf[total..]
    total += take
    if got < 4: break               # short read => EOF
return total
```

Two cases to handle:
1. **The file is shorter than `n`.** Stop when `read4` returns less than 4.
2. **`n` is not a multiple of 4.** The last chunk may have more characters
   than you need, so copy only `n - total` of them.

### Complexity
- **Time:** O(n)
- **Space:** O(1) for the 4-char temp buffer

## Building and Running

```bash
make run     # build + run tests
make clean
```

The function is called `readN` in the C file, because `read` conflicts with
the POSIX `read()` from `<unistd.h>`. `read4` is simulated with a global
string so you can test locally.
