# 09 — Preprocessor and Miscellaneous Concepts

Source: [GfG C Tutorial → Miscellaneous Concepts](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`

**Contents**
1. [Preprocessors](#1-preprocessors)
2. [Macros](#2-macros)
3. [Header Files](#3-header-files)
4. [Date and Time](#4-date-and-time)
5. [Linkage](#5-linkage)
6. [Storage Classes](#6-storage-classes)

---

## 1. Preprocessors

**What it is**
- The **preprocessor** runs **before compilation** (stage 1 in 01 §2). It works on the source **as text**: it pastes in headers, replaces macros, and keeps or drops code according to conditions.
- Every line that starts with `#` is a **directive**. Directives don't end with `;`.
- See the result with `gcc -E file.c`.

**Directives**

| Directive | Purpose |
|-----------|---------|
| `#include <file>` | system header: searched in system include paths |
| `#include "file"` | your header: searched in the current directory first, then system paths |
| `#define NAME value` | define a macro |
| `#undef NAME` | remove a macro |
| `#ifdef NAME` / `#ifndef NAME` | compile the block if NAME is / isn't defined |
| `#if expr` / `#elif expr` / `#else` / `#endif` | conditional compilation on a constant integer expression |
| `defined(NAME)` | use inside `#if`: `#if defined(A) && !defined(B)` |
| `#error "msg"` | stop compilation with a message |
| `#warning "msg"` | print a warning (standard in C23, a GCC extension before that) |
| `#pragma ...` | compiler-specific instructions: `#pragma once`, `#pragma pack(1)`, `#pragma GCC diagnostic ...` |
| `#line n "file"` | change the reported line number and file name (used by code generators) |

**Predefined macros**

| Macro | Value |
|-------|-------|
| `__FILE__`, `__LINE__` | current file name (string) and line number (int) |
| `__func__` | current function name (C99; strictly an identifier, not a macro) |
| `__DATE__`, `__TIME__` | compile date and time (strings) |
| `__STDC_VERSION__` | `199901L` (C99), `201112L` (C11), `201710L` (C17), `202311L` (C23) |
| `__linux__`, `_WIN32`, `__APPLE__` | platform (compiler-provided) |
| `__GNUC__` | defined by GCC and Clang |

**Example** — [examples/09_preprocessor.c](examples/09_preprocessor.c)
```c
#ifndef LEVEL                     /* default unless given on the command line */
#define LEVEL 1
#endif

#if LEVEL < 0
#error "LEVEL must be >= 0"
#endif

#ifdef DEBUG
#define LOG(msg) fprintf(stderr, "[debug %s:%d] %s\n", __FILE__, __LINE__, msg)
#else
#define LOG(msg) ((void)0)        /* debug logging compiles to nothing */
#endif

#if LEVEL >= 3
    printf("LEVEL >= 3: verbose mode\n");
#elif LEVEL == 2
    printf("LEVEL == 2: normal mode\n");
#else
    printf("LEVEL <= 1: quiet mode\n");
#endif
```
```
$ gcc 09_preprocessor.c && ./a.out
notes-demo v1, PI = 3.14159, buf size = 64
LEVEL <= 1: quiet mode
platform: Linux
__FILE__ = 09_preprocessor.c, __LINE__ = 48, __func__ = main
__STDC_VERSION__ = 201112L
compiled on Nov 23 2026 at 16:30:16
PI is no longer defined after #undef

$ gcc -DDEBUG -DLEVEL=3 09_preprocessor.c && ./a.out      ← -D defines macros from the command line
[debug 09_preprocessor.c:30] inside main
notes-demo v3, PI = 3.14159, buf size = 64
LEVEL >= 3: verbose mode
...

$ gcc -DLEVEL=-1 09_preprocessor.c
09_preprocessor.c:15:2: error: #error "LEVEL must be >= 0"
```

**Key points / pitfalls**
- The preprocessor knows nothing about C types or scope. It does pure text substitution.
- Conditional compilation is how C handles **debug vs release builds** (`-DNDEBUG`), **platform differences**, and **feature flags**.
- To disable a big block of code, `#if 0 ... #endif` beats `/* */`, which can't be nested.
- An undefined identifier inside `#if` evaluates to `0`, so a typo silently becomes false. `-Wundef` warns about it.

**Interview Qs**
- *What does the preprocessor do?* It handles `#` directives (includes, macro expansion, conditional compilation) and produces pure C for the compiler.
- *`#include <>` vs `#include ""`?* `<>` searches the system paths. `""` searches the current directory first, then the system paths.
- *How do you see preprocessor output?* `gcc -E file.c`.

---

## 2. Macros

**What it is** — A macro is a name that the preprocessor replaces with text **before** compilation.

| Type | Example |
|------|---------|
| Object-like | `#define BUFFER_SIZE 64` |
| Function-like | `#define SQUARE(x) ((x) * (x))` |
| Multi-line | end each line with `\` |
| Variadic (C99) | `#define LOGF(fmt, ...) printf(fmt, __VA_ARGS__)` |

**Special operators**
- `#x` (**stringify**) turns the argument into a string literal: `STR(hello)` → `"hello"`.
- `a##b` (**token pasting**) joins two tokens into one: `CONCAT(my, Var)` → `myVar`.

**Example** — [examples/09_macros.c](examples/09_macros.c)
```c
#define SQUARE_BAD(x)  x * x
#define SQUARE(x)      ((x) * (x))           /* parenthesise every arg AND the whole body */
#define SWAP(T, a, b)  do { T tmp_ = (a); (a) = (b); (b) = tmp_; } while (0)
#define STR(x)         #x
#define XSTR(x)        STR(x)                /* two levels: expand x first */
#define PRINT_VAR(v)   printf(#v " = %d\n", v)
#define LOGF(fmt, ...) printf("[log] " fmt "\n", __VA_ARGS__)

/* X-macro: maintain ONE list, generate several things from it */
#define COLOR_LIST X(RED) X(GREEN) X(BLUE)
#define X(name) COLOR_##name,
enum Color { COLOR_LIST COLOR_COUNT };       /* COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_COUNT */
#undef X
#define X(name) #name,
static const char *color_names[] = { COLOR_LIST };   /* "RED", "GREEN", "BLUE" */
#undef X
```
Output:
```
SQUARE_BAD(2 + 3) = 11  (expands to 2 + 3 * 2 + 3)
SQUARE(2 + 3)     = 25
100 / SQUARE_BAD(5) = 100 (expands to 100 / 5 * 5)
100 / SQUARE(5)     = 4
MAX(7, 12)        = 12
after SWAP: a = 2, b = 1
STR(hello world)  = "hello world"
STR(VERSION)      = "VERSION"
XSTR(VERSION)     = "3"
myVar = 99
[log] cart has 3 items
color 0 = RED
color 1 = GREEN
color 2 = BLUE
```

See the expansion yourself:
```
$ printf '#define SQUARE_BAD(x) x * x\nSQUARE_BAD(2 + 3);\n' | gcc -E -P -
2 + 3 * 2 + 3;
```

**Macro pitfalls and fixes**

| Pitfall | Example | Fix |
|---------|---------|-----|
| Missing parentheses around args | `SQUARE_BAD(2+3)` → `2+3*2+3` = 11 | `((x) * (x))` |
| Missing parentheses around the body | `100 / SQUARE_BAD(5)` → `100/5*5` = 100 | wrap the whole body in `( )` |
| **Double evaluation** | `SQUARE(i++)` → `((i++) * (i++))`, which is UB | use a `static inline` function (02 §5) |
| Multi-statement macro in an `if` without braces | `if (c) SWAP(...); else ...` breaks | wrap in `do { ... } while (0)` |
| Stray semicolon | `#define N 10;` → `int a[N];` = `int a[10;];` | never end a `#define` with `;` |
| `#` stops expansion | `STR(VERSION)` → `"VERSION"` | two-level `XSTR` |

**Key points / pitfalls**
- **Why `do { } while (0)`?** It turns several statements into a single statement that still needs a trailing `;`, so the macro works correctly inside `if`/`else` without braces.
- Prefer `enum` or `const` for constants and `static inline` for small functions (02 §5). Use macros when you need what only the preprocessor can do: stringify, paste tokens, conditional compilation, or generic code.
- Macros ignore scope. A macro named `max` breaks every later use of `max` as a variable. Use UPPERCASE names.
- No space is allowed between a function-like macro's name and `(` in its definition: `#define F (x)` is an object-like macro whose body is `(x)`.

**Interview Qs**
- *Macro vs function?* A macro is text substitution with no type checking and no call overhead, and it may evaluate arguments more than once. A function is type-checked and evaluates each argument once.
- *What do `#` and `##` do in macros?* `#` stringifies an argument. `##` pastes two tokens into one.
- *Why wrap multi-statement macros in `do { } while (0)`?* So they behave like a single statement, safely inside `if`/`else`.
- *What is `__VA_ARGS__`?* It stands for the variable arguments (`...`) of a variadic macro.

---

## 3. Header Files

**What it is**
- A **header file** (`.h`) holds **declarations** that several `.c` files share: function prototypes, `extern` variable declarations, type definitions (`struct`, `typedef`, `enum`), and macros.
- `#include` simply **pastes** the header's text into the file.
- Standard headers: `stdio.h`, `stdlib.h`, `string.h`, `math.h`, `ctype.h`, `time.h`, `errno.h`, `assert.h`, `limits.h`, `stdint.h`, `stdbool.h`, `stddef.h`, `stdarg.h`, `signal.h`, `setjmp.h`.

**What goes where**

| Header (`.h`) — the interface | Source (`.c`) — the implementation |
|-------------------------------|------------------------------------|
| function prototypes | function definitions |
| `extern int g;` (declaration) | `int g = 0;` (definition) |
| `struct` / `typedef` / `enum` definitions | `static` helper functions and variables |
| macros, `static inline` functions | |
| **No** variable definitions or non-inline function bodies | |

**Include guards** stop the same header being pasted twice into one file, which would redefine its types:
```c
#ifndef MATHUTIL_H
#define MATHUTIL_H
/* ... declarations ... */
#endif
```
`#pragma once` does the same in one line. It isn't in the standard, but every major compiler supports it.

**Multi-file example** — [examples/09_multifile/](examples/09_multifile/)

[mathutil.h](examples/09_multifile/mathutil.h)
```c
#ifndef MATHUTIL_H
#define MATHUTIL_H
#define MATHUTIL_VERSION "1.0"
typedef struct { int min, max; } Range;
extern int mathutil_calls;          /* declaration only */
int  clamp(int x, Range r);
long factorial(int n);
#endif
```
[mathutil.c](examples/09_multifile/mathutil.c)
```c
#include "mathutil.h"               /* own header: compiler checks the definitions match */
int mathutil_calls = 0;             /* the one definition */
static void count_call(void) { mathutil_calls++; }   /* private helper */
int clamp(int x, Range r) { count_call(); return x < r.min ? r.min : x > r.max ? r.max : x; }
long factorial(int n) { ... }
```
[main.c](examples/09_multifile/main.c)
```c
#include <stdio.h>
#include "mathutil.h"
#include "mathutil.h"                /* twice on purpose: the guard makes it harmless */
int main(void) {
    Range r = {0, 10};
    printf("clamp(-5) = %d, clamp(7) = %d, clamp(42) = %d\n", clamp(-5, r), clamp(7, r), clamp(42, r));
    ...
}
```
```
$ cd examples/09_multifile
$ gcc -Wall -Wextra -std=c11 main.c mathutil.c -o app && ./app
mathutil v1.0
clamp(-5) = 0, clamp(7) = 7, clamp(42) = 10
factorial(10) = 3628800
mathutil_calls = 4 (extern variable from mathutil.c)

# separate compilation: only recompile files that changed, then re-link
$ gcc -c mathutil.c        # → mathutil.o
$ gcc -c main.c            # → main.o
$ gcc main.o mathutil.o -o app
```

**Key points / pitfalls**
- **Never define variables or (non-inline) functions in a header.** If two `.c` files include it, the linker sees two definitions (`multiple definition of ...`).
- Every header gets an include guard.
- A `.c` file should `#include` its own header, so the compiler catches mismatches between declarations and definitions.
- Headers should be self-contained: include whatever they themselves need (e.g. `<stddef.h>` for `size_t`).
- `gcc -I dir` adds a directory to the `#include` search path.

**Interview Qs**
- *What goes in a header file?* Declarations: prototypes, `extern` variables, types and macros. No definitions.
- *What are include guards?* `#ifndef X / #define X / #endif` around a header's contents, so including it twice is harmless.
- *What happens if you define a global variable in a header included by two files?* A linker error: multiple definition.

---

## 4. Date and Time

**What it is** — `<time.h>` provides calendar time, broken-down time, formatting, and CPU-time measurement.

| Type / function | Purpose |
|-----------------|---------|
| `time_t` | arithmetic type: seconds since the **epoch** (1970-01-01 00:00:00 UTC) |
| `struct tm` | broken-down time: `tm_year` (**years since 1900**), `tm_mon` (**0–11**), `tm_mday` (1–31), `tm_hour`, `tm_min`, `tm_sec`, `tm_wday` (0 = Sunday), `tm_yday` (0–365), `tm_isdst` |
| `time(NULL)` | current time as `time_t` |
| `localtime(&t)` / `gmtime(&t)` | `time_t` → `struct tm *` (local / UTC) |
| `mktime(&tm)` | `struct tm` (local) → `time_t`, and normalises out-of-range fields |
| `strftime(buf, n, fmt, &tm)` | format into a string |
| `ctime(&t)` / `asctime(&tm)` | quick fixed-format string (ends with `'\n'`) |
| `difftime(t1, t0)` | `t1 - t0` in seconds, as a `double` |
| `clock()` | CPU time used by the program, in ticks. Divide by `CLOCKS_PER_SEC` |

**Common `strftime` formats**: `%Y` year, `%m` month 01–12, `%d` day, `%H:%M:%S` time, `%A` weekday name, `%B` month name, `%j` day of year, `%Z` time zone.

**Example** — [examples/09_time.c](examples/09_time.c)
```c
time_t now = time(NULL);
struct tm *local = localtime(&now);
printf("%d-%02d-%02d\n", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);

char buf[64];
strftime(buf, sizeof buf, "%A, %d %B %Y", local);

struct tm later = *local;           /* copy: localtime returns a shared static buffer */
later.tm_mday += 100;               /* "day 123 of November" is fine...               */
time_t t_later = mktime(&later);    /* ...mktime normalises it to a real date          */

clock_t start = clock();
/* ... work ... */
double secs = (double)(clock() - start) / CLOCKS_PER_SEC;
```
Output (from one run; your values will differ):
```
time(NULL)  = 1795431617 seconds since the epoch
struct tm   : year=2026 month=11 day=23 16:30:17 weekday=1 yearday=326
strftime    : 2026-11-23 16:30:17
strftime    : Monday, 23 November 2026
gmtime      : 2026-11-23 11:00:17 UTC
ctime       : Mon Nov 23 16:30:17 2026
+100 days   : 2027-03-03 (difftime = 8640000 s = 100 days)
loop took   : 0.045 s CPU time
```

**Key points / pitfalls**
- `tm_year` counts **years since 1900** and `tm_mon` is **0-based**. Forgetting `+1900` / `+1` is the classic bug.
- `localtime`, `gmtime` and `ctime` return pointers to a **shared static buffer**, which the next call overwrites. They are not thread-safe. Copy the struct, or use POSIX `localtime_r`/`gmtime_r`.
- `clock()` measures **CPU time**, not wall-clock time: it doesn't advance while the program sleeps or waits for I/O. For wall-clock timing use `time()` (1-second resolution) or POSIX `clock_gettime(CLOCK_MONOTONIC, ...)`.
- A 32-bit signed `time_t` overflows in **January 2038** (the Y2038 problem). 64-bit systems use a 64-bit `time_t`.

**Interview Qs**
- *What is the Unix epoch?* 1970-01-01 00:00:00 UTC. `time_t` counts seconds from it.
- *How do you measure how long code takes?* `clock()` for CPU time, `time()`/`difftime()` or `clock_gettime` for wall-clock time.
- *Why add 1900 to `tm_year`?* `struct tm` stores years since 1900.

---

## 5. Linkage

**What it is** — **Linkage** decides whether a name declared in different places (or different files) refers to the **same** object or function.

| Linkage | Meaning | How you get it |
|---------|---------|----------------|
| **External** | one entity shared across **all files** of the program | file-scope functions and variables **by default**; `extern` declarations |
| **Internal** | private to **one file** (translation unit) | `static` at file scope |
| **None** | local to its block | local variables, function parameters |

```c
/* a.c */                                  /* b.c */
int shared = 1;          /* external */    extern int shared;       /* refers to a.c's */
static int hidden = 2;   /* internal */    static int hidden = 9;   /* a DIFFERENT variable */
void api(void) {}        /* external */    void api(void);          /* refers to a.c's */
static void helper(void) {} /* internal */ /* helper() not reachable from here */
```

From the multi-file example: `main.c` uses `mathutil_calls` through its `extern` declaration in the header. But `count_call` is `static` in `mathutil.c`, so calling it from another file fails **at link time**:
```
$ gcc main_calls_count_call.c mathutil.c
undefined reference to `count_call'
```

**Declaration vs definition (the One Definition Rule)**
- A **declaration** says "this exists somewhere": `extern int g;`, `int f(void);`. You may have many.
- A **definition** creates the object: `int g = 0;`, `int f(void) { ... }`. There must be **exactly one** across the program, for anything with external linkage.

**Key points / pitfalls**
- **Make every file-scope function and variable `static` unless other files need it.** This is C's form of encapsulation. It prevents name clashes and lets the compiler optimise.
- `static` means two different things: at **file scope** it gives internal linkage. On a **local variable** it gives static storage duration (§6).
- Two files that each define `int count;` (no `extern`, no `static`) are an error with GCC ≥ 10 (`-fno-common` is the default): `multiple definition of 'count'`.
- `extern` on a function prototype is allowed but redundant, since functions have external linkage by default.

**Interview Qs**
- *Internal vs external linkage?* External: visible to all files. Internal (`static` at file scope): visible only in its own file.
- *What does `static` do to a global variable or function?* It limits visibility to the current file (internal linkage).
- *What does `extern` do?* It declares a variable defined elsewhere, without allocating storage.

---

## 6. Storage Classes

**What it is** — A storage class sets a variable's **lifetime** (storage duration), **scope** (where the name is visible), **linkage**, and **default initial value**.

| Storage class | Where declared | Storage location | Default value | Scope | Lifetime | Linkage |
|---------------|----------------|------------------|---------------|-------|----------|---------|
| `auto` (default for locals) | inside a block | stack | **garbage** | block | until the block ends | none |
| `register` | inside a block | CPU register (hint) | **garbage** | block | until the block ends | none |
| `static` (local) | inside a block | data/BSS | **0** | block | **whole program** | none |
| `static` (global) | file scope | data/BSS | **0** | file | whole program | **internal** |
| `extern` | anywhere | data/BSS (defined elsewhere) | **0** (at the definition) | declaration's scope | whole program | **external** |
| (plain global) | file scope | data/BSS | **0** | file (+ others via `extern`) | whole program | external |

C11 adds **`_Thread_local`**: each thread gets its own copy of the variable.

**Example** — [examples/09_storage_classes.c](examples/09_storage_classes.c)
```c
int global_counter = 0;              /* static storage, external linkage */
static int file_private = 100;       /* static storage, internal linkage */

void counter_demo(void)
{
    auto int a = 0;                  /* re-created on every call */
    static int s = 0;                /* initialised ONCE, keeps its value */
    register int r = 0;              /* &r is not allowed */
    a++; s++; r++; global_counter++;
}

int next_id(void) { static int id = 1000; return id++; }   /* classic static-local use */

void use_extern(void) {
    extern int defined_later;        /* declaration; the definition comes later */
    printf("%d\n", defined_later);
}
int defined_later = 7;
```
Output:
```
  auto a = 1, static s = 1, register r = 1, global = 1
  auto a = 1, static s = 2, register r = 1, global = 2
  auto a = 1, static s = 3, register r = 1, global = 3
ids: 1000 1001 1002
file_private = 100
extern defined_later = 7
inner x = 2
outer x = 1
```

**Key points / pitfalls**
- A `static` local is initialised **once**, before the program starts. Its initialiser must be a constant expression (`static int x = f();` is an error in C).
- `register` is only a hint, and modern compilers ignore it for optimisation. The one visible effect is that **you can't take its address**.
- A static local makes a function **stateful**, so it is not re-entrant or thread-safe. Example: `strtok` (03 §4).
- The **order in which function arguments are evaluated is unspecified**: `printf("%d %d", next_id(), next_id())` printed `1002 1001` when first tried. Call stateful functions in separate statements.
- Returning a pointer to a `static` local is safe because it lives for the whole program. Returning a pointer to an `auto` local is not (04 §1).

**Interview Qs**
- *What are the storage classes in C?* `auto`, `register`, `static`, `extern` (plus `_Thread_local` in C11; `typedef` is grammatically a storage-class specifier too).
- *Difference between a static local and a normal local?* A static local keeps its value between calls and lives for the whole program. A normal local is re-created on every call.
- *Default value of a static or global variable vs an auto variable?* Static and global: 0. Auto: indeterminate (garbage).
- *Can you take the address of a `register` variable?* No.

---

### Quick revision
- The preprocessor does text substitution before compiling: `#include`, `#define`, `#if/#ifdef`, `#error`. Use `-D` on the command line and view output with `gcc -E`.
- Macros: parenthesise args and the body, use `do{}while(0)` for statements, beware double evaluation. `#` stringifies, `##` pastes tokens. `__VA_ARGS__` holds variadic args.
- Headers hold **declarations only** and need include guards. Definitions go in exactly one `.c` file.
- `<time.h>`: `time` → `localtime` → `strftime`. `tm_year+1900`, `tm_mon+1`. `clock()/CLOCKS_PER_SEC` measures CPU time.
- Linkage: external (default), internal (`static` at file scope), none (locals). Make file-scope things `static` by default.
- Storage: `auto` (stack, garbage), `static` (lives forever, zeroed, initialised once), `register` (no `&`), `extern` (defined elsewhere).
