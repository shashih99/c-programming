# Plan: C Programming Notes (based on GeeksforGeeks C Tutorial)

## Context
You want study notes for C that follow the GeeksforGeeks C tutorial
(https://www.geeksforgeeks.org/c/c-programming-language/). They go in a new `notes/`
folder inside the existing practice repo `c-programming/c-programming/`, next to
`array/`, `string/`, and the other folders. Style: **concise notes with runnable code**.

## Folder layout
```
c-programming/c-programming/notes/
├── README.md                     # index: table of contents linking every file + how to compile examples
├── 01-basics.md
├── 02-functions.md
├── 03-arrays-and-strings.md
├── 04-pointers.md
├── 05-user-defined-types.md
├── 06-memory-management.md
├── 07-file-handling.md
├── 08-error-handling.md
├── 09-preprocessor-and-misc.md
├── 10-advanced-concepts.md
├── 11-whats-next.md              # interview Q's, DSA-in-C, practice problems, careers
└── examples/                     # one compilable .c per major example, named NN_topic.c
```

## Template for every topic (inside each section file)
1. **What it is**: 2–4 line explanation
2. **Syntax**: a minimal code block
3. **Example**: a short, compilable program and its expected output
4. **Key points / pitfalls**: bullets (undefined behaviour (UB), common bugs)
5. **Interview Qs**: 2–3 quick questions with one-line answers
6. **Reference**: link to the matching GfG page

## Content per file (follows the tutorial's order)

**01-basics.md**
- Intro to C (history, features, structure of a C program, hello world)
- Setting up the environment (gcc, VS Code) and the compilation process (preprocess → compile → assemble → link; `gcc -E/-S/-c`)
- Identifiers, keywords
- Input/Output (`printf`/`scanf`, format specifiers)
- Variables (scope, declaration vs definition)
- Data types (sizes, signed/unsigned, `sizeof`, type conversion)
- Operators (precedence table, bitwise, short-circuit, `++`/`--` pitfalls)
- Conditional statements (if/else, switch, ternary)
- Loops (for/while/do-while, break/continue, goto)

**02-functions.md**
- Declaration, definition, prototypes, return values
- Parameter passing (pass by value vs. by pointer)
- `main()` forms, `argc`/`argv`, return codes
- Recursion (base case, call stack, tail recursion)
- Inline functions (`inline`, `static inline`)
- Nested functions (not standard C; GCC extension)

**03-arrays-and-strings.md**
- 1-D arrays (init, indexing, decay to pointer, passing to functions)
- Multidimensional arrays (row-major layout, passing 2-D arrays)
- Strings (`char[]` vs `char*`, the `'\0'` terminator, string literals)
- String functions (`strlen`, `strcpy`/`strncpy`, `strcat`, `strcmp`, `strchr`, `strstr`, `strtok`, safety notes)

**04-pointers.md**
- Pointer basics (`&`, `*`, NULL, void*, wild/dangling pointers)
- Pointer arithmetic (scaling by type size, array ↔ pointer equivalence)
- Pointer to pointer (double pointers, modifying a pointer inside a function)
- Function pointers (callbacks, `qsort` comparator, arrays of function pointers)
- `const` with pointers (`const int*` vs `int* const`)

**05-user-defined-types.md**
- Structures (definition, `typedef`, nested structs, `.` vs `->`, arrays of structs)
- Structure alignment, padding and packing (this is in the GfG sidebar only, not the main outline)
- Unions (shared memory, size, use cases such as tagged unions)
- Enumerations (enum values, enums vs `#define`)
- Bit fields

**06-memory-management.md**
- Program memory layout (text, data, bss, heap, stack, with an ASCII diagram)
- Dynamic allocation (`malloc`, `calloc`, `realloc`, `free`)
- Memory leaks: causes and detection with `valgrind` / `-fsanitize=address`

**07-file-handling.md**
- `FILE*`, `fopen` modes, `fclose`
- Reading and writing text (`fgetc`/`fputc`, `fgets`/`fputs`, `fprintf`/`fscanf`)
- Reading a whole file
- Binary I/O: reading and writing structs (`fread`/`fwrite`)
- EOF, `getc()`, `feof()` (and the `while(!feof())` pitfall)
- `fseek`/`ftell`/`rewind`, `remove()`/`rename()`

**08-error-handling.md**
- `errno`, `perror`, `strerror`, exit codes (`EXIT_SUCCESS`/`EXIT_FAILURE`)
- Cleanup with `goto` (the single-exit pattern)
- File-operation errors (`ferror`, checking return values)
- Divide-by-zero and other runtime errors, `assert`

**09-preprocessor-and-misc.md**
- Preprocessor directives (`#include`, `#define`, `#if/#ifdef`, `#pragma`)
- Macros (object-like and function-like, macro pitfalls, `#` and `##`, predefined macros)
- Header files (include guards, writing your own header)
- Date and time (`<time.h>`: `time`, `localtime`, `strftime`, `clock`)
- Linkage (internal vs. external, `extern`, `static` at file scope)
- Storage classes (`auto`, `register`, `static`, `extern`, with a lifetime/scope table)

**10-advanced-concepts.md**
- Variadic functions (`<stdarg.h>`: `va_list`, `va_start`, `va_arg`, `va_end`)
- I/O system calls (`open`, `read`, `write`, `close`, file descriptors vs `FILE*`)
- Signals (`signal`, `SIGINT`, handlers, async-signal safety)
- Socket programming (a minimal TCP client and server)
- `_Generic` (C11 type-generic macros)
- Multithreading (`pthread_create`/`join`, mutex basics; compile with `-pthread`)

**11-whats-next.md**
- Top C interview questions (a condensed list with short answers)
- Pointers to DSA in C, plus a link-back table to the solved problems already in this repo (`array/`, `string/`, `linked_list/`, …)
- Practice problem lists (fundamentals, functions, compound types)
- A short note on careers and companies that use C, and a comparison of C vs Java vs Python

**README.md**
- A table of contents linking all section files
- How to compile and run examples: `gcc -Wall -Wextra -std=c11 examples/NN_x.c -o /tmp/a && /tmp/a`
- A suggested study order

## Execution approach
- Write each section file from the topic list above. Fetch each linked GfG page only where a detail needs checking; the notes are written in my own words, not copied from GfG.
- Put the larger examples in `examples/` as standalone `.c` files that the markdown refers to.

## Verification
- Compile every file in `notes/examples/` with `gcc -Wall -Wextra -std=c11` (adding `-pthread` for threading). It should build with no warnings, and each program's output should match what the notes say.
- Check that every link in README.md points to an existing file.
- Do not make a git commit unless you ask for one.
