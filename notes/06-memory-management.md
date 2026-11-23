# 06 — Memory Management

Source: [GfG C Tutorial → Memory Management](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`
(Addresses below are from one run on x86-64 Linux. They change every run because of ASLR.)

**Contents**
1. [Program's Memory Layout](#1-programs-memory-layout)
2. [Dynamic Memory Allocation](#2-dynamic-memory-allocation)
3. [Memory Leaks](#3-memory-leaks)
4. [Other Memory Errors and Tools](#4-other-memory-errors-and-tools)

---

## 1. Program's Memory Layout

**What it is** — A running C program's virtual memory is divided into **segments**, each with its own purpose and lifetime.

```
 High addresses
┌──────────────────────────┐
│ Command-line args, env   │  argv, envp
├──────────────────────────┤
│ STACK        ↓ grows down│  local variables, function params, return addresses
│                          │  (one "frame" per active call; ~8 MB default on Linux)
├ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┤
│      (free space)        │  shared libraries / mmap regions also live up here
├ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┤
│ HEAP         ↑ grows up  │  malloc / calloc / realloc → you manage it with free
├──────────────────────────┤
│ BSS                      │  uninitialised (or zero) globals & statics → set to 0
├──────────────────────────┤
│ DATA                     │  initialised globals & statics (read-write)
├──────────────────────────┤
│ RODATA                   │  string literals, const globals (read-only)
├──────────────────────────┤
│ TEXT (code)              │  compiled machine instructions (read-only, executable)
└──────────────────────────┘
 Low addresses
```

| Segment | What goes there | Lifetime | Who manages it |
|---------|-----------------|----------|----------------|
| Text | function code | whole program | OS loader |
| Rodata | `"literals"`, `const` globals | whole program | OS loader |
| Data | `int g = 10;`, `static int s = 5;` | whole program | OS loader |
| BSS | `int g;`, `static int s;` (zeroed) | whole program | OS loader |
| Heap | `malloc`'d blocks | until `free` | **you** |
| Stack | locals, params, return addresses | until the function returns | compiler (automatic) |

**Example** — [examples/06_memory_layout.c](examples/06_memory_layout.c)
```c
int global_init = 10;          /* .data  */
int global_uninit;             /* .bss   */
const char *msg = "hello";     /* literal in .rodata */
void func(void) {}             /* .text  */

int main(void) {
    static int static_local;   /* .bss   */
    int local = 1;             /* stack  */
    int *heap = malloc(sizeof *heap);   /* heap */
    ...
}
```
Output:
```
text   : func           = 0x55f2f5294169
rodata : "hello"        = 0x55f2f5295008
data   : global_init    = 0x55f2f5297030
data   : static_global  = 0x55f2f5297034
bss    : global_uninit  = 0x55f2f5297044 (value 0)
bss    : static_local   = 0x55f2f5297048 (value 0)
heap   : heap           = 0x55f306d292a0
stack  : local          = 0x7fff2c38faf4
stack grows downward:
  depth 0: &local = 0x7fff2c38fadc
  depth 1: &local = 0x7fff2c38faac
  depth 2: &local = 0x7fff2c38fa7c
```
The addresses rise text → rodata → data → bss → heap, and the stack sits far above. Each deeper call's `local` is at a **lower** address, which shows the stack growing down.

Inspect the segment sizes of a compiled binary with `size`:
```
$ size ./layout
   text    data     bss     dec     hex filename
   2333     624      16    2973     b9d ./layout
```

**Stack vs heap**

| | Stack | Heap |
|-|-------|------|
| Allocation | automatic (enter/leave function) | manual (`malloc`/`free`) |
| Speed | very fast (just move the stack pointer) | slower (allocator bookkeeping) |
| Size | small and fixed (`ulimit -s` = 8192 KB) | large, limited by RAM and virtual memory |
| Lifetime | ends when the function returns | until you `free` |
| Size known at | compile time (except VLAs) | runtime |
| Failure mode | **stack overflow** (segfault) | `malloc` returns `NULL` |
| Fragmentation | none | possible |

**Key points / pitfalls**
- BSS takes **no space in the executable file**. The loader simply zero-fills it. That is why `int big[1000000];` at global scope doesn't bloat the binary.
- Deep or infinite recursion and huge local arrays exhaust the stack (02 §4, 03 §1).
- Returning `&local` gives a pointer into a dead stack frame (04 §1).
- `static` locals live in data/BSS, not on the stack. That is why they keep their value between calls (01 §6).

**Interview Qs**
- *Name the segments of a C program's memory.* Text, (ro)data, BSS, heap, stack.
- *Where are global, static, local and dynamically allocated variables stored?* Globals and statics in data/BSS, locals on the stack, `malloc`'d memory on the heap.
- *Why is BSS separate from data?* Zero-initialised data needn't be stored in the file. Only its size is recorded.
- *Which way does the stack grow?* Downward (toward lower addresses) on x86 and most common architectures.

---

## 2. Dynamic Memory Allocation

**What it is** — Requesting memory **at runtime** from the heap, when the size isn't known at compile time or the data must outlive the function that created it. All the functions are in `<stdlib.h>`.

| Function | Signature | What it does |
|----------|-----------|--------------|
| `malloc` | `void *malloc(size_t size)` | allocates `size` bytes, **uninitialised** (garbage) |
| `calloc` | `void *calloc(size_t n, size_t size)` | allocates `n * size` bytes, **zeroed**, and checks `n*size` for overflow |
| `realloc` | `void *realloc(void *p, size_t size)` | resizes a block, **keeping its contents**. It may move it to a new address |
| `free` | `void free(void *p)` | returns a block to the allocator. `free(NULL)` is a safe no-op |

All three allocators return **`NULL` on failure**. Always check.

**Idiomatic usage**
```c
int *a = malloc(n * sizeof *a);          /* sizeof *a: stays correct if a's type changes */
if (a == NULL) { perror("malloc"); return 1; }
...
free(a);
a = NULL;                                /* avoid a dangling pointer / double free */
```

**`realloc` — the safe pattern**
```c
int *tmp = realloc(a, new_n * sizeof *a);
if (tmp == NULL) { /* a is STILL valid: handle error, free(a) */ }
else a = tmp;
/* WRONG: a = realloc(a, ...);  → on failure a becomes NULL and the old block leaks */
```
Special cases: `realloc(NULL, n)` behaves like `malloc(n)`. `realloc(p, 0)` is implementation-defined, so don't use it to free.

**Example** — [examples/06_dynamic_alloc.c](examples/06_dynamic_alloc.c)
```c
/* growable array — doubling capacity gives amortised O(1) push */
typedef struct { int *data; size_t len, cap; } Vec;

int vec_push(Vec *v, int x) {
    if (v->len == v->cap) {
        size_t new_cap = v->cap ? v->cap * 2 : 4;
        int *tmp = realloc(v->data, new_cap * sizeof *tmp);
        if (!tmp) return 0;
        v->data = tmp; v->cap = new_cap;
    }
    v->data[v->len++] = x;
    return 1;
}

/* dynamic 2-D, ONE block (cache-friendly, single free) */
int *grid = malloc((size_t)rows * cols * sizeof *grid);
grid[r * cols + c] = ...;
free(grid);

/* dynamic 2-D, array of row pointers (rows can differ in length) */
int **m = malloc(rows * sizeof *m);
for (int r = 0; r < rows; r++) m[r] = calloc(r + 1, sizeof **m);
...
for (int r = 0; r < rows; r++) free(m[r]);   /* free rows first */
free(m);                                     /* then the pointer array */

/* flexible array member (C99): header + variable-length data in ONE allocation */
typedef struct { size_t len; char text[]; } Message;
Message *msg = malloc(sizeof *msg + strlen(s) + 1);
```
Output:
```
malloc : 0 1 4 9 16
calloc : 0 0 0 0 0
realloc: 0 1 4 9 16 -1 -1 -1
vec_push 1..9:
  (grew capacity to 4)
  (grew capacity to 8)
  (grew capacity to 16)
vec: len=9 cap=16, last=9
grid[2][3] = 23
jagged m[2][2] = 7
Message: len=9 text=flexible! sizeof(Message)=8
```
(`sizeof(Message)` is 8: the flexible `text[]` contributes 0 bytes.)

**`malloc` vs `calloc`**

| | `malloc(n * size)` | `calloc(n, size)` |
|-|--------------------|-------------------|
| Arguments | 1 (total bytes) | 2 (count, element size) |
| Contents | garbage | all bits zero |
| Overflow check on `n*size` | no (you must check) | yes |
| Speed | slightly faster | may be just as fast for large blocks (fresh OS pages are already zero) |

**Key points / pitfalls**
- **Every `malloc`/`calloc`/`realloc` must be matched by exactly one `free`.**
- Pass `free` only a pointer that came from `malloc`/`calloc`/`realloc`, unchanged. Freeing a pointer to the stack, or `p + 1`, is UB.
- `free` doesn't change your pointer. It still holds the old address (dangling). Set it to `NULL` yourself.
- Don't cast the result of `malloc` in C. The cast is unnecessary and can hide a missing `#include <stdlib.h>`.
- `malloc(0)` may return `NULL` or a unique pointer. Never dereference it.
- `sizeof(ptr)` gives the pointer size (8), **not** the allocated size. C can't tell you how big a heap block is, so track the length yourself.
- After `realloc` moves a block, **every other pointer into the old block is dangling**.
- For nested allocations, free in **reverse order** (children before parents).

**Interview Qs**
- *`malloc` vs `calloc`?* `calloc` zeroes memory, takes (count, size) and checks for overflow. `malloc` leaves memory uninitialised.
- *What does `realloc` do if it can't grow in place?* It allocates a new block, copies the old contents, frees the old block and returns the new address.
- *Why not write `p = realloc(p, n)`?* If `realloc` fails it returns `NULL`, the original pointer is lost, and the block leaks.
- *What happens if you `free` the same pointer twice?* Undefined behaviour (heap corruption). It is often exploitable.

---

## 3. Memory Leaks

**What it is** — A **memory leak** is heap memory that was allocated but never freed and is **no longer reachable** (no pointer to it remains). The program's memory use keeps growing. That is bad for long-running programs: servers, daemons, embedded systems.

**Common causes**
1. **Early return / error path** that skips `free`.
2. **Ignoring ownership**: a function returns heap memory and the caller never frees it.
3. **Overwriting the only pointer** to a block (`p = malloc(...)` twice).
4. `p = realloc(p, n)` failing (§2).
5. Freeing a struct but not the blocks its members point to.
6. A local pointer going out of scope without `free`.

**Example** — [examples/06_memory_leak.c](examples/06_memory_leak.c)
```c
char *make_greeting(const char *name) {   /* returns heap memory: CALLER must free */
    char *s = malloc(strlen(name) + 8);
    if (s) sprintf(s, "Hello, %s", name);
    return s;
}

int process(int fail) {
    int *buf = malloc(100 * sizeof *buf);
    if (fail) return -1;                  /* LEAK 1: forgot free(buf) on this path */
    free(buf);
    return 0;
}

char *g = make_greeting("C");             /* LEAK 2: never free(g) */
int *p = malloc(sizeof *p);
p = malloc(sizeof *p);                    /* LEAK 3: first block now unreachable */
```

**Detecting leaks**

With AddressSanitizer (built into GCC/Clang):
```
$ gcc -g -fsanitize=address 06_memory_leak.c -o leak && ./leak
Hello, C
done
Direct leak of 400 byte(s) in 1 object(s) allocated from:
    #1 ... in process   06_memory_leak.c:18
Direct leak of 9 byte(s) in 1 object(s) allocated from:
    #1 ... in make_greeting 06_memory_leak.c:11
Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #1 ... in main      06_memory_leak.c:40
SUMMARY: AddressSanitizer: 413 byte(s) leaked in 3 allocation(s).

$ gcc -g -fsanitize=address -DFIXED 06_memory_leak.c -o leak && ./leak
Hello, C
done                     ← no leak report
```
With Valgrind (`sudo apt install valgrind`):
```
$ gcc -g 06_memory_leak.c -o leak && valgrind --leak-check=full ./leak
==...== LEAK SUMMARY:
==...==    definitely lost: 413 bytes in 3 blocks
```
`-g` adds debug info so the reports show file:line.

**How to avoid leaks**
- **Clear ownership**: document who frees what (e.g. "caller must free the returned string").
- **Single exit with cleanup**: use the `goto cleanup;` pattern on error paths (see 08).
- Pair functions: `x_create()` / `x_destroy()`, with `destroy` freeing every inner allocation.
- Set pointers to `NULL` after `free`. `free(NULL)` is harmless, so cleanup code can free unconditionally.
- Run tests under ASan or Valgrind regularly.

**Key points / pitfalls**
- Memory is reclaimed by the OS **when the process exits**, so short-lived programs "get away with" leaks. That doesn't make it correct, and it hides bugs that matter in long-running code.
- A leak is different from a dangling pointer: a leak is memory with no pointer to it, a dangling pointer points at no valid memory.
- Valgrind's "still reachable" means a pointer still existed at exit. That is usually less serious than "definitely lost".

**Interview Qs**
- *What is a memory leak and how do you detect it?* Allocated memory that is never freed and no longer reachable. Detect it with Valgrind, AddressSanitizer/LeakSanitizer, or code review.
- *Does the OS free leaked memory?* Yes, when the process exits. During execution it stays allocated.
- *How do you prevent leaks in functions with multiple error paths?* Use a single cleanup label (`goto cleanup`) that frees everything allocated so far.

---

## 4. Other Memory Errors and Tools

| Error | Example | Consequence |
|-------|---------|-------------|
| **Use after free** | `free(p); *p = 1;` | UB, heap corruption, security holes |
| **Double free** | `free(p); free(p);` | UB, often a crash (`free(): double free detected`) |
| **Buffer overflow** | `int *a = malloc(5 * sizeof *a); a[5] = 1;` | corrupts neighbouring heap data |
| **Uninitialised read** | `int *a = malloc(...); printf("%d", a[0]);` | garbage values |
| **Invalid free** | `int x; free(&x);` or `free(p + 1)` | UB, crash |
| **Mismatched size** | `malloc(n)` instead of `malloc(n * sizeof(int))` | allocates too little → overflow |
| **Stack overflow** | infinite recursion, huge local array | segfault |

**Tools**

| Tool | Command | Finds |
|------|---------|-------|
| AddressSanitizer | `gcc -g -fsanitize=address` | overflows, use-after-free, double free, leaks |
| UBSan | `gcc -g -fsanitize=undefined` | signed overflow, bad shifts, misaligned access… |
| Valgrind memcheck | `valgrind --leak-check=full ./prog` | leaks, invalid reads/writes, uninitialised use (no recompile needed) |
| Compiler warnings | `gcc -Wall -Wextra` | many obvious mistakes at compile time |

> Tip: while learning, compile with `gcc -Wall -Wextra -g -fsanitize=address,undefined`. It catches most of the bugs in this section at the exact line where they happen.

---

### Quick revision
- Layout (low → high): **text, rodata, data, bss, heap ↑ … ↓ stack**.
- Globals and statics live in data/BSS (zeroed if not initialised). Locals live on the stack. `malloc` memory lives on the heap.
- `malloc` gives garbage, `calloc` gives zeroes, `realloc` resizes (assign through a temp), `free` releases.
- Always check for `NULL`. Use `sizeof *p`. Every allocation needs exactly one `free`. Set `p = NULL` after `free`.
- Free nested allocations children-first. Use a single cleanup path for error handling.
- Find leaks and memory bugs with `-fsanitize=address` or `valgrind --leak-check=full`.
