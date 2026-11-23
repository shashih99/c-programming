# Number of 1 Bits

LeetCode 191: https://leetcode.com/problems/number-of-1-bits/

## Problem Statement

Given a positive integer `n`, write a function that returns the number of set bits in its binary representation (also known as the [Hamming weight](https://en.wikipedia.org/wiki/Hamming_weight)).

### Examples

- Input: `11` → Output: `3` (binary `1011`)
- Input: `128` → Output: `1` (binary `10000000`)
- Input: `2147483645` → Output: `30` (binary `1111111111111111111111111111101`)

### Constraints

- `1 <= n <= 2^31 - 1`

## Solution Approach

### Brian Kernighan's Trick

`n & (n - 1)` clears the lowest set bit of `n`. Subtracting 1 flips the lowest `1` to `0` and all the `0`s below it to `1`; AND-ing with the original wipes out exactly that region.

```
n       = 1011 0100
n - 1   = 1011 0011
n & n-1 = 1011 0000
```

Repeat until `n` is `0` and count the iterations:

```
count = 0
while n != 0:
    n = n & (n - 1)
    count++
```

The loop runs once per set bit instead of once per bit position.

### Alternative: Check Every Bit

```
while n != 0:
    count += n & 1
    n >>= 1
```

Also correct, but always walks up to the highest set bit (up to 32 iterations).

### Complexity

- **Time**: O(k), where k is the number of set bits (≤ 32)
- **Space**: O(1)

## Example Walkthrough: `11` (`1011`)

```
n = 1011 → n & (n-1) = 1011 & 1010 = 1010, count = 1
n = 1010 → n & (n-1) = 1010 & 1001 = 1000, count = 2
n = 1000 → n & (n-1) = 1000 & 0111 = 0000, count = 3
Result: 3 ✓
```

## Follow-up

If the function is called many times, precompute a 256-entry table of bit counts and sum the counts of the four bytes. Compilers also provide `__builtin_popcount`, which maps to a single CPU instruction on most targets.

## Building and Running

```bash
make        # compile
make run    # run test cases
make clean  # remove build artifacts
```
