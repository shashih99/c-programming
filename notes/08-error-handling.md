# 08 — Error Handling

Source: [GfG C Tutorial → Error Handling](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog -lm && ./prog`

**Contents**
1. [Error Handling in C](#1-error-handling-in-c)
2. [Exception Handling Using goto](#2-exception-handling-using-goto)
3. [File Error Handling](#3-file-error-handling)
4. [Divide by Zero and Runtime Errors](#4-divide-by-zero-and-runtime-errors)
5. [assert](#5-assert)
6. [setjmp / longjmp](#6-setjmp--longjmp)

---

## 1. Error Handling in C

**What it is**
- C has **no exceptions** (`try`/`catch`). Errors are reported by **return values** and the global variable **`errno`**, and the caller must check them.
- The standard library follows a few conventions:

| Convention | Examples |
|------------|----------|
| Return `NULL` on failure | `fopen`, `malloc`, `strstr` |
| Return `EOF` / negative | `fgetc`, `fclose`, `printf` |
| Return a count smaller than asked | `fread`, `fwrite`, `scanf` |
| Return non-zero | `remove`, `rename`, `fseek` |
| Set **`errno`** to explain *why* | most of the above |

**Tools** (`<errno.h>`, `<string.h>`, `<stdio.h>`, `<stdlib.h>`)

| Tool | Purpose |
|------|---------|
| `errno` | int set by library calls on failure: `ENOENT` (no such file), `EACCES` (permission), `ENOMEM`, `ERANGE` (out of range), `EDOM` (math domain)… |
| `perror("msg")` | prints `msg: <description of errno>` to **stderr** |
| `strerror(errno)` | returns the description as a string, to use in your own messages |
| `exit(status)` / `return` from `main` | report success (`EXIT_SUCCESS` = 0) or failure (`EXIT_FAILURE` = 1) to the shell |

**Example** — [examples/08_errno.c](examples/08_errno.c)
```c
FILE *fp = fopen("/no/such/dir/file.txt", "r");
if (fp == NULL) {
    int saved = errno;                         /* save before any other call */
    printf("errno = %d\n", saved);
    printf("strerror: %s\n", strerror(saved));
    perror("perror  ");
}

/* parse a whole string as int, detecting every error case */
int parse_int(const char *s, int *out)
{
    char *end;
    errno = 0;                                 /* reset first */
    long v = strtol(s, &end, 10);
    if (end == s)       return -1;             /* no digits at all       */
    if (*end != '\0')   return -1;             /* trailing junk          */
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX) return -1;   /* overflow */
    *out = (int)v;
    return 0;
}
```
Output:
```
errno = 2
strerror: No such file or directory
perror  : No such file or directory
sqrt(-1) = -nan, errno = 33 (EDOM)
  "42" -> 42
  "abc": not a number
  "12xy": trailing junk "xy"
  "99999999999": out of int range
  "-7" -> -7
EXIT_SUCCESS = 0, EXIT_FAILURE = 1
```

**Key points / pitfalls**
- Library functions only **set** `errno` on failure. They never reset it to 0 on success. So:
  1. check the **return value** first, and only then look at `errno`, and
  2. when the return value is ambiguous (as with `strtol`), set `errno = 0` **before** the call.
- **Save `errno` immediately**. Any later library call, even `printf`, may overwrite it.
- `atoi`/`atof` can't report errors (`atoi("abc")` is 0, the same as `atoi("0")`). Use `strtol`/`strtod`.
- Print errors to **`stderr`**, not `stdout`, so they show up even when output is redirected (`./prog > out.txt`).
- `errno` values are platform-specific numbers. Compare them with the **macro names** (`ENOENT`), never with literals like `2`.
- Design your own functions the same way: return a status code (0 = OK, negative = error) and pass results out through pointer parameters (02 §2).

**Interview Qs**
- *How does C handle errors without exceptions?* Through return values (NULL, EOF, −1, short counts) and `errno`, which the caller checks.
- *`perror` vs `strerror`?* `perror` prints a message plus the `errno` description to stderr. `strerror` returns the description string.
- *Why set `errno = 0` before calling `strtol`?* `strtol` may legitimately return `LONG_MAX`. Only a changed `errno` tells you it overflowed.

---

## 2. Exception Handling Using goto

**What it is** — When a function acquires several resources (files, memory, locks), every failure must release **exactly what has been acquired so far**. Writing the cleanup out at each failure point gets repetitive and error-prone. The idiomatic C solution is **`goto cleanup`**: one exit path at the bottom of the function. The Linux kernel uses this pattern everywhere.

**Without goto: cleanup repeated at every exit**
```c
in = fopen(src, "rb");
if (!in) return -1;
out = fopen(dst, "wb");
if (!out) { fclose(in); return -1; }
buf = malloc(4096);
if (!buf) { fclose(out); fclose(in); return -1; }   /* grows with every resource */
```

**With goto: single exit** — [examples/08_goto_cleanup.c](examples/08_goto_cleanup.c)
```c
int copy_file(const char *src, const char *dst)
{
    int status = -1;                     /* assume failure */
    FILE *in = NULL, *out = NULL;        /* initialise to NULL so cleanup is safe */
    char *buf = NULL;

    in = fopen(src, "rb");
    if (!in) { perror(src); goto cleanup; }

    out = fopen(dst, "wb");
    if (!out) { perror(dst); goto cleanup; }

    buf = malloc(4096);
    if (!buf) { perror("malloc"); goto cleanup; }

    size_t n;
    while ((n = fread(buf, 1, 4096, in)) > 0)
        if (fwrite(buf, 1, n, out) != n) { perror("fwrite"); goto cleanup; }
    if (ferror(in)) { perror("fread"); goto cleanup; }

    status = 0;                          /* success */

cleanup:                                 /* release in REVERSE order of acquisition */
    free(buf);                           /* free(NULL) is a no-op */
    if (out && fclose(out) != 0) { perror("fclose"); status = -1; }
    if (in) fclose(in);
    return status;
}
```
Output:
```
copy existing file : ok
missing.txt: No such file or directory
copy missing file  : failed
/no/dir/out.txt: No such file or directory
copy to bad path   : failed
```

A variant uses **several labels** (`err_free_buf:`, `err_close_out:`, `err_close_in:`), each falling through to the next, so each failure point jumps to the label that undoes exactly what it acquired.

**Key points / pitfalls**
- Initialise every resource to `NULL` at the top, so the cleanup code can test or free them unconditionally.
- Jump **forward** to cleanup only. Backward jumps and jumps into blocks make spaghetti code.
- Don't jump past the declaration of a variable-length array (that is a compile error). Declare variables at the top of the function.
- This is the one widely accepted use of `goto` in modern C. Elsewhere, prefer structured control flow.

**Interview Qs**
- *Is `goto` always bad?* No. Forward jumps to a single cleanup block are idiomatic and make resource handling clearer.
- *How do you emulate exceptions in C?* Return codes with `goto cleanup`, or `setjmp`/`longjmp` (§6) for non-local jumps.

---

## 3. File Error Handling

**What it is** — Every file operation can fail: open (missing file, permissions), read (I/O error), write (disk full), close (the final flush fails). Check each one.

| Check | When |
|-------|------|
| `fopen(...) == NULL` | after opening |
| Read return value (`EOF`, `NULL`, short count) | every read |
| `ferror(fp)` | after a read loop ends, to tell an error from EOF (07 §5) |
| Write return value (`fwrite` count, `fprintf` < 0, `fputs` == EOF) | every write |
| `fclose(fp) == EOF` | **especially after writing**: buffered data is flushed here |
| `clearerr(fp)` | reset the error/EOF flags to continue |

**Example** — [examples/08_file_errors.c](examples/08_file_errors.c)
```c
FILE *fp = fopen("missing.txt", "r");
if (!fp) printf("fopen missing.txt failed: %s\n", strerror(errno));

fp = fopen("err_demo.txt", "w");
int c = fgetc(fp);                           /* reading a write-only stream → error */
printf("... ferror = %d, feof = %d\n", ferror(fp) != 0, feof(fp) != 0);

fp = fopen("/dev/full", "w");                /* Linux device: every write fails (disk full) */
int r = fprintf(fp, "hello");                /* only fills the buffer → reports success! */
if (fclose(fp) == EOF)                       /* the real write happens here and fails */
    printf("fclose failed: %s\n", strerror(errno));
```
Output:
```
fopen missing.txt failed: No such file or directory
fgetc on write-only stream -> -1, ferror = 1, feof = 0
after clearerr, ferror = 0
fprintf to /dev/full returned 5 (buffered, no error yet)
fclose failed: No space left on device
```

**Key points / pitfalls**
- Because of buffering, **a successful `fprintf` doesn't mean the data was written**. Disk-full and similar errors often show up only at `fflush` or `fclose`. Programs that save important data must check `fclose`.
- `fgetc` returning `EOF` is ambiguous: it can mean end of file or an error. Use `feof`/`ferror` to tell which.
- A good error message includes **what** failed, **which file**, and **why**: `perror(path)` gives `data.txt: Permission denied`.

---

## 4. Divide by Zero and Runtime Errors

**What it is**
- **Integer** division or modulo by zero is **undefined behaviour**. On x86 Linux the program usually dies with `SIGFPE` ("Floating point exception", despite the name). C does not throw anything you can catch, so you must **check before dividing**.
- `INT_MIN / -1` (and `INT_MIN % -1`) also overflows. That is UB too.
- **Floating-point** division by zero is *not* an error under IEEE-754. It produces `inf`, `-inf` or `nan`, which you can test with `isinf`/`isnan` (`<math.h>`).

**Example** — [examples/08_divide_by_zero.c](examples/08_divide_by_zero.c)
```c
int safe_divide(int a, int b, int *result)
{
    if (b == 0)                    { fprintf(stderr, "error: division by zero\n"); return -1; }
    if (a == INT_MIN && b == -1)   { fprintf(stderr, "error: overflow\n");        return -1; }
    *result = a / b;
    return 0;
}

double zero = 0.0;
printf("%f %f %f\n", 1.0 / zero, -1.0 / zero, zero / zero);   /* inf -inf nan */
```
Output:
```
  10 / 2 = 5
  error: division by zero (7 / 0)
  error: overflow (INT_MIN / -1)
  -9 / 4 = -2
1.0 / 0.0 = inf, -1.0 / 0.0 = -inf, 0.0 / 0.0 = -nan
isinf(1.0/0.0) = 1, isnan(0.0/0.0) = 1
average = 4.00
```
(`-9 / 4 = -2`: integer division truncates **toward zero** since C99.)

**Other common runtime errors**

| Error | Typical result | Prevention |
|-------|---------------|------------|
| NULL / dangling pointer dereference | segfault (`SIGSEGV`) | check pointers, set to NULL after free |
| Array out of bounds | silent corruption or segfault | check indices, use ASan |
| Signed integer overflow | UB | check before the operation, use wider types |
| Stack overflow | segfault | limit recursion depth, avoid huge locals |
| Uninitialised variable | garbage values | always initialise, use `-Wall` |

**Key points / pitfalls**
- Validate inputs at the boundary: user input, file data, function arguments.
- Compiling with `-fsanitize=undefined` reports integer divide-by-zero and overflow with the file and line.
- Handling `SIGFPE` with a signal handler is possible, but returning from the handler is UB. It is fit only for logging and exiting (see 10 → Signals).

**Interview Qs**
- *What happens on integer division by zero in C?* Undefined behaviour. In practice it usually crashes with SIGFPE.
- *And floating-point division by zero?* It gives ±inf, or NaN for 0.0/0.0, per IEEE-754. It is not a crash.
- *Which other integer division can fail?* `INT_MIN / -1`, because the result doesn't fit in an int.

---

## 5. assert

**What it is** — `assert(expr)` from `<assert.h>` checks a condition that **must be true if the program is correct**. If it is false, `assert` prints the expression, file, line and function, then calls `abort()`.

```c
#include <assert.h>
double average(const int *a, int n)
{
    assert(a != NULL && "array must not be NULL");   /* string trick: shows in the message */
    assert(n > 0);
    ...
}
```
```
$ ./a.out
a.out: a.c:2: main: Assertion `n > 0' failed.
Aborted (core dumped)              ← exit status 134

$ gcc -DNDEBUG a.c && ./a.out      ← NDEBUG removes all asserts
(nothing; exit status 0)
```
C11 also has **`static_assert(cond, "msg")`**, which checks at **compile time**, e.g. `static_assert(sizeof(int) == 4, "need 32-bit int");`.

**assert vs error handling**

| Use `assert` for | Use error handling (return codes) for |
|------------------|---------------------------------------|
| **Bugs**: conditions that should be impossible | **Expected failures**: missing files, bad user input, out of memory |
| Function preconditions in internal code | Anything that can happen in production |
| Removed in release builds (`-DNDEBUG`) | Always active |

**Key points / pitfalls**
- **Never put side effects inside `assert`**: `assert(fp = fopen(...))` vanishes completely with `NDEBUG`.
- Don't use `assert` to validate user input or check `malloc` results in production code.

---

## 6. setjmp / longjmp

**What it is** — `<setjmp.h>` provides **non-local jumps**. `setjmp(env)` saves the current execution context and returns 0. Later, `longjmp(env, val)`, even from deep inside nested calls, jumps back so that `setjmp` "returns again" with `val`. This is the closest C has to `try`/`throw`/`catch`.

**Example** — [examples/08_setjmp.c](examples/08_setjmp.c)
```c
static jmp_buf on_error;

int parse_digit(char c) {
    if (c < '0' || c > '9') longjmp(on_error, ERR_PARSE);   /* "throw" */
    return c - '0';
}

switch (setjmp(on_error)) {          /* "try" */
case ERR_NONE:  printf("sum %d\n", checked_sum(s)); break;
case ERR_PARSE: printf("error PARSE\n");            break;   /* "catch" */
case ERR_RANGE: printf("error RANGE\n");            break;
}
```
Output:
```
"123" -> sum 6
"12a" -> error PARSE
"99999" -> error RANGE
```

**Key points / pitfalls**
- `setjmp` may only appear in restricted contexts: as the whole controlling expression of `if`/`switch`/`while`, compared with a constant, or as a standalone statement. `int e = setjmp(env);` is technically **not allowed**.
- **No cleanup happens during the jump**: memory, open files and locks acquired between `setjmp` and `longjmp` leak unless you track them.
- Local variables modified after `setjmp` have indeterminate values after `longjmp` unless declared `volatile`.
- Never `longjmp` into a function that has already returned.
- In practice, prefer return codes with `goto cleanup`. `setjmp`/`longjmp` is used in parsers, interpreters (e.g. Lua's error handling) and some test frameworks.

**Interview Qs**
- *How can you implement try/catch in C?* With `setjmp` (try/catch point) and `longjmp` (throw).
- *Main danger of `longjmp`?* It skips all intermediate cleanup, so resources leak and non-volatile locals become unreliable.

---

### Quick revision
- No exceptions: **check every return value** (NULL, EOF, −1, short counts). `errno` tells you why.
- Reset `errno = 0` before ambiguous calls (`strtol`). Save `errno` right away. Print with `perror`/`strerror` to **stderr**.
- Use `strtol` (with `endptr` + `errno`) instead of `atoi` for safe parsing.
- `goto cleanup` gives a single exit that frees resources in reverse order. Initialise resource pointers to NULL.
- Check `fclose` after writing, because buffered write errors surface there.
- Integer `/0` and `INT_MIN / -1` are UB, so check first. Float `/0` gives `inf`/`nan`.
- `assert` is for bugs and is removed with `-DNDEBUG`. Never put side effects in it. `static_assert` checks at compile time.
- `setjmp`/`longjmp` work like try/catch, but skip cleanup. Use them sparingly.
