# C Programming Notes

Concise notes with runnable examples, following the
[GeeksforGeeks C Tutorial](https://www.geeksforgeeks.org/c/c-programming-language/).

## Contents

| # | Section | Status |
|---|---------|--------|
| 01 | [Basics](01-basics.md) — intro, compilation, identifiers, keywords, I/O, variables, data types, operators, conditionals, loops | ✅ |
| 02 | [Functions](02-functions.md) — prototypes, parameter passing, `main`, recursion, inline, nested | ✅ |
| 03 | [Arrays and Strings](03-arrays-and-strings.md) — 1-D/2-D arrays, decay, strings, `<string.h>` | ✅ |
| 04 | Pointers | ⏳ |
| 05 | User Defined Data Types — struct, padding, union, enum, bit fields | ⏳ |
| 06 | Memory Management — layout, malloc/free, leaks | ⏳ |
| 07 | File Handling | ⏳ |
| 08 | Error Handling | ⏳ |
| 09 | Preprocessor and Misc — macros, headers, time.h, linkage, storage classes | ⏳ |
| 10 | Advanced — variadic, syscalls, signals, sockets, `_Generic`, threads | ⏳ |
| 11 | What's Next — interview Qs, DSA, practice | ⏳ |

## Running the examples

```bash
cd examples
gcc -Wall -Wextra -std=c11 01_operators.c -o prog && ./prog
```

Example files are named `NN_topic.c`, where `NN` is the section number.

See [PLAN.md](PLAN.md) for the full outline.

> `02_nested.c` uses a GCC-only extension: compile it with `-std=gnu11` instead of `-std=c11`.
