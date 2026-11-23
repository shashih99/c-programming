# 05 — User Defined Data Types

Source: [GfG C Tutorial → User Defined Data Types](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`
(Sizes and offsets below are from x86-64 Linux with GCC 12.)

**Contents**
1. [Structures](#1-structures)
2. [Structure Alignment, Padding and Packing](#2-structure-alignment-padding-and-packing)
3. [Unions](#3-unions)
4. [Enumerations](#4-enumerations)
5. [Bit Fields](#5-bit-fields)
6. [typedef](#6-typedef)

---

## 1. Structures

**What it is**
- A `struct` groups **related variables of different types** under one name, e.g. a student's id, name and GPA.
- Each member has **its own storage**. They are laid out in declaration order, possibly with padding in between (§2).
- Structs are the building block for records and data structures: linked-list nodes, tree nodes, and so on.

**Syntax**
```c
struct Point {              /* definition: "struct Point" is the type      */
    int x;
    int y;
};                          /* ← semicolon required                       */

struct Point p1 = {1, 2};               /* positional init                 */
struct Point p2 = {.y = 10, .x = 6};    /* designated init (C99), any order */
struct Point p3 = {0};                  /* all members zero                 */

p1.x = 5;                   /* .  → access via a struct variable          */
struct Point *pp = &p1;
pp->y = 7;                  /* -> → access via a pointer; same as (*pp).y */
```

**Example** — [examples/05_structs.c](examples/05_structs.c)
```c
typedef struct {
    int id;
    char name[20];
    float gpa;
    struct Point home;                         /* nested struct */
} Student;

void print_student(const Student *s)           /* pass a pointer: no copy */
{
    printf("  #%d %-6s gpa=%.1f home=(%d,%d)\n",
           s->id, s->name, s->gpa, s->home.x, s->home.y);
}

struct Point midpoint(struct Point a, struct Point b)   /* by value in, by value out */
{
    struct Point m = { (a.x + b.x) / 2, (a.y + b.y) / 2 };
    return m;
}

struct Point copy = p1;                        /* assignment copies ALL members */
strcpy(s.name, "Asha K");                      /* char array member: use strcpy */

Student cls[] = {
    s,
    {2, "Ravi", 7.4f, {0, 0}},
    {.id = 3, .name = "Meena", .gpa = 9.1f},   /* unlisted members → 0 */
};
```
Output:
```
p1 = (1, 2), p2 = (6, 10)
midpoint = (3, 6)
p1.x = 1, copy.x = 99 (independent copies)
s.name = Asha, ps->name = Asha, (*ps).name = Asha
class of 3:
  #1 Asha K gpa=8.7 home=(3,4)
  #2 Ravi   gpa=7.4 home=(0,0)
  #3 Meena  gpa=9.1 home=(0,0)
sizeof(struct Point) = 8, sizeof(Student) = 36
```

**What you can and can't do with structs**

| Operation | Allowed? |
|-----------|----------|
| Assign `a = b` | ✓ copies every member, including arrays inside |
| Pass to / return from a function | ✓ by value (copies), or pass a pointer |
| Compare `a == b` | ✗ compare member by member (`memcmp` is unreliable because of padding) |
| Assign a string to a `char[]` member (`s.name = "x"`) | ✗ use `strcpy`/`snprintf` |
| Contain itself (`struct Node next;`) | ✗ infinite size |
| Contain a pointer to itself (`struct Node *next;`) | ✓ **self-referential struct**, used for linked lists and trees |

**Self-referential struct** (see `../linked_list/`, `../tree/`)
```c
struct Node {
    int data;
    struct Node *next;      /* pointer to the same type is fine */
};
```

**Key points / pitfalls**
- Defining the struct type allocates **no memory**. Memory is allocated only when you create a variable of that type.
- Passing big structs by value copies them every time. Pass `const T *` when the function only reads.
- `p->x` is just shorthand for `(*p).x`. `*p.x` means `*(p.x)` and is wrong.
- `sizeof(struct)` can be **more** than the sum of the member sizes because of padding (§2). Always use `sizeof`, never add the sizes by hand.
- Unlike C++, C structs cannot contain functions. They **can** contain function pointers (04 §4).
- A struct with a flexible array member (`int data[];` as the last member) gets its storage via `malloc`. See 06.

**Interview Qs**
- *`.` vs `->`?* `.` is used on a struct variable and `->` on a pointer to a struct.
- *Can structs be compared with `==`?* No. Compare member by member.
- *What is a self-referential structure?* A struct that contains a pointer to its own type, e.g. a linked-list node.
- *Struct in C vs C++?* In C a struct has no member functions or access specifiers, and you need `struct` (or a typedef) when naming the type.

---

## 2. Structure Alignment, Padding and Packing

**What it is**
- CPUs read memory fastest (and some CPUs *only*) when a value sits at an address that is a **multiple of its size** (its *alignment*): `int` at multiples of 4, `double` at multiples of 8.
- The compiler inserts unused **padding bytes** between members, and at the end, so that every member is aligned.

**Rules**
1. Each member starts at an offset that is a multiple of **its own alignment**.
2. The struct's total size is a multiple of its **largest member's alignment**, so arrays of the struct stay aligned. This is called tail padding.

**Example** — [examples/05_padding.c](examples/05_padding.c)
```c
struct Bad  { char a; int b; char c; double d; };      /* poorly ordered */
struct Good { double d; int b; char a; char c; };      /* largest first  */
struct __attribute__((packed)) Packed { char a; int b; char c; double d; };
```
Output:
```
struct Bad    : sizeof = 24, align = 8
  a        offset  0, size 1
  b        offset  4, size 4
  c        offset  8, size 1
  d        offset 16, size 8
struct Good   : sizeof = 16, align = 8
  d        offset  0, size 8
  b        offset  8, size 4
  a        offset 12, size 1
  c        offset 13, size 1
struct Packed : sizeof = 14
  a        offset  0, size 1
  b        offset  1, size 4
  c        offset  5, size 1
  d        offset  6, size 8
```

**Layout picture** (each cell = 1 byte, `.` = padding)
```
struct Bad (24 bytes)
 0       4       8              16                      24
 [a . . .][b b b b][c . . . . . . .][d d d d d d d d]

struct Good (16 bytes)  — same members, 8 bytes saved
 0               8       12  14  16
 [d d d d d d d d][b b b b][a][c][. .]

struct Packed (14 bytes) — no padding, but b and d are misaligned
 [a][b b b b][c][d d d d d d d d]
```

**Tools**
- `offsetof(type, member)` from `<stddef.h>` gives a member's byte offset.
- `_Alignof(type)` (C11; `alignof` with `<stdalign.h>`) gives a type's alignment.
- `_Alignas(n)` forces a stricter alignment on a variable or member.
- `__attribute__((packed))` (GCC/Clang) or `#pragma pack(1)` (GCC, MSVC) removes padding.

**Key points / pitfalls**
- **Order members from largest to smallest** to minimise padding. This is free memory savings, which matters in large arrays of structs.
- Packing saves space but misaligned access is **slower** on x86 and can **crash** on some ARM, SPARC and older CPUs. Taking the address of a packed member is risky. Use packing only for wire or file formats and hardware registers.
- Padding bytes have unspecified values, so `memcmp` on two structs may report "different" even when all members are equal.
- Writing raw structs to files or sockets (`fwrite(&s, sizeof s, ...)`) is **not portable**. Padding, endianness and type sizes differ between platforms. Serialise field by field instead (see 07).

**Interview Qs**
- *What is structure padding and why does it exist?* Extra bytes the compiler inserts so members are aligned for efficient (or legal) CPU access.
- *`sizeof(struct {char c; int i;})`?* Usually 8: 1 + 3 padding + 4.
- *How do you reduce padding?* Reorder members from largest to smallest, or pack the struct (with performance and portability trade-offs).
- *What does `#pragma pack(1)` do?* It sets the maximum alignment to 1 byte, which removes all padding.

---

## 3. Unions

**What it is**
- A `union` looks like a struct, but **all members share the same memory** and start at the same address.
- Its size equals its **largest member** (plus alignment padding). Only **one member holds a meaningful value at a time**: the one written last.
- Uses: saving memory when only one of several fields is needed, **tagged unions** (variant types), and viewing the same bytes in different ways (type punning).

**Struct vs union**
```
struct S { int i; float f; char str[12]; };   → 20 bytes, each member separate
 [i i i i][f f f f][s s s s s s s s s s s s]

union  U { int i; float f; char str[12]; };   → 12 bytes, all overlapping
 [i i i i . . . . . . . . ]
 [f f f f . . . . . . . . ]
 [s s s s s s s s s s s s]
```

| | struct | union |
|-|--------|-------|
| Memory | sum of members (+ padding) | largest member (+ padding) |
| Members valid at once | all | one (last written) |
| Writing one member | doesn't affect others | overwrites the others |

**Example** — [examples/05_unions.c](examples/05_unions.c)
```c
union Data { int i; float f; char str[12]; };

d.i = 42;
d.f = 2.5f;                   /* overwrites the same bytes: d.i is now garbage-looking */

union Word { uint32_t value; uint8_t bytes[4]; };   /* inspect bytes → endianness */
union Word w = { .value = 0x11223344 };

typedef struct {              /* TAGGED UNION: the enum says which member is valid */
    ShapeKind kind;
    union {
        struct { double r; } circle;
        struct { double w, h; } rect;
    };                        /* anonymous union (C11): access s.circle directly */
} Shape;

double area(const Shape *s) {
    switch (s->kind) {
    case SHAPE_CIRCLE: return 3.14159 * s->circle.r * s->circle.r;
    case SHAPE_RECT:   return s->rect.w * s->rect.h;
    }
    return 0;
}
```
Output:
```
sizeof(union Data) = 12 (largest member = 12)
d.i = 42
d.f = 2.5, d.i now = 1075838976 (reinterpreted bits)
&d.i = 0x7fff...60b0, &d.f = 0x7fff...60b0, &d.str = 0x7fff...60b0 (all same)
bytes of 0x11223344: 44 33 22 11 -> little-endian
shape 0 area = 3.14
shape 1 area = 12.00
sizeof(Shape) = 24
```
(`1075838976` is `0x40200000`, the IEEE-754 bit pattern of `2.5f`.)

**Key points / pitfalls**
- Reading a member other than the one last written ("type punning") is **allowed in C** (C99 TC3 and later): the bytes are reinterpreted. In C++ it is UB. The result depends on endianness and representation.
- Always track which member is active, usually with an `enum` tag. Reading the wrong member gives garbage.
- Only the **first** member can be set with a plain `{...}` initialiser. Use designated initialisers (`{.f = 2.5f}`) for the others.
- Unions are common in protocol parsers, interpreters (variant values) and embedded register maps.

**Interview Qs**
- *Size of a union?* The size of its largest member, rounded up to the union's alignment.
- *Struct vs union?* A struct gives every member its own storage. A union's members overlap, and only one is valid at a time.
- *How do you check endianness in C?* Store a multi-byte integer and look at its first byte through a `char` pointer or a union.
- *What is a tagged union?* A struct holding an enum tag plus a union, where the tag records which union member is active.

---

## 4. Enumerations

**What it is** — An `enum` defines a set of **named integer constants**. It makes code readable (`RED` instead of `0`) and lets the compiler help with `switch` checks.

**Syntax**
```c
enum Color { RED, GREEN, BLUE };                   /* 0, 1, 2 — auto-increment from 0 */
enum Level { LOW = 10, MEDIUM = 20, HIGH };        /* HIGH = 21 — continues from last  */
typedef enum { MON = 1, TUE, WED } Day;            /* typedef'd: write "Day d = WED;"  */

enum Perm { PERM_READ = 1 << 0, PERM_WRITE = 1 << 1, PERM_EXEC = 1 << 2 };  /* bit flags */
```

**Example** — [examples/05_enums.c](examples/05_enums.c)
```c
const char *color_name(enum Color c)
{
    switch (c) {                       /* -Wall warns if you forget a case */
    case RED:   return "red";
    case GREEN: return "green";
    case BLUE:  return "blue";
    }
    return "?";
}

int perms = PERM_READ | PERM_WRITE;    /* combine flags */
if (perms & PERM_WRITE) ...            /* test a flag   */
perms &= ~PERM_WRITE;                  /* remove a flag */
```
Output:
```
RED=0 GREEN=1 BLUE=2
LOW=10 MEDIUM=20 HIGH=21
color 0 = red
color 1 = green
color 2 = blue
WED = 3, weekend? no
perms = 3, can write? yes, can exec? no
after removing write: perms = 1
sizeof(enum Color) = 4
```

**enum vs `#define` vs `const int`**

| | `enum` | `#define` | `const int` |
|-|--------|-----------|-------------|
| Handled by | compiler | preprocessor | compiler |
| Has a type / scope | yes (type is int-compatible) | no, plain text | yes |
| Visible in the debugger | yes | no | yes |
| Usable as `case` label / array size | yes | yes | **no** in C (not a constant expression) |
| Groups related values | yes | no | no |
| Auto-numbering | yes | no | no |

**Key points / pitfalls**
- Enum constants are plain `int`s. C does **not** stop you assigning any integer to an enum variable (`enum Color c = 42;` compiles).
- Two enums in the same scope cannot share a constant name. Prefix names to avoid clashes (`COLOR_RED`, `SHAPE_CIRCLE`).
- Values can repeat (`A = 1, B = 1`) and can be negative.
- Common trick: add a final `COUNT` member to get the number of values (`enum { A, B, C, COLOR_COUNT };` makes `COLOR_COUNT == 3`).
- Leave out `default:` in a `switch` over an enum, so `-Wall` (`-Wswitch`) warns when you add a new value and forget to handle it.

**Interview Qs**
- *Default value of the first enum constant?* 0. Each later constant is the previous one + 1.
- *Why use enum over `#define`?* Type and scope, debugger visibility, auto-numbering, and grouping of related values.
- *Size of an enum?* Implementation-defined but compatible with an integer type. It is usually 4 bytes.

---

## 5. Bit Fields

**What it is** — Struct members with an **explicit width in bits**. Several small values can be packed into one machine word. Used for flags, hardware registers and compact protocol headers.

**Syntax**
```c
struct DateBits {
    unsigned int day   : 5;   /* 0..31   */
    unsigned int month : 4;   /* 0..15   */
    unsigned int year  : 12;  /* 0..4095 */
};                            /* 21 bits → fits in one 4-byte unsigned int */
```
An n-bit unsigned field holds values from 0 to 2ⁿ − 1.

**Example** — [examples/05_bitfields.c](examples/05_bitfields.c)
```c
struct DateBits d = {23, 11, 2026};

struct Flags { unsigned is_open : 1; unsigned is_dirty : 1; unsigned mode : 2; };
struct Flags f = {0};
f.is_open = 1;
f.mode = 3;

unsigned v = 5;
f.mode = v;          /* 2 bits only: 101 → 01 = 1 (silently truncated) */
```
Output:
```
date = 23/11/2026
sizeof(DateNormal) = 12, sizeof(DateBits) = 4
flags: open=1 dirty=0 mode=3, sizeof = 4
f.mode = 5 stored as 1
```

**Key points / pitfalls**
- **You cannot take the address** of a bit field (`&f.mode` is an error), and you cannot make an array of bit fields.
- Out-of-range values are **silently truncated** to the low bits. GCC warns (`-Woverflow`) only when you assign a constant.
- Allowed types: `unsigned int`, `signed int`, `_Bool` (and others as an implementation extension). Plain `int` bit fields may be signed or unsigned depending on the compiler, so always write `unsigned` or `signed` explicitly.
- Bit order inside the word, and whether a field may straddle storage units, are **implementation-defined**. Don't rely on bit fields to match an exact binary layout across compilers. For portable bit layouts use masks and shifts (see 01 §8).
- A zero-width unnamed field (`unsigned : 0;`) forces the next field to start in a new storage unit.

**Interview Qs**
- *What are bit fields used for?* Packing flags and small integers to save memory, and mapping hardware registers.
- *Can you take the address of a bit field?* No, because it may not start on a byte boundary.
- *Are bit fields portable?* Their layout (bit order, padding) is implementation-defined, so not for exact binary formats.

---

## 6. typedef

**What it is** — `typedef` creates an **alias** (a new name) for an existing type. It creates no new type and allocates no memory.

```c
typedef unsigned long ulong;                 /* simple alias              */
typedef struct Point Point;                  /* drop the "struct" keyword  */
typedef struct { int x, y; } Vec2;           /* anonymous struct + alias   */
typedef struct Node { int v; struct Node *next; } Node;  /* self-referential: use the tag inside */
typedef int (*Comparator)(const void *, const void *);   /* function pointer (04 §4) */
typedef int Matrix3[3][3];                   /* array type                 */
```

**Key points / pitfalls**
- Inside a self-referential struct you must use `struct Node *`, because the alias `Node` isn't defined until the typedef ends.
- `typedef` vs `#define`: in `typedef char *Str; Str a, b;` both are `char *`. In `#define Str char *` followed by `Str a, b;`, only `a` is a pointer.
- Don't hide pointers behind typedefs (`typedef struct X *XPtr;`) unless the type is meant to be opaque. It makes ownership and `const` confusing.
- Names ending in `_t` are reserved by POSIX. Avoid them for your own types in POSIX code.

**Interview Qs**
- *`typedef` vs `#define`?* `typedef` is handled by the compiler and respects types (it works correctly for pointers). `#define` is plain text substitution.
- *Does typedef create a new type?* No, only a new name for an existing type.

---

### Quick revision
- `struct`: members stored separately, in order. Use `.` on variables and `->` on pointers. Assignment copies, `==` is not allowed.
- Padding aligns members. Order them largest → smallest. Inspect with `offsetof`/`_Alignof`. `packed` removes padding at a cost.
- `union`: members overlap, size = largest member, one valid at a time. Pair it with an enum tag.
- `enum`: named int constants starting at 0 and auto-incrementing. Good for `switch` and bit flags.
- Bit fields: `unsigned x : n;` packs values into bits. No `&`. Values are truncated. Layout is implementation-defined.
- `typedef` is an alias only. Use the struct tag for self-reference. It is safer than `#define` for types.
