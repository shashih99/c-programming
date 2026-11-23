# 04 — Pointers

Source: [GfG C Tutorial → Pointers](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`
(Addresses in the outputs below change on every run.)

**Contents**
1. [Pointer Basics](#1-pointer-basics)
2. [Pointer Arithmetic](#2-pointer-arithmetic)
3. [Pointer to Pointer](#3-pointer-to-pointer)
4. [Function Pointers](#4-function-pointers)
5. [const with Pointers](#5-const-with-pointers)

---

## 1. Pointer Basics

**What it is**
- A pointer is a variable that **stores a memory address**, usually the address of another variable.
- Two operators:
  - `&x` is the **address-of** operator: "where does x live?"
  - `*p` is the **dereference** operator: "the value stored at address p"
- Why pointers matter: functions can modify the caller's data (02 §2), you get dynamic memory (06), arrays and strings are handled efficiently, and you can build linked lists and trees (see `../linked_list/`, `../tree/`).

**Syntax**
```c
int x = 42;
int *p = &x;      /* declare: p is a "pointer to int", initialised with x's address */
*p = 100;         /* dereference: write 100 into x                                   */
int *a, b;        /* careful: a is int*, b is a plain int                            */
```

**Memory picture**
```
       x                         p
   ┌───────┐                ┌──────────────┐
   │  42   │ ◄───────────── │ 0x7ffe...994 │
   └───────┘                └──────────────┘
   @0x7ffe...994             @0x7ffe...988
   *p == 42,  p == &x,  &p is p's own address
```

**Example** — [examples/04_pointers.c](examples/04_pointers.c)
```c
int x = 42;
int *p = &x;
*p = 100;                                   /* x is now 100 */

int *np = NULL;                             /* "points nowhere" */
if (np == NULL) printf("np is NULL, don't dereference it\n");

double d = 3.14;
void *vp = &d;                              /* generic pointer */
printf("%.2f\n", *(double *)vp);            /* convert before dereferencing */

int *heap = malloc(sizeof *heap);
free(heap);                                 /* heap is now DANGLING */
heap = NULL;                                /* reset after free */
```
Output:
```
x  = 42
&x = 0x7ffee432e994
p  = 0x7ffee432e994 (same as &x)
*p = 42 (value at that address)
after *p = 100, x = 100
&p = 0x7ffee432e988 (p has its own address)
sizeof(int*) = 8, sizeof(char*) = 8, sizeof(double*) = 8
np is NULL, don't dereference it
*(double *)vp = 3.14
*(int *)vp    = 100
*heap = 7
heap reset to NULL after free
```

**Types of "bad" pointers**

| Name | What it is | Cause | Fix |
|------|-----------|-------|-----|
| **NULL pointer** | holds 0, points nowhere | set on purpose | check `if (p)` before `*p` |
| **Wild pointer** | uninitialised, holds garbage | `int *p;` | always initialise (`= NULL`) |
| **Dangling pointer** | points to memory that is no longer valid | after `free(p)`; returning `&local`; a variable going out of scope | set `p = NULL` after free; never return a local's address |
| **void pointer** | generic pointer with no type | `void *` | cast/convert before dereferencing; no arithmetic in standard C |

**Key points / pitfalls**
- Every pointer has the **same size** on a given platform (8 bytes on 64-bit), whatever it points to. The type only tells the compiler how to *interpret* and *step through* memory.
- Dereferencing NULL, a wild pointer or a dangling pointer is **UB**. On Linux it usually crashes with a segfault.
- Print addresses with `%p` and a `(void *)` cast.
- `malloc` returns `void *`. In C it converts implicitly, so `int *p = malloc(...)` needs **no cast** (C++ does need one).
- `int *p, q;`: the `*` belongs to the variable, not the type. Declare one pointer per line.

**Interview Qs**
- *What is a pointer?* A variable that holds the address of another object.
- *NULL vs dangling vs wild pointer?* NULL points nowhere on purpose. Dangling points to freed or expired memory. Wild was never initialised.
- *Size of a pointer?* Platform-dependent: 8 bytes on 64-bit and 4 on 32-bit, the same for every data pointer type.
- *Can you dereference a `void *`?* No. Convert it to a concrete pointer type first.

---

## 2. Pointer Arithmetic

**What it is** — You can add integers to pointers, subtract pointers and compare them. Arithmetic is **scaled by the size of the pointed-to type**: `p + 1` moves `sizeof(*p)` bytes, not 1 byte.

| Operation | Meaning | Result type |
|-----------|---------|-------------|
| `p + n`, `p - n` | move n *elements* forward/back | pointer |
| `p++`, `p--`, `p += n` | same, in place | pointer |
| `q - p` | number of **elements** between them (same array only) | `ptrdiff_t` (`%td`) |
| `p < q`, `p == q` | compare positions (same array only) | int |
| `p + q`, `p * 2`, `p / 2` | **not allowed** | — |

```
int a[5]; int *p = a;

 p      p+1    p+2    p+3    p+4    p+5 (one past end: may point, never deref)
 ▼      ▼      ▼      ▼      ▼      ▼
┌──────┬──────┬──────┬──────┬──────┐
│  10  │  20  │  30  │  40  │  50  │
└──────┴──────┴──────┴──────┴──────┘
0x7d0  0x7d4  0x7d8  0x7dc  0x7e0      ← steps of 4 bytes (sizeof(int))
```

**Array ↔ pointer equivalence**
```
a[i]  ≡  *(a + i)  ≡  *(p + i)  ≡  p[i]        &a[i]  ≡  a + i
m[i][j]  ≡  *(*(m + i) + j)
```

**Example** — [examples/04_pointer_arithmetic.c](examples/04_pointer_arithmetic.c)
```c
int a[5] = {10, 20, 30, 40, 50};
int *p = a;

for (int *q = a; q < a + 5; q++)   /* pointer-style loop */
    printf("%d ", *q);

ptrdiff_t diff = &a[4] - p;         /* 4 elements, not 16 bytes */

int *r = a;
printf("%d", *r++);                 /* prints a[0], then r moves to a[1] */
printf("%d", ++*r);                 /* increments a[1] itself: 20 → 21   */

int (*row)[3] = m;                  /* pointer to a row of 3 ints */
```
Output:
```
p     = 0x7fffa29c67d0 -> 10
p + 1 = 0x7fffa29c67d4 -> 20 (moved 4 bytes)
c     = 0x7fffa29c67cc, c + 1 = 0x7fffa29c67cd (moved 1 byte)
walk with pointer: 10 20 30 40 50
end - p = 4 elements
after p += 2: *p = 30, p[1] = 40, p[-1] = 20
*r++ = 10, now *r = 20
++*r = 21 (increments the value a[1])
a[1] = 21
row[1][2] = 6, *(*(m + 1) + 2) = 6
```

**`*` and `++` combinations** (postfix `++` binds tighter than `*`, prefix is right-to-left)

| Expression | Means | Effect |
|------------|-------|--------|
| `*p++` | `*(p++)` | read `*p`, then move p |
| `(*p)++` | | increment the value, p unchanged |
| `*++p` | `*(++p)` | move p, then read |
| `++*p` | `++(*p)` | increment the value, then read |

**Key points / pitfalls**
- Arithmetic is only valid **within one array** (plus one-past-the-end). Going further, or subtracting pointers into different arrays, is UB.
- You may *form* `a + n` (one past the end) for loop bounds, but **never dereference** it.
- No arithmetic on `void *` in standard C (GCC allows it as an extension, treating it as 1 byte).
- `int *p` vs `int (*p)[3]` vs `int *p[3]`: pointer to int, pointer to an array of 3 ints, and an array of 3 pointers. Read declarations from the name outward ("spiral rule").

**Interview Qs**
- *If `int *p = 0x1000`, what is `p + 1`?* `0x1004` (with 4-byte ints).
- *What does subtracting two pointers give?* The number of elements between them, as `ptrdiff_t`.
- *Difference between `*p++` and `(*p)++`?* The first moves the pointer. The second increments the pointed-to value.
- *Are arrays and pointers the same?* No. An array is a block of storage. It **decays** to a pointer in most expressions, but `sizeof` and `&` treat it differently, and an array name can't be reassigned.

---

## 3. Pointer to Pointer

**What it is** — A **double pointer** (`int **pp`) stores the address of another pointer. Common uses:
1. A function that must **change which address the caller's pointer holds** (allocate, reset to NULL, insert at the head of a linked list).
2. **Arrays of pointers**: `char *argv[]`, arrays of strings, dynamically allocated 2-D arrays.

**Syntax and picture**
```c
int x = 5;
int *p = &x;
int **pp = &p;          /* **pp == *p == x */
```
```
     pp                  p                  x
┌──────────┐       ┌──────────┐       ┌──────────┐
│ &p       │ ────► │ &x       │ ────► │    5     │
└──────────┘       └──────────┘       └──────────┘
*pp == p           **pp == x
```

**Example** — [examples/04_double_pointer.c](examples/04_double_pointer.c)
```c
/* WRONG: p is a copy. Caller's pointer stays NULL and the block LEAKS */
void alloc_wrong(int *p, int n) { p = malloc(n * sizeof *p); }

/* RIGHT: pass the ADDRESS of the caller's pointer */
int alloc_right(int **pp, int n)
{
    *pp = malloc(n * sizeof **pp);
    return *pp != NULL;
}

int *arr = NULL;
alloc_wrong(arr, 3);       /* arr still NULL */
alloc_right(&arr, 3);      /* arr now points to 3 ints */

const char *names[] = {"Ada", "Linus", "Dennis"};
const char **it = names;   /* *it = string, **it = its first char */
```
Output:
```
x = 5, *p = 5, **pp = 5
&x = 0x7ffdb0c4d39c, p = 0x7ffdb0c4d39c, *pp = 0x7ffdb0c4d39c
after **pp = 50, x = 50
after alloc_wrong: arr is still NULL
after alloc_right: 11 22 33
names[0] = Ada (first char A)
names[1] = Linus (first char L)
names[2] = Dennis (first char D)
```
> Compiling this file with `-fsanitize=address` reports `detected memory leaks ... 12 byte(s)`. That leak is the block `alloc_wrong` lost. Try it: it is a good way to see that the bug is real.

**Key points / pitfalls**
- Rule of thumb: **to change a `T` inside a function, pass a `T *`.** To change an `int *`, pass an `int **`.
- Linked lists: `void push(struct Node **head, int v)` updates the caller's head. Compare with `../linked_list/`.
- `int **` is **not** the same as `int[R][C]` (see 03 §2). An `int **` points to an array of row pointers.
- Each extra level of `*` makes code harder to read. Use a `typedef`, or return the new pointer instead (`arr = make_array(3);`).

**Interview Qs**
- *When do you need a double pointer?* When a function must modify the caller's pointer itself, or to handle arrays of pointers.
- *What is `argv`'s type?* `char **` (equivalently `char *argv[]`).
- *How do you allocate a 2-D array dynamically?* `malloc` an array of row pointers (`int **`) and then each row, or allocate one block of `R*C` and index it with `i*C+j`.

---

## 4. Function Pointers

**What it is** — A pointer that stores the **address of a function**. Calling through it lets you choose behaviour at runtime: **callbacks**, `qsort` comparators, dispatch tables, and plugin-style designs.

**Syntax**
```c
int add(int a, int b);

int (*fp)(int, int) = add;        /* parentheses around *fp are REQUIRED   */
                                  /* int *fp(int,int) = a function returning int* */
fp(2, 3);  (*fp)(2, 3);           /* both call add                         */

typedef int (*binop)(int, int);   /* typedef makes it readable             */
binop ops[] = {add, sub, mul};    /* array of function pointers            */
```

**Example** — [examples/04_function_pointers.c](examples/04_function_pointers.c)
```c
int apply(binop f, int a, int b) { return f(a, b); }   /* callback */

int cmp_asc(const void *x, const void *y)              /* qsort comparator */
{
    int a = *(const int *)x, b = *(const int *)y;
    return (a > b) - (a < b);         /* -1, 0, 1 without the overflow risk of a - b */
}

binop ops[] = {add, sub, mul};
for (int i = 0; i < 3; i++)
    printf("9 %c 3 = %d\n", "+-*"[i], ops[i](9, 3));

qsort(v, 5, sizeof v[0], cmp_asc);
```
Output:
```
fp(2, 3)        = 5
(*fp)(2, 3)     = 5
apply(mul,4,5)  = 20
9 + 3 = 12
9 - 3 = 6
9 * 3 = 27
qsort asc : -2 1 5 7 9
qsort desc: 9 7 5 1 -2
```

**`qsort` signature**
```c
void qsort(void *base, size_t count, size_t size,
           int (*compar)(const void *, const void *));
/* compar returns <0 if a before b, 0 if equal, >0 if a after b */
```

**Key points / pitfalls**
- A function name decays to a pointer to that function, just as an array name decays: `fp = add` and `fp = &add` are the same.
- The pointer's type must match the function's signature exactly. Calling through a mismatched type is UB.
- Comparator pitfall: `return a - b;` can **overflow** for large values of opposite sign. Use `(a > b) - (a < b)`.
- Function pointers enable "OOP in C": a struct holding function pointers works like a vtable (e.g. the Linux kernel's `file_operations`).
- `void (*signal(int, void (*)(int)))(int);`: complex declarations become readable with a `typedef`.

**Interview Qs**
- *Declare a pointer to a function taking two ints and returning int.* `int (*fp)(int, int);`
- *What is a callback?* A function passed as an argument to be called later, e.g. a `qsort` comparator or an event handler.
- *Difference between `int *f(int)` and `int (*f)(int)`?* The first is a function returning `int *`. The second is a pointer to a function returning `int`.

---

## 5. const with Pointers

**What it is** — `const` can protect **the data**, **the pointer**, or both. Read the declaration **right to left**:

| Declaration | Read as | Change `*p`? | Change `p`? |
|-------------|---------|--------------|-------------|
| `const int *p` (= `int const *p`) | p is a pointer to a const int | ✗ | ✓ |
| `int *const p` | p is a const pointer to an int | ✓ | ✗ |
| `const int *const p` | p is a const pointer to a const int | ✗ | ✗ |

**Example** — [examples/04_const_pointers.c](examples/04_const_pointers.c)
```c
const int *p1 = &a;   /* *p1 = 10; error */  p1 = &b;   /* OK */
int *const p2 = &a;   *p2 = 10;   /* OK */   /* p2 = &b; error */
const int *const p3 = &b;          /* both changes are errors */
```
Output:
```
p1 -> 2
p2 -> 10 (a = 10)
p3 -> 2
```

**Key points / pitfalls**
- Use `const T *` for function parameters the function only reads (`size_t strlen(const char *s)`). It documents intent and catches accidental writes.
- `int *` → `const int *` converts implicitly (adding a promise is safe). The reverse needs a cast and is a code smell.
- `const` means "read-only through this name", not "the value never changes": another non-const pointer may still modify it.
- Casting away `const` from an object that was **defined** `const` and then writing to it is UB.

**Interview Qs**
- *`const int *p` vs `int *const p`?* The first protects the pointed-to data. The second protects the pointer itself.
- *Why does `strcpy` take `const char *src`?* It promises not to modify the source.

---

### Quick revision
- `&x` gives an address and `*p` gives the value at an address. All data pointers are 8 bytes on 64-bit.
- Initialise pointers (to NULL or a valid address). After `free`, set to NULL. Never return `&local`.
- `p + 1` moves `sizeof(*p)` bytes. `q - p` counts elements. Stay inside the array.
- `a[i] ≡ *(a+i)`. `*p++` moves the pointer, while `(*p)++` changes the value.
- To change a caller's `T`, pass `T *`. So to change a caller's pointer, pass `T **`.
- Function pointer: `int (*fp)(int,int)`. Use a `typedef`. Callbacks and `qsort` comparators use them.
- `const int *p` protects the data, `int *const p` protects the pointer. Read right to left.
