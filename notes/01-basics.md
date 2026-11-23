# 01 — C Basics

Source: [GfG C Tutorial → Basics](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`

**Contents**
1. [Introduction](#1-introduction)
2. [Compilation Process](#2-compilation-process)
3. [Identifiers](#3-identifiers)
4. [Keywords](#4-keywords)
5. [Input and Output](#5-input-and-output)
6. [Variables](#6-variables)
7. [Data Types](#7-data-types)
8. [Operators](#8-operators)
9. [Conditional Statements](#9-conditional-statements)
10. [Loops](#10-loops)

---

## 1. Introduction

**What it is**
- C is a general-purpose, procedural, **mid-level** language created by **Dennis Ritchie at Bell Labs in 1972**. It was written to build the UNIX operating system.
- "Mid-level" means it has high-level constructs (functions, loops, structs) but also low-level access to memory (pointers, bitwise ops).
- It is compiled straight to machine code, so it is fast and has almost no runtime. It is used for OS kernels, embedded firmware, compilers, databases and drivers.
- Standards: K&R C → C89/C90 (ANSI) → C99 → C11 → C17 → C23.

**Structure of a C program** — [examples/01_hello.c](examples/01_hello.c)
```c
#include <stdio.h>          /* 1. preprocessor directive (header file)   */

int main(void)              /* 2. main(): where execution starts         */
{                           /* 3. body                                   */
    printf("Hello, C!\n");  /* 4. statement — every statement ends in ;  */
    return 0;               /* 5. return 0 = success to the OS           */
}
```
Output:
```
Hello, C!
```

**Key points / pitfalls**
- C is **case-sensitive**: `Main` is not `main`.
- Without `#include <stdio.h>`, calling `printf` is an error in C99 and later (implicit declaration).
- `int main(void)` and `int main(int argc, char *argv[])` are the two standard forms. `void main()` is not standard.
- Comments: `/* block */` and `// line` (the line form was added in C99).

**Interview Qs**
- *Why is C called a mid-level language?* It combines high-level features with low-level memory and hardware access.
- *Who developed C and why?* Dennis Ritchie, at Bell Labs in 1972, to rewrite UNIX.
- *Is C procedural or object-oriented?* Procedural. It has no classes or inheritance.

---

## 2. Compilation Process

**What it is** — Turning `prog.c` into an executable takes **4 stages**:

```
 prog.c ──► [Preprocessor] ──► prog.i ──► [Compiler] ──► prog.s ──► [Assembler] ──► prog.o ──► [Linker] ──► a.out
           expands #include,    pure C      C → assembly    assembly    asm → machine    object      joins .o files +
           #define, removes                                               code           file        libraries (libc)
           comments
```

| Stage | Command | Output | What happens |
|-------|---------|--------|--------------|
| Preprocess | `gcc -E prog.c -o prog.i` | `.i` | Headers pasted in, macros expanded, comments removed |
| Compile | `gcc -S prog.c` | `.s` | C translated to assembly; syntax/type errors caught here |
| Assemble | `gcc -c prog.c` | `.o` | Assembly → machine code (object file, not yet runnable) |
| Link | `gcc prog.o -o prog` | executable | Resolves calls like `printf` against libc |
| All-in-one | `gcc prog.c -o prog` | executable | |
| Keep all temps | `gcc -save-temps prog.c` | `.i .s .o` | Handy for learning |

> Try it: `gcc -E examples/01_hello.c | wc -l` prints ~750 lines. A 7-line program grows that much because the whole of `stdio.h` gets pasted in.

**Key points / pitfalls**
- **Compile error** (syntax/type) vs **linker error** (`undefined reference to 'foo'`, meaning a function was declared but never defined or linked).
- Always compile with `-Wall -Wextra`. Warnings point to real bugs.
- Use `-lm` for `<math.h>` functions on Linux: `gcc x.c -lm`.

**Interview Qs**
- *What are the stages of compilation?* Preprocessing, compilation, assembly, linking.
- *Difference between a compiler and an interpreter?* A compiler translates the whole program ahead of time into machine code. An interpreter executes the program line by line at runtime.
- *What is an object file?* Machine code for one translation unit, with unresolved references to symbols in other files.

---

## 3. Identifiers

**What it is** — Names you give to variables, functions, arrays, structs, and so on.

**Rules**
- Allowed characters: letters `a-z A-Z`, digits `0-9`, underscore `_`.
- Must **not start with a digit**.
- Cannot be a keyword. Case-sensitive. No spaces or special characters (`@ $ -`).

```c
int count, _temp, total2, studentAge;   /* valid   */
int 2total, my-var, int, float;        /* invalid */
```

**Key points / pitfalls**
- Names beginning with `_` + uppercase letter, or with `__`, are **reserved** for the implementation. Avoid them.
- Use meaningful names: `count` rather than `c`.

**Interview Qs**
- *Can an identifier start with an underscore?* Yes, but `_X` and `__x` style names are reserved, so avoid them.
- *Are `sum` and `Sum` the same?* No. C is case-sensitive.

---

## 4. Keywords

**What it is** — Reserved words with special meaning to the compiler. They cannot be used as identifiers. C89 has **32**.

| Category | Keywords |
|----------|----------|
| Data types | `int char float double void short long signed unsigned` |
| User-defined types | `struct union enum typedef` |
| Storage classes | `auto static extern register` |
| Qualifiers | `const volatile` |
| Control flow | `if else switch case default for while do break continue goto return` |
| Other | `sizeof` |

Later additions: C99 `inline restrict _Bool _Complex`, C11 `_Alignas _Atomic _Generic _Noreturn _Static_assert _Thread_local`. C23 made `bool true false nullptr` keywords.

**Interview Qs**
- *How many keywords does C have?* 32 in C89/C90 (more in later standards).
- *Is `sizeof` a function?* No. It is a compile-time **operator** and a keyword.
- *Is `main` a keyword?* No. It is just an identifier with special meaning to the runtime.

---

## 5. Input and Output

**What it is** — `<stdio.h>` provides formatted I/O: `printf` writes to stdout and `scanf` reads from stdin.

**Syntax**
```c
printf("format string", values...);
scanf("format string", &addresses...);   /* scanf needs ADDRESSES (&) */
```

**Format specifiers**

| Specifier | Type | Specifier | Type |
|-----------|------|-----------|------|
| `%d` / `%i` | int | `%c` | char |
| `%u` | unsigned int | `%s` | string (char array) |
| `%ld` / `%lld` | long / long long | `%p` | pointer address |
| `%f` | float/double (printf) | `%x` / `%o` | hex / octal |
| `%lf` | double (**scanf**) | `%zu` | size_t (`sizeof`) |
| `%e` | scientific | `%%` | literal `%` |

Width and precision: `%5d` (right-align in width 5), `%-5d` (left-align), `%.2f` (2 decimals), `%05d` (zero-pad).

**Example** — [examples/01_io.c](examples/01_io.c)
```c
int age; float height; char name[32];
printf("Enter name, age and height: ");
if (scanf("%31s %d %f", name, &age, &height) != 3) {   /* returns #items read */
    printf("Invalid input\n");
    return 1;
}
printf("Name: %s | Age: %d | Height: %.2f\n", name, age, height);
```
Input `Asha 26 5.9` → Output:
```
Name: Asha | Age: 26 | Height: 5.90
```

Other I/O functions: `getchar()/putchar()` (single char), `fgets(buf, size, stdin)` (safe line read), `puts(s)` (prints string + newline).

**Key points / pitfalls**
- Forgetting `&` in `scanf("%d", x)` → **undefined behaviour / crash**. Arrays (`name`) don't need `&`.
- `scanf("%s")` stops at whitespace and can overflow the buffer. Always give a width (`%31s`) or use `fgets`.
- Check `scanf`'s return value. It returns the number of items successfully read.
- After `scanf("%d")`, a `'\n'` stays in the input buffer. A following `scanf("%c")` reads it. Fix: `scanf(" %c", &ch)` (leading space).
- Never use `gets()`. It was removed in C11 because it cannot be used safely.

**Interview Qs**
- *Why does scanf need `&`?* It must write into your variable, so it needs the variable's address.
- *`%f` vs `%lf`?* In `printf` both print a double. In `scanf`, `%f` reads into a `float*` and `%lf` into a `double*`.
- *What does printf return?* The number of characters printed.

---

## 6. Variables

**What it is** — A named memory location that holds a value of a specific type.

**Syntax**
```c
int x;            /* declaration (+ definition: memory allocated) */
int y = 10;       /* definition with initialisation               */
int a = 1, b = 2; /* multiple                                     */
const int MAX = 100;  /* read-only after init                     */
extern int g;     /* declaration only: defined in another file    */
```

**Scope (where it's visible) and lifetime (how long it lives)**

| Kind | Declared | Scope | Lifetime | Default value |
|------|----------|-------|----------|---------------|
| Local | inside `{ }` | that block | until block ends | **garbage** |
| Global | outside all functions | whole file (+ others via `extern`) | whole program | 0 |
| Static local | `static` inside function | that block | whole program (keeps value between calls) | 0 |

```c
int g = 5;               /* global */
void f(void) {
    static int calls = 0; /* initialised once */
    int local = 0;        /* re-created each call */
    calls++; local++;
    printf("calls=%d local=%d\n", calls, local);  /* calls=1,2,3... local always 1 */
}
```

**Key points / pitfalls**
- **Declaration** tells the compiler the name and type. **Definition** also allocates memory. A variable can be declared many times but defined only once.
- An uninitialised local variable holds garbage. Reading it is UB, so always initialise.
- An inner variable with the same name **shadows** the outer one.

**Interview Qs**
- *Declaration vs definition?* A declaration announces the type. A definition allocates storage.
- *Default value of a global/static variable?* Zero.
- *Can a `const` variable be changed?* Not through its name. Modifying it via a pointer cast is UB.

---

## 7. Data Types

**What it is** — A data type tells the compiler how much memory to reserve and how to interpret the bits.

| Category | Types |
|----------|-------|
| Basic / primitive | `char`, `int`, `float`, `double`, `void` |
| Modifiers | `short`, `long`, `signed`, `unsigned` |
| Derived | arrays, pointers, functions |
| User-defined | `struct`, `union`, `enum`, `typedef` |

**Typical sizes on 64-bit Linux** (from [examples/01_datatypes.c](examples/01_datatypes.c))

| Type | Size | Range (approx.) | Specifier |
|------|------|-----------------|-----------|
| `char` | 1 | −128 … 127 (or 0 … 255) | `%c` |
| `short` | 2 | −32,768 … 32,767 | `%hd` |
| `int` | 4 | −2,147,483,648 … 2,147,483,647 | `%d` |
| `unsigned int` | 4 | 0 … 4,294,967,295 | `%u` |
| `long` | 8 | ±9.2 × 10¹⁸ | `%ld` |
| `long long` | 8 | ±9.2 × 10¹⁸ | `%lld` |
| `float` | 4 | ~6–7 significant digits | `%f` |
| `double` | 8 | ~15–16 significant digits | `%lf`/`%f` |

Sizes are **implementation-defined**. The standard only guarantees `sizeof(char)==1` and `short ≤ int ≤ long ≤ long long`. Exact limits are in `<limits.h>` and `<float.h>`. For fixed widths use `<stdint.h>` (`int32_t`, `uint8_t`, …).

**Type conversion**
- **Implicit (promotion)**: smaller types are converted up automatically, e.g. `char`→`int`, `int`→`double` in mixed expressions.
- **Explicit (cast)**: `(double)a / b`.

**Example output** — [examples/01_datatypes.c](examples/01_datatypes.c)
```
char   : 1 byte
short  : 2 bytes
int    : 4 bytes
long   : 8 bytes
float  : 4 bytes
double : 8 bytes
INT_MAX = 2147483647, INT_MIN = -2147483648
0u - 1 = 4294967295
7 / 2 = 3
(double)7 / 2 = 3.5
'A' + 1 = 66 (B)
```

**Key points / pitfalls**
- `int / int` is integer division: `7/2 == 3`. Cast one operand to get `3.5`.
- **Unsigned overflow wraps** (well-defined). **Signed overflow is UB**: never rely on `INT_MAX + 1`.
- Mixing signed and unsigned: `-1 < 1u` is **false**, because `-1` converts to a huge unsigned value.
- Floats are approximations: `0.1 + 0.2 != 0.3`. Compare with a tolerance (epsilon).
- Whether plain `char` is signed or unsigned depends on the platform.

**Interview Qs**
- *Size of int?* Platform-dependent. It is usually 4 bytes and is guaranteed to be at least 16 bits.
- *What is `void`?* "No type". It is used for functions that return nothing, for empty parameter lists, and for generic pointers (`void*`).
- *What happens on signed integer overflow?* Undefined behaviour.

---

## 8. Operators

**What it is** — Symbols that perform operations on operands.

| Type | Operators |
|------|-----------|
| Arithmetic | `+ - * / %` |
| Relational | `== != > < >= <=` (result is 0 or 1) |
| Logical | `&& \|\| !` |
| Bitwise | `& \| ^ ~ << >>` |
| Assignment | `= += -= *= /= %= &= \|= ^= <<= >>=` |
| Increment/Decrement | `++ --` (prefix/postfix) |
| Conditional (ternary) | `cond ? a : b` |
| Misc | `sizeof`, `&` (address), `*` (dereference), `,` (comma), `.` `->` (member), `(type)` cast |

**Precedence (high → low, short version)**
```
()  []  ->  .                         left→right
!  ~  ++  --  unary -  *  &  sizeof  (type)   right→left
*  /  %
+  -
<<  >>
<  <=  >  >=
==  !=
&
^
|
&&
||
?:                                    right→left
=  +=  -= ...                         right→left
,
```
Memory tip: **Unary > Arithmetic > Shift > Relational > Equality > Bitwise > Logical > Ternary > Assignment > Comma**. When in doubt, add parentheses.

**Example output** — [examples/01_operators.c](examples/01_operators.c)
```
a+b=13 a-b=7 a*b=30 a/b=3 a%b=1
-7 % 3 = -1
a>b=1 a==b=0
short-circuit avoided divide by zero
p&q=8 p|q=14 p^q=6 ~p&0xF=3 p<<1=24 p>>2=3
pre=6 post=6 i=7
max=10
2 + 3 * 4 = 14, (2 + 3) * 4 = 20
```

**Bitwise tricks** (used a lot in DSA; see `../bit_manipulation/`)
```c
x & 1          /* odd?               */
x & (x - 1)    /* clear lowest set bit; ==0 → power of two */
x | (1 << k)   /* set bit k          */
x & ~(1 << k)  /* clear bit k        */
x ^ (1 << k)   /* toggle bit k       */
(x >> k) & 1   /* read bit k         */
```

**Key points / pitfalls**
- `=` (assign) vs `==` (compare): `if (x = 5)` is always true. `-Wall` warns about it.
- `&&` and `||` **short-circuit**: the right side is skipped once the result is known.
- `%` works only on integers. The sign of the result follows the dividend (`-7 % 3 == -1`).
- `i = i++ + ++i;` → **UB** (the same variable is modified twice without a sequence point).
- Do not shift by a negative amount or by ≥ the bit width (UB). Do not left-shift negative numbers.
- `&` and `|` bind more loosely than `==`: `x & 1 == 0` means `x & (1 == 0)`. Use parentheses.

**Interview Qs**
- *`++i` vs `i++`?* Prefix increments, then yields the new value. Postfix yields the old value, then increments.
- *Swap two numbers without a temp?* `a ^= b; b ^= a; a ^= b;` (fails if `a` and `b` are the same variable).
- *Is `sizeof` evaluated at runtime?* At compile time, except for variable-length arrays.

---

## 9. Conditional Statements

**What it is** — Statements that choose which code runs based on a condition. Any **non-zero value is true** and **0 is false**.

**Syntax**
```c
if (cond) { ... }

if (cond) { ... } else { ... }

if (c1) { ... } else if (c2) { ... } else { ... }

switch (int_expr) {          /* integer/char/enum only */
case 1:  ...; break;
case 2:  ...; break;
default: ...;
}

result = cond ? a : b;       /* ternary */
```

**Example** — [examples/01_control.c](examples/01_control.c)
```c
int marks = 72;
if (marks >= 90)      printf("Grade A\n");
else if (marks >= 70) printf("Grade B\n");
else                  printf("Grade C\n");

switch (day) {          /* day = 3 */
case 1:  printf("Mon\n"); break;
case 2:  printf("Tue\n"); break;
case 3:  printf("Wed\n");
         /* fall through */
case 4:  printf("Thu (fell through)\n"); break;
default: printf("Other\n");
}
```
Output:
```
Grade B
Wed
Thu (fell through)
```

**Key points / pitfalls**
- A missing `break` in `switch` makes execution **fall through** to the next case. Sometimes this is intentional, but usually it is a bug.
- `case` labels must be **constant integer expressions**: no strings, floats or variables.
- **Dangling else**: `else` binds to the nearest `if`. Use braces.
- `if (x);` with a stray semicolon makes the body empty, so the block after it always runs.

**Interview Qs**
- *Can switch work on strings?* No. Use `if`/`strcmp` instead.
- *When is switch better than if-else?* When there are many discrete integer cases. Compilers can turn them into a jump table.
- *Is `default` mandatory?* No, and it can appear anywhere in the switch.

---

## 10. Loops

**What it is** — Loops repeat a block while a condition holds.

| Loop | Checks condition | Runs at least once? | Typical use |
|------|-----------------|---------------------|-------------|
| `for` | before each iteration | no | known number of iterations |
| `while` | before each iteration | no | unknown count, e.g. reading input |
| `do-while` | **after** each iteration | **yes** | menus, retry prompts |

**Syntax**
```c
for (init; condition; update) { ... }
while (condition) { ... }
do { ... } while (condition);   /* note the ; */
```

Jump statements:
- `break` exits the innermost loop or switch.
- `continue` skips to the next iteration.
- `goto label;` jumps anywhere in the function. Avoid it, except for error cleanup (see 08).
- `return` exits the function.

**Example output** — [examples/01_control.c](examples/01_control.c)
```
for:      1 2 3 4 5
while:    5 4 3 2 1
do-while: 10
odd < 10, stop at 7: 1 3 5 7
```
(`do-while` printed `10` even though `10 < 5` is false: the body runs once before the check.)

**Key points / pitfalls**
- Infinite loops: `for(;;)` or `while(1)`. Make sure something eventually `break`s.
- Off-by-one: `i <= n` vs `i < n` when indexing an array of size `n`.
- Never use a float as a loop counter (`for (float f = 0; f != 1.0; f += 0.1)` may never stop).
- `break` leaves only the **innermost** loop. To exit nested loops, use a flag or `goto`.
- An `unsigned` counter counting down: `for (unsigned i = n; i >= 0; i--)` never ends, because an unsigned value is always ≥ 0.

**Interview Qs**
- *`while` vs `do-while`?* `do-while` runs the body at least once.
- *`break` vs `continue`?* `break` exits the loop. `continue` skips the rest of the current iteration.
- *Entry-controlled vs exit-controlled loop?* `for` and `while` are entry-controlled. `do-while` is exit-controlled.

---

### Quick revision
- Structure: `#include` → `main()` → statements → `return 0`.
- Stages: **preprocess → compile → assemble → link** (`-E`, `-S`, `-c`).
- `scanf` needs `&`. Check its return value. Give `%s` a width.
- Integer division truncates. Signed overflow is UB. Unsigned overflow wraps.
- `=` vs `==`. `&&`/`||` short-circuit. Add parentheses around bitwise ops.
- `switch` needs `break`. `do-while` runs at least once.
