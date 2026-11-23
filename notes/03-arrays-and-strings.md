# 03 — Arrays and Strings

Source: [GfG C Tutorial → Arrays and Strings](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`

**Contents**
1. [Arrays](#1-arrays)
2. [Multidimensional Arrays](#2-multidimensional-arrays)
3. [Strings](#3-strings)
4. [String Functions](#4-string-functions)

---

## 1. Arrays

**What it is**
- An array is a **fixed-size** collection of elements of the **same type**, stored in **contiguous memory**.
- Elements are accessed by index from `0` to `n-1`. Access is O(1) because the address is computed: `addr(a[i]) = base + i * sizeof(element)`.

**Syntax**
```c
int a[5] = {10, 20, 30, 40, 50};   /* full init                        */
int b[5] = {1, 2};                 /* remaining elements become 0      */
int c[]  = {7, 8, 9};              /* size deduced from initialiser: 3 */
int z[5] = {0};                    /* all zeros                        */
int d[6] = {[1] = 5, [4] = 9};     /* designated initialisers (C99)    */
int n = 10; int v[n];              /* VLA (C99, optional in C11): no initialiser allowed */
```

**Memory layout**
```
int a[5] = {10, 20, 30, 40, 50};

 index:     a[0]   a[1]   a[2]   a[3]   a[4]
          ┌──────┬──────┬──────┬──────┬──────┐
 value:   │  10  │  20  │  30  │  40  │  50  │
          └──────┴──────┴──────┴──────┴──────┘
 address:  0x100  0x104  0x108  0x10C  0x110      (int = 4 bytes)
```

**Example** — [examples/03_arrays.c](examples/03_arrays.c)
```c
#define LEN(a) (sizeof(a) / sizeof((a)[0]))   /* element count — real arrays only */

void size_in_function(int *arr)               /* identical to: int arr[] */
{
    printf("sizeof(arr) in function = %zu (pointer!)\n", sizeof(arr));
}

void reverse(int arr[], int n)
{
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
    }
}

printf("a[2] = %d, *(a + 2) = %d, 2[a] = %d\n", a[2], *(a + 2), 2[a]);
```
Output:
```
a: 10 20 30 40 50
b: 1 2 0 0 0
c: 7 8 9
z: 0 0 0 0 0
d: 0 5 0 0 9 0
sizeof(a) = 20, LEN(a) = 5
sizeof(arr) in function = 8 (pointer!)
a[2] = 30, *(a + 2) = 30, 2[a] = 30
a = 0x7fff...9e00, &a[0] = 0x7fff...9e00 (same address)
reversed a: 50 40 30 20 10
max = 50
```

**Array decay**
- In most expressions an array name **decays** to a pointer to its first element: `a` → `&a[0]`.
- `a[i]` is defined as `*(a + i)`, which is why the odd-looking `2[a]` also works.
- Decay does **not** happen with `sizeof(a)`, `&a`, or when a string literal initialises a char array.
- `&a` has type `int (*)[5]` (pointer to the whole array). It has the same address as `a` but a different type: `&a + 1` jumps 20 bytes.

**Key points / pitfalls**
- **No bounds checking.** `a[5]` or `a[-1]` is **UB**: it may silently corrupt other variables or crash. Catch it with `gcc -fsanitize=address`.
- The size must be known when the array is created and **cannot change** later. Use `malloc`/`realloc` for growable arrays (see 06).
- Arrays cannot be assigned or compared as a whole: `a = b` is an error, and `a == b` compares addresses. Use a loop, `memcpy` or `memcmp`.
- When passed to a function, an array decays to a pointer, so `sizeof` gives 8 and the `LEN()` macro gives the wrong answer. Always pass `n`. If you write the parameter as `int arr[]`, GCC warns with `-Wsizeof-array-argument`.
- An uninitialised **local** array holds garbage. Global and static arrays are zeroed.
- Big local arrays (e.g. `int big[10000000]`) overflow the stack. Make them `static` or use `malloc`.

**Interview Qs**
- *Why do array indices start at 0?* The index is an offset from the base address, so `a[0]` is at `base + 0`.
- *Difference between `a` and `&a`?* They hold the same address, but `a` decays to `int *` while `&a` is `int (*)[5]`. Adding 1 moves 4 bytes vs 20 bytes.
- *How do you find the length of an array?* `sizeof(a) / sizeof(a[0])`. This works only in the scope where the array is declared, not on a pointer.

---

## 2. Multidimensional Arrays

**What it is** — An array of arrays. `int m[2][3]` is 2 rows, each an array of 3 ints. C stores it in **row-major order**: row 0 completely, then row 1, and so on.

**Syntax**
```c
int m[2][3] = { {1, 2, 3}, {4, 5, 6} };
int m2[2][3] = {1, 2, 3, 4, 5, 6};          /* same thing, flat initialiser */
int m3[][3]  = { {1, 2, 3}, {4, 5, 6} };    /* first dimension may be omitted */
int cube[2][2][2];                           /* 3-D */
```

**Memory layout (row-major)**
```
Logical view:            Memory (contiguous):
      col0 col1 col2
row0 [ 1 ][ 2 ][ 3 ]     [ 1 ][ 2 ][ 3 ][ 4 ][ 5 ][ 6 ]
row1 [ 4 ][ 5 ][ 6 ]      ─── m[0] ───   ─── m[1] ───

addr(m[i][j]) = base + (i * COLS + j) * sizeof(int)
```

**Passing to functions** — every dimension **except the first** must be known:
```c
void f1(int m[][3], int rows);                   /* fixed column count            */
void f2(int (*m)[3], int rows);                  /* same as f1 (pointer to row)   */
void f3(int rows, int cols, int m[rows][cols]);  /* C99 VLA param: any size       */
void f4(int **m, int rows, int cols);            /* ONLY for arrays of pointers / malloc'd rows,
                                                    NOT for int m[2][3]           */
```

**Example** — [examples/03_multidim.c](examples/03_multidim.c)
```c
int m[ROWS][COLS] = { {1, 2, 3}, {4, 5, 6} };

int *flat = &m[0][0];                         /* walk it as one flat block */
for (int k = 0; k < ROWS * COLS; k++) printf("%d ", flat[k]);

int t[COLS][ROWS];                            /* transpose */
for (int i = 0; i < ROWS; i++)
    for (int j = 0; j < COLS; j++)
        t[j][i] = m[i][j];
print_vla(COLS, ROWS, t);
```
Output:
```
print_fixed:
  1  2  3
  4  5  6
row-major memory: 1 2 3 4 5 6
sizeof(m) = 24, sizeof(m[0]) = 12
transpose (print_vla):
  1  4
  2  5
  3  6
cube[1][0][1] = 6
```

**Key points / pitfalls**
- `int m[2][3]` **is not** `int **`. Passing it to `void f(int **m)` compiles only with a cast and then crashes.
- `sizeof(m[0])` is the size of one row (12 bytes) and `sizeof(m)` is the whole matrix (24 bytes). Rows = `sizeof(m)/sizeof(m[0])`.
- Loop with `i` (row) outside and `j` (column) inside. That walks memory sequentially, which is cache-friendly and much faster for large matrices than column-first loops.
- A "jagged" array (rows of different lengths) needs an array of pointers, e.g. `char *names[] = {"Al", "Barbara"};`.

**Interview Qs**
- *Row-major vs column-major?* C stores rows contiguously (row-major). Fortran and MATLAB are column-major.
- *Why must the column size be given when passing a 2-D array?* The compiler needs it to compute `m[i][j] = base + i*COLS + j`.
- *Address of `m[i][j]` in an R×C int array?* `base + (i*C + j) * 4`.

---

## 3. Strings

**What it is** — C has **no string type**. A string is a **`char` array terminated by the null character `'\0'`** (value 0). Every string function relies on that terminator to find the end.

**Syntax**
```c
char s1[] = "hello";               /* array of 6: h e l l o \0 — your own modifiable copy */
char s2[10] = "hi";                /* rest filled with \0                                  */
char s3[] = {'a', 'b', 'c', '\0'}; /* char-by-char: YOU must add \0                         */
const char *p = "world";           /* pointer to a READ-ONLY string literal                */
```

**`char s[]` vs `char *p`**
```
char s1[] = "hello";                   const char *p = "world";

stack: s1 ┌─┬─┬─┬─┬─┬──┐                stack: p [0x4005d0]──┐
          │h│e│l│l│o│\0│                                     ▼
          └─┴─┴─┴─┴─┴──┘                read-only: ┌─┬─┬─┬─┬─┬──┐
sizeof(s1) = 6, modifiable                         │w│o│r│l│d│\0│
                                                   └─┴─┴─┴─┴─┴──┘
                                        sizeof(p) = 8, p[0]='W' → UB (crash)
```

| | `char s[] = "..."` | `char *p = "..."` |
|-|--------------------|-------------------|
| What it is | array (copy of the literal) | pointer to a literal |
| Modify chars? | yes | **no** (UB). Declare it as `const char *` |
| `sizeof` | length + 1 | 8 (pointer size) |
| Re-point? | no (`s = "x"` is an error) | yes (`p = "other"`) |

**Example** — [examples/03_strings.c](examples/03_strings.c)
```c
int my_strlen(const char *s)
{
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

char line[32];
if (fgets(line, sizeof line, stdin)) {        /* safe line input */
    line[strcspn(line, "\n")] = '\0';         /* strip the newline fgets keeps */
    printf("You typed: \"%s\" (%zu chars)\n", line, strlen(line));
}
```
Output (input `  learn C today `):
```
s1 = hello, sizeof = 6, strlen = 5
s2 = hi, sizeof = 10, strlen = 2
s3 = abc, my_strlen = 3
p  = world, sizeof(p) = 8 (pointer)
modified s1 = Hello
chars of s1: 'H'(72) 'e'(101) 'l'(108) 'l'(108) 'o'(111)
Enter a line: You typed: "  learn C today " (16 chars)
```

**Reading strings**

| Method | Reads spaces? | Safe? | Notes |
|--------|--------------|-------|-------|
| `scanf("%s", s)` | no, stops at whitespace | **no** | can overflow |
| `scanf("%31s", s)` | no | yes | width = size − 1 |
| `scanf("%31[^\n]", s)` | yes | yes | scanset |
| `fgets(s, size, stdin)` | yes | **yes** | keeps the `'\n'`, so strip it |
| `gets(s)` | yes | **never** | removed in C11 |

**Key points / pitfalls**
- Always leave room for `'\0'`: `"hello"` needs `char[6]`. `char s[5] = "hello";` compiles but has **no terminator**, so printing it reads past the end.
- `strlen` excludes `'\0'`, while `sizeof` on an array includes it.
- Modifying a string literal is UB. Declare pointers to literals as `const char *`.
- `'a'` is a `char` (an int value, 97). `"a"` is a string: 2 bytes, `'a'` plus `'\0'`.
- Compare strings with `strcmp`, **never `==`**, which only compares addresses.
- Characters are small integers: `'0' + 5 == '5'`, `c - '0'` turns a digit char into its value, and `'a' - 'A' == 32`.

**Interview Qs**
- *How is a string stored in C?* As a char array ending with `'\0'`.
- *Difference between `char s[] = "hi"` and `char *s = "hi"`?* The first is a modifiable array copy. The second is a pointer to a read-only literal.
- *Why is `gets()` dangerous?* It cannot know the buffer size, so long input overflows it. That is a classic security hole.
- *`sizeof("hello")` vs `strlen("hello")`?* 6 vs 5.

---

## 4. String Functions

**What it is** — `<string.h>` provides string and memory routines, and `<ctype.h>` classifies and converts characters.

**`<string.h>` cheat sheet**

| Function | Purpose | Returns / note |
|----------|---------|----------------|
| `strlen(s)` | length excluding `\0` | `size_t`, O(n) |
| `strcpy(d, s)` | copy s → d | d must be big enough |
| `strncpy(d, s, n)` | copy at most n chars | **may not add `\0`** |
| `strcat(d, s)` | append s to d | d must have room |
| `strncat(d, s, n)` | append at most n chars | always adds `\0` |
| `strcmp(a, b)` | compare | `<0`, `0`, `>0` (not necessarily −1/1) |
| `strncmp(a, b, n)` | compare first n chars | |
| `strchr(s, c)` | first occurrence of c | pointer or `NULL` |
| `strrchr(s, c)` | last occurrence of c | pointer or `NULL` |
| `strstr(s, sub)` | first occurrence of a substring | pointer or `NULL` |
| `strtok(s, delims)` | split into tokens | **modifies s**, not thread-safe |
| `strcspn(s, set)` | length of prefix with no chars from set | used to strip `\n` |
| `memset(p, c, n)` | fill n bytes with c | |
| `memcpy(d, s, n)` | copy n bytes (no overlap) | |
| `memmove(d, s, n)` | copy n bytes (overlap OK) | |
| `memcmp(a, b, n)` | compare n bytes | |
| `snprintf(buf, n, fmt, ...)` | formatted write into a buffer | `<stdio.h>`, never overflows |

**`<ctype.h>`**: `isalpha isdigit isalnum isspace isupper islower ispunct toupper tolower`

**Example** — [examples/03_string_functions.c](examples/03_string_functions.c)
```c
char small[6];
strncpy(small, "abcdefgh", sizeof small - 1);
small[sizeof small - 1] = '\0';                  /* strncpy may NOT terminate */

char buf[16];
snprintf(buf, sizeof buf, "%s-%d", "id", 42);    /* safest way to build strings */

printf("%td\n", strstr(text, "brown") - text);   /* index = pointer difference */

char csv[] = "red,green,,blue";                  /* must be an array: strtok writes into it */
for (char *tok = strtok(csv, ","); tok; tok = strtok(NULL, ","))
    printf("[%s] ", tok);

word[i] = toupper((unsigned char)word[i]);       /* cast avoids UB for negative chars */
```
Output:
```
strcpy  : Hello
strcat  : Hello, World (len 12)
strncpy : abcde
snprintf: id-42
strcmp("apple","banana") = -1
strcmp("abc","abc")      = 0
strncmp("hello","help",3) = 0
strchr(text,'q')  -> "quick brown fox"
strrchr(text,'o') -> "ox"
strstr(text,"brown") at index 10
strstr(text,"cat") = NULL
strtok  : [red] [green] [blue]
ctype   : HELLO123 letters=5 digits=3
memset  : *******
```

**Key points / pitfalls**
- `strcpy` and `strcat` don't check sizes, which is the #1 source of buffer overflows. Prefer `snprintf`, or carefully sized `strncat`.
- `strncpy` does **not** null-terminate if the source is ≥ n characters. Terminate it yourself.
- `strtok` modifies its input (so never pass it a literal), **skips empty tokens** (`",,"` gives nothing), and keeps hidden state between calls. POSIX `strtok_r` is the re-entrant version.
- `strcmp` returns *some* negative or positive value, not necessarily −1 or 1. Test `< 0`, `== 0`, `> 0`.
- Calling `strlen(s)` in a loop condition (`for (i = 0; i < strlen(s); i++)`) makes the loop O(n²). Store the length first.
- Pass `(unsigned char)c` to `<ctype.h>` functions. A negative `char` is UB.
- `memcpy` with overlapping regions is UB. Use `memmove`.

**Interview Qs**
- *Implement `strlen`, `strcpy`, `strcmp` and reverse-a-string yourself.* These are classic warm-ups. See `my_strlen` above and `../string/` for more.
- *`memcpy` vs `memmove`?* `memmove` handles overlapping buffers. `memcpy` may be faster but requires no overlap.
- *`strcpy` vs `strncpy`?* `strncpy` limits the count but may leave the string unterminated.
- *How do you reverse a string in place?* Swap `s[i]` and `s[n-1-i]` for `i < n/2`.

---

### Quick revision
- Arrays are fixed-size, contiguous, indexed from 0, and **not bounds-checked**. `a[i] == *(a+i)`.
- An array decays to a pointer when passed, so `sizeof` gives 8. Always pass the length.
- 2-D arrays are row-major. Give every dimension except the first when passing. `int[2][3]` is not `int **`.
- A string is a char array ending in `'\0'`. Leave room for it. Compare with `strcmp`, not `==`.
- `char s[]` is a modifiable copy. `char *p = "..."` points to a read-only literal.
- Read lines with `fgets` and strip `\n` with `strcspn`. Build strings with `snprintf`. Never use `gets`.
- `strncpy` may not terminate. `strtok` modifies its input. Use `memmove` for overlapping copies.
