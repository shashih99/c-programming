# 07 — File Handling

Source: [GfG C Tutorial → File Handling](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`
(The examples create their demo files in the current directory and delete them afterwards.)

**Contents**
1. [Basics of File Handling](#1-basics-of-file-handling)
2. [Reading and Writing Text](#2-reading-and-writing-text)
3. [Read a Whole File](#3-read-a-whole-file)
4. [Read/Write Structures (Binary I/O)](#4-readwrite-structures-binary-io)
5. [EOF, getc() and feof()](#5-eof-getc-and-feof)
6. [File Positioning](#6-file-positioning)
7. [Delete, Rename and Temporary Files](#7-delete-rename-and-temporary-files)

---

## 1. Basics of File Handling

**What it is**
- Files let data **outlive the program**, unlike variables, which vanish when it exits.
- `<stdio.h>` works with files through a **`FILE *`** (a "stream"): an opaque struct holding the OS file descriptor, a buffer, the current position, and EOF/error flags.
- Three streams are open from the start: **`stdin`**, **`stdout`**, **`stderr`**. `printf(...)` is just `fprintf(stdout, ...)`.

**The life cycle**
```
fopen()  ──►  read / write / seek  ──►  fclose()
   │                                       │
   └─ returns NULL on failure              └─ flushes buffer, releases the OS handle
```

**Syntax**
```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {               /* ALWAYS check: missing file, no permission, bad path... */
    perror("data.txt");         /* prints e.g. "data.txt: No such file or directory" */
    return 1;
}
/* ... use fp ... */
fclose(fp);
```

**`fopen` modes**

| Mode | Meaning | File must exist? | Truncates? | Position |
|------|---------|------------------|------------|----------|
| `"r"` | read | **yes** (else NULL) | no | start |
| `"w"` | write | no (creates) | **yes, erases contents** | start |
| `"a"` | append | no (creates) | no | **always end** |
| `"r+"` | read + write | **yes** | no | start |
| `"w+"` | read + write | no (creates) | **yes** | start |
| `"a+"` | read + append | no (creates) | no | reads anywhere, writes at end |
| add `b` | binary: `"rb"`, `"wb"`, `"r+b"`… | | | |
| add `x` (C11) | `"wx"`: fail if the file already exists | | | |

**Text vs binary mode**

| | Text (`"r"`) | Binary (`"rb"`) |
|-|--------------|-----------------|
| Contents | human-readable characters | raw bytes (structs, images…) |
| Newline translation | on Windows `\r\n` ↔ `\n` | none |
| On Linux/macOS | no difference in practice | no difference in practice |
| Typical functions | `fgets`, `fprintf`, `fscanf` | `fread`, `fwrite` |

**Key points / pitfalls**
- `"w"` **silently destroys** an existing file. Double-check the mode.
- Every successful `fopen` needs exactly one `fclose`. Open files leak like memory, and the OS limits how many a process can open (`ulimit -n`).
- Output is **buffered**. Data may not reach the disk until `fclose`, `fflush(fp)` or program exit. If the program crashes, buffered data is lost.
- Never call `fclose` twice on the same `FILE *`, and never use it after closing.
- When switching between reading and writing on an `r+`/`w+` stream, call `fseek`, `rewind` or `fflush` in between.

**Interview Qs**
- *What does `fopen` return on failure?* `NULL`, with `errno` set to the reason.
- *Difference between `"w"` and `"a"`?* `"w"` truncates the file and writes from the start. `"a"` keeps the contents and always writes at the end.
- *What are the three standard streams?* `stdin`, `stdout`, `stderr`. `stderr` is unbuffered, so error messages appear immediately.

---

## 2. Reading and Writing Text

| Unit | Write | Read | Read returns at end/error |
|------|-------|------|---------------------------|
| Character | `fputc(c, fp)` / `putc` | `fgetc(fp)` / `getc` | `EOF` |
| Line/string | `fputs(s, fp)` | `fgets(buf, size, fp)` | `NULL` |
| Formatted | `fprintf(fp, fmt, ...)` | `fscanf(fp, fmt, ...)` | number of items matched, or `EOF` |

**Example** — [examples/07_file_basics.c](examples/07_file_basics.c)
```c
FILE *fp = fopen(path, "w");
fputc('#', fp);
fputs(" Scores\n", fp);
fprintf(fp, "%s %d\n", "asha", 91);
fclose(fp);

fp = fopen(path, "a");                       /* append one more line */
fprintf(fp, "%s %d\n", "meena", 85);
fclose(fp);

fp = fopen(path, "r");
int ch;                                      /* int, NOT char: must be able to hold EOF */
while ((ch = fgetc(fp)) != EOF) { ... }      /* char by char */

rewind(fp);
char line[64];
while (fgets(line, sizeof line, fp) != NULL) /* line by line */
    printf("  | %s", line);

while (fscanf(fp, "%15s %d", name, &score) == 2) { ... }   /* formatted */
```
Output:
```
fgetc : 34 chars, 4 lines
fgets :
  | # Scores
  | asha 91
  | ravi 78
  | meena 85
fscanf: 3 students, average 84.7
ftell at end = 34 bytes
```

**Key points / pitfalls**
- Store `fgetc`'s result in an **`int`**. If you store it in a `char`, either the byte `0xFF` is mistaken for `EOF` (signed char) or the loop never ends (unsigned char).
- `fgets` keeps the `'\n'` and always null-terminates. A line longer than the buffer is split across calls.
- Check that `fscanf` returned the **number of items you asked for**, not just "not EOF". A malformed line returns fewer and leaves the bad input unread.
- For robust parsing, read lines with `fgets`, then parse with `sscanf`/`strtol`.
- `fprintf(stderr, ...)` is the right place for error messages.

**Interview Qs**
- *Why does `fgetc` return `int` instead of `char`?* It must return every possible byte value (0–255) **plus** a distinct `EOF` (−1).
- *`fgets` vs `fscanf("%s")`?* `fgets` reads a whole line, including spaces, and is bounded. `%s` stops at whitespace and needs a width to be safe.

---

## 3. Read a Whole File

**What it is** — Load an entire file into one heap buffer: find the size with `fseek`/`ftell`, `malloc` that many bytes + 1, `fread` everything, and add `'\0'`.

**Example** — [examples/07_read_whole_file.c](examples/07_read_whole_file.c)
```c
char *read_file(const char *path, long *out_size)
{
    FILE *fp = fopen(path, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);                 /* size in bytes */
    rewind(fp);

    char *buf = malloc(size + 1);          /* +1 for '\0' */
    if (!buf) { fclose(fp); return NULL; }

    size_t got = fread(buf, 1, size, fp);
    fclose(fp);
    if (got != (size_t)size) { free(buf); return NULL; }

    buf[size] = '\0';
    *out_size = size;
    return buf;                            /* caller must free (06 §3) */
}
```
Output (`./prog`, which reads its own source by default):
```
07_read_whole_file.c: 1437 bytes, 43 lines
first line: /* 07_read_whole_file.c - read an entire file into a heap buffer
```

**Key points / pitfalls**
- Open in **binary** mode (`"rb"`). On Windows, text mode translates `\r\n`, so the bytes read won't match `ftell`'s size.
- `fseek`/`ftell` don't work on pipes or `stdin`. For those, read in chunks and `realloc` the buffer as it grows (see 06 §2).
- `ftell` returns `long`. For files over 2 GB on some platforms, use POSIX `fseeko`/`ftello` with `off_t`.

---

## 4. Read/Write Structures (Binary I/O)

**What it is** — `fwrite` and `fread` copy **raw bytes** between memory and a file. They are ideal for arrays and structs, and fast, since there is no text formatting.

**Syntax**
```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *fp);
size_t fread (void *ptr,       size_t size, size_t count, FILE *fp);
/* both return the number of ITEMS (not bytes) actually transferred */
```

**Example** — [examples/07_struct_io.c](examples/07_struct_io.c)
```c
typedef struct { int id; char name[16]; float salary; } Employee;

fp = fopen(path, "wb");
fwrite(staff, sizeof(Employee), n, fp);              /* whole array in one call */

fp = fopen(path, "rb");
while (fread(&e, sizeof e, 1, fp) == 1)              /* one record at a time */
    printf("  %d %-6s %.2f\n", e.id, e.name, e.salary);

fseek(fp, 2 * (long)sizeof(Employee), SEEK_SET);     /* RANDOM ACCESS: jump to record #2 */
fread(&e, sizeof e, 1, fp);

fp = fopen(path, "r+b");                             /* UPDATE IN PLACE */
fseek(fp, 1 * (long)sizeof(Employee), SEEK_SET);
fread(&e, sizeof e, 1, fp);
e.salary += 1500.0f;
fseek(fp, -(long)sizeof(Employee), SEEK_CUR);        /* step back over the record */
fwrite(&e, sizeof e, 1, fp);
```
Output:
```
wrote 3 records (24 bytes each)
sequential read:
  101 Asha   52000.00
  102 Ravi   48500.50
  103 Meena  61000.00
random access record 2: Meena
after update (3 read): Ravi now earns 50000.50
```

Fixed-size records make the file work like an on-disk array: record *k* starts at byte `k * sizeof(record)`.

**Key points / pitfalls**
- Binary files written this way are **not portable** between machines or compilers, because padding (05 §2), endianness and type sizes may differ. For portable formats, write each field explicitly in a defined byte order, or use text (CSV/JSON).
- **Never `fwrite` a struct that contains pointers** (e.g. `char *name`). Only the address is saved, not the data it points to, and that address is meaningless when read back.
- Compare the return value with the **count** you requested, not with the byte size.
- Always use binary mode (`"wb"`/`"rb"`) for binary data.

**Interview Qs**
- *What do `fread`/`fwrite` return?* The number of complete items transferred. A short count means EOF or an error.
- *Why is writing structs directly to a file risky?* Padding, endianness and type sizes are platform-dependent, and pointer members are saved as meaningless addresses.
- *How do you get to the n-th record directly?* `fseek(fp, n * sizeof(record), SEEK_SET)`.

---

## 5. EOF, getc() and feof()

**What it is**
- **`EOF`** is a macro for a negative int (−1 on glibc) that read functions return when there's nothing more to read, **or on error**.
- **`getc(fp)`** is the same as `fgetc(fp)`, but it may be implemented as a macro (so don't pass arguments with side effects). `getchar()` is `getc(stdin)`.
- **`feof(fp)`** returns non-zero if the stream's **EOF flag** is set, which happens only **after a read has already tried to go past the end**.
- **`ferror(fp)`** returns non-zero if a read/write **error** occurred. `clearerr(fp)` resets both flags.

**Example** — [examples/07_eof_feof.c](examples/07_eof_feof.c)
```c
/* WRONG: feof() becomes true only AFTER a read fails → one extra iteration */
while (!feof(fp)) {
    int c = getc(fp);      /* the last call returns EOF and is processed as data */
    count++;
}

/* RIGHT: test the read's own return value */
while ((c = getc(fp)) != EOF)
    count++;

/* after the loop, ask WHY it stopped */
if (feof(fp))        puts("end of file");
else if (ferror(fp)) puts("read error");
```
Output (file contains `"abc\n"`, 4 characters):
```
EOF macro = -1
while(!feof) loop ran 5 times (file has 4 chars)
while((c = getc(fp)) != EOF) ran 4 times
stopped: end of file reached
after clearerr, feof = 0
```

**Key points / pitfalls**
- **`while (!feof(fp))` is almost always a bug**: it processes the failed last read as data. The same applies to `fgets` and `fscanf` loops. Loop on the read function's return value.
- `feof` is for **after** the loop, to tell "end of file" apart from "error".
- `EOF` is not a character stored in the file. It is a signal value returned by the function.
- At the keyboard you can send EOF with **Ctrl+D** (Linux/macOS) or **Ctrl+Z, Enter** (Windows).

**Interview Qs**
- *Why is `while(!feof(fp))` wrong?* The EOF flag is set only after a read fails, so the loop body runs once more with invalid data.
- *What is the value of `EOF`?* An implementation-defined negative int, usually −1.
- *`feof` vs `ferror`?* `feof` means end of file was reached. `ferror` means an I/O error happened.

---

## 6. File Positioning

| Function | Purpose |
|----------|---------|
| `ftell(fp)` | current position (bytes from start), `long`; −1 on error |
| `fseek(fp, offset, whence)` | move. `whence` = `SEEK_SET` (from start), `SEEK_CUR` (from current), `SEEK_END` (from end). Returns 0 on success |
| `rewind(fp)` | `fseek(fp, 0, SEEK_SET)` + clears the error/EOF flags |
| `fgetpos` / `fsetpos` | save/restore position using an opaque `fpos_t` (works for huge files) |
| `fflush(fp)` | write buffered output now (output streams only; `fflush(stdin)` is UB) |

```c
fseek(fp, 0, SEEK_END);  long size = ftell(fp);   /* file size */
fseek(fp, -10, SEEK_END);                         /* 10 bytes before the end */
fseek(fp, sizeof rec, SEEK_CUR);                  /* skip one record */
```

**Key points / pitfalls**
- In **text** mode, the only portable `fseek` offsets are 0 or a value previously returned by `ftell`. Arbitrary byte offsets are reliable only in binary mode.
- `"a"` mode always writes at the end, whatever `fseek` says.
- `fflush(stdin)` is undefined behaviour in standard C (Windows supports it as an extension). Don't use it to "clear input".

---

## 7. Delete, Rename and Temporary Files

| Function | Purpose | Returns |
|----------|---------|---------|
| `remove(path)` | delete a file | 0 on success, non-zero on failure (`errno` set) |
| `rename(old, new)` | rename or move a file | 0 on success |
| `tmpfile()` | open an anonymous temp file (`"wb+"`), deleted automatically on close/exit | `FILE *` or `NULL` |

**Example** — [examples/07_delete_rename.c](examples/07_delete_rename.c)
```c
rename("old_name.txt", "new_name.txt");
remove("new_name.txt");
if (remove("no_such_file.txt") != 0)
    perror("remove no_such_file.txt");       /* explains why it failed */

FILE *tmp = tmpfile();                       /* scratch storage, no cleanup needed */
```
Output:
```
old_name.txt exists? 1
renamed -> new_name.txt exists? 1
removed -> new_name.txt exists? 0
remove no_such_file.txt: No such file or directory
tmpfile contains: scratch data
```

**Key points / pitfalls**
- Close a file before you `remove` or `rename` it. On Windows, removing an open file fails.
- `rename` onto an existing file replaces it on POSIX, but fails on Windows.
- Checking existence with `fopen(path, "r")` also fails when the file exists but isn't readable. POSIX `access()` or `stat()` are more precise.
- To delete a directory use POSIX `rmdir()`. `remove` deletes empty directories on POSIX too.
- Avoid `tmpnam()`: there's a race between generating the name and creating the file. Use `tmpfile()` or POSIX `mkstemp()`.

---

### Quick revision
- `FILE *fp = fopen(path, mode)` → **check for NULL** → use it → `fclose(fp)`.
- Modes: `r` (must exist), `w` (**truncates**), `a` (append), `+` for read+write, `b` for binary.
- Text: `fgetc`/`fputc`, `fgets`/`fputs`, `fscanf`/`fprintf`. Store `fgetc`'s result in an **int**.
- Binary: `fwrite`/`fread` return an **item count**. Writing raw structs isn't portable, and never save pointers.
- Loop on the read's return value, **not `while(!feof(fp))`**. Use `feof`/`ferror` afterwards to see why it stopped.
- `fseek`/`ftell`/`rewind` move around the file. Record *k* is at `k * sizeof(rec)`.
- `remove`, `rename`, `tmpfile`. Report failures with `perror`.
