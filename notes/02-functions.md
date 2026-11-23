# 02 — Functions

Source: [GfG C Tutorial → Functions](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`

**Contents**
1. [Functions](#1-functions)
2. [Parameter Passing Techniques](#2-parameter-passing-techniques)
3. [Main Function](#3-main-function)
4. [Recursion](#4-recursion)
5. [Inline Function](#5-inline-function)
6. [Nested Functions](#6-nested-functions)

---

## 1. Functions

**What it is**
- A function is a named block of code that does one job. You write it once and call it many times.
- Benefits: reuse, readability, easier testing and debugging, and a big problem split into small ones.
- Two kinds: **library functions** (`printf`, `strlen`, `sqrt`) and **user-defined functions**.

**Three parts of a function**
```c
int add(int a, int b);          /* 1. DECLARATION (prototype): name, return type, param types */

int add(int a, int b)           /* 2. DEFINITION: the actual body                            */
{
    return a + b;
}

int s = add(3, 4);              /* 3. CALL: control jumps to add, comes back with 7          */
```

**Terminology**
- **Parameters** (formal parameters) are the variables in the definition: `a`, `b`.
- **Arguments** (actual parameters) are the values passed in the call: `3`, `4`.
- **Return type** is the type of value sent back. Use `void` if nothing is returned.
- **Signature** = name + parameter types (+ return type).

**Example** — [examples/02_functions.c](examples/02_functions.c)
```c
int add(int a, int b);
void greet(void);
double average(const int arr[], int n);

int main(void)
{
    greet();
    printf("add(3, 4) = %d\n", add(3, 4));
    int nums[] = {4, 8, 15, 16, 23, 42};
    printf("average = %.2f\n", average(nums, 6));
    return 0;
}

double average(const int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return (double)sum / n;
}
```
Output:
```
Hello from greet()
add(3, 4) = 7
average = 18.00
```

**What happens on a call (the call stack)**
```
main() calls add(3, 4)
   ┌──────────────┐
   │ add: a=3,b=4 │  ← new stack frame (params, locals, return address)
   ├──────────────┤
   │ main: s=?    │
   └──────────────┘
add returns 7 → its frame is popped → main continues with s = 7
```

**Key points / pitfalls**
- If a function is **defined after `main`**, you must declare a prototype before calling it. Otherwise C99+ gives an error.
- `int f();` and `int f(void);` mean different things before C23. `()` means "unspecified parameters" and `(void)` means "no parameters". Use `(void)`.
- A non-void function that falls off the end without `return` gives a garbage result (UB if the caller uses it). `-Wall` warns about this.
- A function can return **only one value**. To return more, use pointer parameters (see §2) or return a struct.
- **Never return the address of a local variable.** The local dies when the function returns, which leaves a dangling pointer.
- C has **no function overloading** and **no default arguments**.

**Interview Qs**
- *Declaration vs definition of a function?* The declaration (prototype) gives the name, return type and parameter types. The definition contains the body.
- *Can a function return more than one value?* Not directly. Use pointer parameters, a struct, or an array via a pointer.
- *Does C support function overloading?* No. Every function name must be unique. C11's `_Generic` can imitate overloading.

---

## 2. Parameter Passing Techniques

**What it is** — C has **only pass by value**: the function always receives a *copy* of each argument. "Pass by reference" is simulated by passing a **pointer** (a copy of the address).

| Technique | How | Can the function change the caller's variable? |
|-----------|-----|---------------------------------------|
| Pass by value | `f(x)` → `void f(int a)` | **No**, it works on a copy |
| Pass by pointer ("by reference") | `f(&x)` → `void f(int *a)` | **Yes**, through `*a` |
| Arrays | `f(arr)` → `void f(int arr[])` | **Yes**. The array decays to a pointer to its first element |

**Example** — [examples/02_param_passing.c](examples/02_param_passing.c)
```c
void swap_by_value(int a, int b)     { int t = a; a = b; b = t; }      /* swaps copies */
void swap_by_pointer(int *a, int *b) { int t = *a; *a = *b; *b = t; }  /* swaps originals */

void min_max(const int arr[], int n, int *min, int *max)   /* "returns" two values */
{
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

int x = 1, y = 2;
swap_by_value(x, y);      /* x=1 y=2 (unchanged) */
swap_by_pointer(&x, &y);  /* x=2 y=1 */
```
Output:
```
  inside swap_by_value: a=2 b=1
after swap_by_value:   x=1 y=2
after swap_by_pointer: x=2 y=1
after double_all: 2 4 6
min=-3 max=12
```

**Memory picture for `swap_by_pointer(&x, &y)`**
```
main's frame              swap's frame
 x [ 1 ] @0x100  ◄─────── a [0x100]
 y [ 2 ] @0x104  ◄─────── b [0x104]
*a = *b writes through the address → main's x changes
```

**Key points / pitfalls**
- Arrays are never copied. The function gets a pointer, so `sizeof(arr)` inside it gives the **pointer size (8)**, not the array size. Always pass the length `n` separately.
- `int arr[]`, `int arr[10]` and `int *arr` as parameters are all **the same thing**: a pointer.
- Use `const` (`const int arr[]`, `const char *s`) when the function only reads. This documents intent and the compiler enforces it.
- Structs **are** copied when passed by value, which is slow for big structs. Pass `const struct S *` instead.
- Passing a pointer does not let you change *which address* the caller's pointer holds. For that you need a pointer to a pointer (`int **`), covered in 04-pointers.

**Interview Qs**
- *Does C support pass by reference?* No, only pass by value. Passing a pointer by value has the same effect.
- *Why does `sizeof(arr)` inside a function give 8?* The array has decayed to a pointer, and a pointer is 8 bytes on 64-bit.
- *Write a swap function.* `void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }`

---

## 3. Main Function

**What it is** — `main` is the program's **entry point**. The startup code (crt0) calls it after setting up the environment. Its return value becomes the process's **exit status**.

**Standard forms**
```c
int main(void) { ... }                        /* no command-line args */
int main(int argc, char *argv[]) { ... }      /* with args (char **argv is the same) */
```
- `argc` is the argument count. It is always ≥ 1 because the program name counts.
- `argv[0]` is the program name, `argv[1] … argv[argc-1]` are the arguments, and `argv[argc]` is `NULL`.
- All arguments are **strings**. Convert them with `atoi`, `atol`, `strtol`, `strtod`.

**Example** — [examples/02_main_args.c](examples/02_main_args.c)
```c
int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    if (argc < 3) {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("sum = %d\n", atoi(argv[1]) + atoi(argv[2]));
    return EXIT_SUCCESS;
}
```
```
$ ./prog 10 32               $ ./prog
argc = 3                     argc = 1
argv[0] = "./prog"           argv[0] = "./prog"
argv[1] = "10"               usage: ./prog <num1> <num2>
argv[2] = "32"               $ echo $?
sum = 42                     1
$ echo $?
0
```

**Key points / pitfalls**
- Return `0` / `EXIT_SUCCESS` on success and non-zero / `EXIT_FAILURE` on error. Shell scripts and `make` rely on this.
- If `main` reaches `}` without `return`, it returns 0 implicitly (C99+). This applies **only** to `main`.
- `void main()` is non-standard and the exit status is undefined. Don't use it.
- `atoi("abc")` silently returns 0. Use `strtol` with an `endptr` when you need to detect bad input.
- `exit(code)` from anywhere ends the program, the same as returning from `main`, and flushes stdio buffers.

**Interview Qs**
- *What does main's return value mean?* It is the exit status passed to the OS or shell. 0 means success.
- *Can a program have no main?* Not a normal hosted program. Freestanding or embedded code and special linker tricks are exceptions.
- *What is `argv[argc]`?* Always `NULL`.

---

## 4. Recursion

**What it is** — A function that **calls itself** to solve a smaller instance of the same problem. Every recursive function needs:
1. A **base case** that stops the recursion.
2. A **recursive case** that moves toward the base case.

**Syntax**
```c
type f(params) {
    if (base_condition) return base_value;   /* stop */
    return ... f(smaller_input) ...;          /* shrink */
}
```

**How `factorial(4)` runs on the stack**
```
factorial(4) = 4 * factorial(3)
                   factorial(3) = 3 * factorial(2)
                                      factorial(2) = 2 * factorial(1)
                                                         factorial(1) = 1   ← base case
                                      = 2 * 1 = 2
                   = 3 * 2 = 6
= 4 * 6 = 24
```

**Example** — [examples/02_recursion.c](examples/02_recursion.c)
```c
unsigned long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

unsigned long long fact_tail(int n, unsigned long long acc) {   /* tail recursive */
    if (n <= 1) return acc;
    return fact_tail(n - 1, acc * n);    /* nothing left to do after the call */
}

int fib(int n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); }   /* O(2^n)! */

void print_down_up(int n) {
    if (n == 0) return;
    printf("%d ", n);        /* before the call: runs going DOWN */
    print_down_up(n - 1);
    printf("%d ", n);        /* after the call: runs coming back UP */
}
```
Output:
```
factorial(5)      = 120
fact_tail(20, 1)  = 2432902008176640000
fib(10)           = 55
fib_iter(40)      = 102334155
sum_digits(1234)  = 10
print_down_up(3)  : 3 2 1 1 2 3
```

**Types of recursion**

| Type | Meaning | Example |
|------|---------|---------|
| Direct | f calls f | factorial |
| Indirect | f calls g, g calls f | `isEven` ↔ `isOdd` |
| Tail | recursive call is the **last** operation | `fact_tail` — compiler can turn it into a loop at `-O2` |
| Head / non-tail | work remains after the call returns | `factorial` (has `n * …` pending) |
| Tree | more than one recursive call | `fib`, tree traversals |

**Recursion vs iteration**

| | Recursion | Iteration |
|-|-----------|-----------|
| Code | short, natural for trees, divide & conquer, backtracking | can be longer |
| Memory | O(depth) stack frames | O(1) usually |
| Risk | **stack overflow** if too deep or no base case | infinite loop |
| Speed | function-call overhead | faster |

**Key points / pitfalls**
- Missing or unreachable base case → infinite recursion → **stack overflow** (segfault). The default stack is about 8 MB on Linux.
- Naive `fib` recomputes the same values over and over (exponential time). Fix it with **memoization** or a loop. See `../dynamic_programming/`.
- `factorial` overflows `int` at 13! and `unsigned long long` after 20!.
- Every recursive solution can be rewritten iteratively, if necessary with an explicit stack.

**Interview Qs**
- *What is a base case and why is it needed?* It is the condition that stops recursion. Without it the stack overflows.
- *What is tail recursion and why does it matter?* The recursive call is the last action, so the compiler can reuse the stack frame and run in O(1) stack space.
- *Time complexity of naive recursive Fibonacci?* O(2ⁿ) (more precisely O(φⁿ)). With memoization it is O(n).

---

## 5. Inline Function

**What it is** — `inline` (C99) is a **hint** asking the compiler to replace the call with the function body, avoiding call overhead for tiny functions. The compiler is free to ignore it, and at `-O2` it inlines small functions anyway.

**Syntax**
```c
static inline int square(int x) { return x * x; }   /* the usual, portable form */
```
Use `static inline`, normally in a header file. A plain `inline` without `static` follows tricky C99 linkage rules: without a separate non-inline definition elsewhere you can get *"undefined reference"* linker errors at `-O0`.

**Example** — [examples/02_inline.c](examples/02_inline.c)
```c
#define SQUARE_MACRO(x) ((x) * (x))
static inline int square(int x) { return x * x; }

int i = 3;
int r = square(i++);                   /* argument evaluated ONCE → r = 9, i = 4 */
/* SQUARE_MACRO(i++) → ((i++) * (i++)) → i modified twice → UNDEFINED BEHAVIOUR */
```
Output:
```
square(4)       = 16
SQUARE_MACRO(4) = 16
square(i++)     = 9, i = 4
```

**Inline function vs macro**

| | `static inline` function | `#define` macro |
|-|--------------------------|-----------------|
| Processed by | compiler | preprocessor (text replacement) |
| Type checking | yes | no |
| Arguments evaluated | once | possibly many times (side-effect bugs) |
| Debuggable | yes | hard |
| Generic over types | no | yes |

**Key points / pitfalls**
- Use `inline` for **small, frequently called** functions. Inlining big functions bloats the code.
- Recursive functions generally cannot be fully inlined.
- Prefer `static inline` functions over function-like macros when you can.

**Interview Qs**
- *Is `inline` a command or a request?* A request. The compiler decides.
- *Why prefer inline functions over macros?* Type safety, single evaluation of arguments, and easier debugging.
- *Downside of inlining?* Larger code size, which can hurt the instruction cache.

---

## 6. Nested Functions

**What it is** — A function defined **inside another function**. This is **not allowed in standard C**. GCC supports it as an **extension**. Clang and MSVC do not.

**Example** — [examples/02_nested.c](examples/02_nested.c)
```c
int main(void)
{
    int factor = 10;
    int scale(int x) { return x * factor; }   /* nested: can see main's locals */
    printf("scale(5) = %d\n", scale(5));
}
```
```
$ gcc -std=gnu11 02_nested.c && ./a.out
scale(5) = 50
$ gcc -std=c11 -pedantic-errors 02_nested.c
error: ISO C forbids nested functions [-Wpedantic]
```

**Key points / pitfalls**
- Taking the address of a nested function makes GCC build a "trampoline" on the stack, which needs an **executable stack**. This is a security concern.
- Code that uses nested functions is not portable. Instead, make a separate `static` function and pass the needed data as parameters (or through a `void *context` for callbacks).
- **Nested function calls** like `f(g(x))` are perfectly fine and standard. Only nested *definitions* are non-standard.

**Interview Qs**
- *Does C support nested functions?* Not in standard C. GCC has them as an extension.
- *What's the portable alternative?* A file-scope `static` function that receives the needed variables as arguments.

---

### Quick revision
- Prototype → definition → call. Declare before use. Use `(void)` for no parameters.
- C is **always pass by value**. Use pointers to modify the caller's data or return multiple values.
- Arrays decay to pointers, so pass the length separately. `sizeof` inside the function gives the pointer size.
- `main` returns the exit status (0 = success). `argv` holds strings, `argv[argc] == NULL`.
- Recursion needs a base case. Too much depth overflows the stack. Tail calls can be optimized.
- `static inline` is safer than macros. Nested function definitions are a GCC-only extension.
