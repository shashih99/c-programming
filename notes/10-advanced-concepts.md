# 10 — Advanced Concepts

Source: [GfG C Tutorial → Advanced Concepts](https://www.geeksforgeeks.org/c/c-programming-language/)
Examples: [examples/](examples/) — compile with `gcc -Wall -Wextra -std=c11 file.c -o prog && ./prog`
(System calls, signals, sockets and threads are **POSIX** (Linux/macOS), not standard C. Those examples start with `#define _POSIX_C_SOURCE 200809L` so the POSIX functions are declared under `-std=c11`. The threads example also needs `-pthread`.)

**Contents**
1. [Variadic Functions](#1-variadic-functions)
2. [Input-Output System Calls](#2-input-output-system-calls)
3. [Signals](#3-signals)
4. [Socket Programming](#4-socket-programming)
5. [_Generic Keyword](#5-_generic-keyword)
6. [Multithreading](#6-multithreading)

---

## 1. Variadic Functions

**What it is** — Functions that accept a **variable number of arguments**, like `printf` and `scanf`. They are declared with `...` after at least one named parameter, and the arguments are read with the `<stdarg.h>` macros.

| Macro | Purpose |
|-------|---------|
| `va_list ap;` | holds the iteration state |
| `va_start(ap, last_named)` | initialise. Pass the **last named parameter** |
| `va_arg(ap, type)` | fetch the next argument, **which you must say the type of** |
| `va_end(ap)` | clean up. Pair every `va_start`/`va_copy` with one |
| `va_copy(dst, src)` | duplicate the state to walk the arguments twice (C99) |

**The function can't tell how many arguments it got, or their types.** You must pass that information yourself:
1. **a count** parameter: `sum(3, 10, 20, 30)`
2. **a sentinel** value at the end: `print_words("a", "b", NULL)`
3. **a format string** that describes them: `printf("%d %s", ...)`

**Example** — [examples/10_variadic.c](examples/10_variadic.c)
```c
int sum(int count, ...)
{
    va_list ap;
    va_start(ap, count);
    int total = 0;
    for (int i = 0; i < count; i++)
        total += va_arg(ap, int);
    va_end(ap);
    return total;
}

double average(int count, ...) {
    ...
    total += va_arg(ap, double);      /* float args arrive as double! */
}

void log_msg(const char *level, const char *fmt, ...)   /* printf wrapper */
{
    va_list ap;
    va_start(ap, fmt);
    printf("[%s] ", level);
    vprintf(fmt, ap);                 /* v-functions accept a va_list */
    printf("\n");
    va_end(ap);
}
```
Output:
```
sum(3, 10, 20, 30) = 60
sum(0)             = 0
[alpha] [beta] [gamma]
average(3, 1.0, 2.0, f) = 1.83
[INFO] user asha logged in from 10.0.0.7
max = 9, 3 values above 5
```

**Key points / pitfalls**
- **Default argument promotions** apply to the `...` part: `float` → `double`, and `char`/`short` → `int`. So `va_arg(ap, float)` and `va_arg(ap, char)` are **wrong** (UB). Use `double` and `int`.
- Calling `va_arg` with the wrong type, or past the last argument, is **UB**. There is no checking. This is why a `printf` format mismatch is dangerous. GCC checks `printf`-style formats with `__attribute__((format(printf, 2, 3)))`.
- For a `NULL` sentinel, pass `(char *)NULL`. A bare `0` may be passed as an `int`, which is the wrong size on 64-bit.
- To write your own `printf`-like function, use `vprintf`/`vfprintf`/`vsnprintf`. You can't forward `...` directly.
- Variadic macros (`__VA_ARGS__`) are a different, preprocessor-level feature (09 §2).

**Interview Qs**
- *How does `printf` know how many arguments it received?* It doesn't. It trusts the format string.
- *What are `va_start`, `va_arg`, `va_end`?* The macros that initialise, step through and clean up a variable argument list.
- *Why can't you use `va_arg(ap, float)`?* Floats are promoted to double when passed through `...`.

---

## 2. Input-Output System Calls

**What it is**
- **System calls** are requests to the OS kernel. On POSIX systems, low-level file I/O uses **file descriptors**: small non-negative `int`s that index the process's table of open files.
- `fopen`/`fread`/`fprintf` (07) are the **buffered C library layer** built on top of these calls.

| fd | Stream | Macro |
|----|--------|-------|
| 0 | standard input | `STDIN_FILENO` |
| 1 | standard output | `STDOUT_FILENO` |
| 2 | standard error | `STDERR_FILENO` |
| 3+ | files/sockets you open | |

| Call | Header | Signature | Returns |
|------|--------|-----------|---------|
| `open` | `<fcntl.h>` | `int open(const char *path, int flags, mode_t mode)` | fd, or −1 |
| `read` | `<unistd.h>` | `ssize_t read(int fd, void *buf, size_t n)` | bytes read, **0 = EOF**, −1 = error |
| `write` | `<unistd.h>` | `ssize_t write(int fd, const void *buf, size_t n)` | bytes written (may be < n), −1 |
| `lseek` | `<unistd.h>` | `off_t lseek(int fd, off_t off, int whence)` | new position, −1 |
| `close` | `<unistd.h>` | `int close(int fd)` | 0, −1 |
| `creat` | `<fcntl.h>` | `= open(path, O_WRONLY \| O_CREAT \| O_TRUNC, mode)` | fd |
| `unlink` | `<unistd.h>` | delete a file | 0, −1 |

**`open` flags** (combine with `|`): `O_RDONLY`, `O_WRONLY`, `O_RDWR` (pick exactly one), plus `O_CREAT` (create if missing; then `mode` is required, e.g. `0644`), `O_TRUNC`, `O_APPEND`, `O_EXCL` (fail if it exists).

**Example** — [examples/10_syscalls.c](examples/10_syscalls.c)
```c
int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);   /* rw-r--r-- */
if (fd == -1) { perror("open"); return 1; }
write(fd, text, strlen(text));                              /* unbuffered */
close(fd);

fd = open(path, O_RDONLY);
while ((got = read(fd, buf, 10)) > 0)                       /* read 10 bytes at a time */
    write(STDOUT_FILENO, buf, got);

lseek(fd, 6, SEEK_SET);                                     /* random access */
```
Output:
```
opened syscall_demo.txt as fd 3 (0,1,2 are stdin, stdout, stderr)
write() wrote 31 bytes
fstat: size = 31 bytes, mode = 644
read() loop:
Hello from write()
Second line
lseek(6) -> 6, next 4 bytes: "from"
open /no/such/file: No such file or directory
```

**System calls vs standard I/O**

| | `open`/`read`/`write` | `fopen`/`fread`/`fprintf` |
|-|-----------------------|---------------------------|
| Standard | POSIX (OS-specific) | ISO C (portable) |
| Handle | `int` file descriptor | `FILE *` |
| Buffering | none: each call enters the kernel | user-space buffer, fewer syscalls |
| Formatting | none, raw bytes | `fprintf`, `fscanf` |
| Works with | files, pipes, sockets, devices | mainly files and terminals |
| Convert | `fdopen(fd, "r")` → `FILE *` | `fileno(fp)` → fd |

**Key points / pitfalls**
- `read` and `write` may transfer **fewer bytes than requested** (pipes, sockets, signals). Loop until everything is done.
- `read` returning **0 means EOF**, not an error.
- `mode` (`0644`) is **octal** and is reduced by the process `umask`.
- Mixing `printf` (buffered) and `write(1, ...)` (unbuffered) on the same output can reorder the text. `fflush(stdout)` first.
- The kernel limits open fds per process (`ulimit -n`). Always `close`.

**Interview Qs**
- *What is a file descriptor?* A small int the kernel gives a process to refer to an open file, socket or pipe. 0, 1 and 2 are stdin, stdout and stderr.
- *`read()` vs `fread()`?* `read` is an unbuffered syscall on an fd. `fread` is a buffered C library call on a `FILE *`, implemented with `read`.
- *What does `read` return at end of file?* 0.

---

## 3. Signals

**What it is** — A **signal** is an asynchronous notification sent to a process by the kernel, another process, or itself. Each signal has a **default action** (terminate, core dump, ignore, stop), and you can install a **handler** function instead.

| Signal | Number (Linux) | Sent when | Default | Catchable? |
|--------|----------------|-----------|---------|------------|
| `SIGINT` | 2 | **Ctrl+C** | terminate | yes |
| `SIGTERM` | 15 | `kill pid` (polite stop) | terminate | yes |
| `SIGKILL` | 9 | `kill -9 pid` | terminate | **no** |
| `SIGSEGV` | 11 | invalid memory access | core dump | yes, but don't return |
| `SIGFPE` | 8 | integer divide by zero (08 §4) | core dump | yes, but don't return |
| `SIGABRT` | 6 | `abort()`, a failed `assert` | core dump | yes |
| `SIGALRM` | 14 | timer set by `alarm()` | terminate | yes |
| `SIGCHLD` | 17 | child process exited | ignore | yes |
| `SIGUSR1/2` | 10/12 | user-defined | terminate | yes |
| `SIGSTOP` | 19 | stop the process | stop | **no** |

**Sending**: `raise(sig)` (to self, standard C), `kill(pid, sig)` (POSIX), `alarm(secs)`, `kill -INT <pid>` from the shell.

**Handling** — prefer **`sigaction`** (POSIX) over `signal()`, whose behaviour varies between systems.

**Example** — [examples/10_signals.c](examples/10_signals.c)
```c
static volatile sig_atomic_t got_sigint = 0;   /* the only safe thing for a handler to touch */

static void handler(int sig)
{
    if (sig == SIGINT) got_sigint = 1;         /* just set a flag. No printf! */
}

struct sigaction sa = {0};
sa.sa_handler = handler;
sigemptyset(&sa.sa_mask);
sigaction(SIGINT, &sa, NULL);
sigaction(SIGALRM, &sa, NULL);

alarm(3);                                      /* SIGALRM in 3 seconds */
while (!got_sigint && !got_alarm)
    pause();                                   /* sleep until a signal arrives */
if (got_sigint) printf("caught SIGINT from keyboard, cleaning up\n");
```
```
$ ./sig                                  (press Ctrl+C)
caught SIGUSR1 (via raise)
caught SIGINT (via kill) - program keeps running
press Ctrl+C within 3 seconds (or wait for SIGALRM)...
^Ccaught SIGINT from keyboard, cleaning up
exiting normally

$ ./sig                                  (wait 3 s)
...
caught SIGALRM: timeout
exiting normally
```

**Key points / pitfalls**
- A handler can run **at any moment**, even in the middle of `malloc` or `printf` in the main code. It may only call **async-signal-safe** functions (`write`, `_exit`, …). **Not** `printf`, `malloc` or `exit`.
- The standard pattern: the handler sets a `volatile sig_atomic_t` flag, and the main loop checks it and does the real work.
- `SIGKILL` and `SIGSTOP` can't be caught, blocked or ignored.
- Returning from a `SIGSEGV`/`SIGFPE` handler re-runs the faulting instruction (UB). Only log and `_exit`.
- Use `SIG_IGN` to ignore a signal and `SIG_DFL` to restore the default action. `sigprocmask` blocks signals temporarily.
- Signals interrupt blocking calls like `read`, which then fail with `errno == EINTR`. Use `SA_RESTART` to retry them automatically.

**Interview Qs**
- *What is a signal?* An asynchronous software interrupt delivered to a process, such as SIGINT from Ctrl+C.
- *Which signals can't be caught?* `SIGKILL` and `SIGSTOP`.
- *Why can't you call `printf` in a signal handler?* It isn't async-signal-safe. If the signal interrupted another `printf` or `malloc`, their internal state is inconsistent.
- *`SIGTERM` vs `SIGKILL`?* `SIGTERM` asks the process to exit and can be handled for cleanup. `SIGKILL` ends it immediately.

---

## 4. Socket Programming

**What it is** — A **socket** is an endpoint for network communication, used through a file descriptor (so `read`/`write`/`close` work on it too). **TCP** (`SOCK_STREAM`) gives a reliable, ordered byte stream. **UDP** (`SOCK_DGRAM`) gives fast, unreliable datagrams.

**TCP flow**
```
        SERVER                                  CLIENT
  socket()                                 socket()
     │                                        │
  bind(127.0.0.1:9090)                        │
     │                                        │
  listen()                                    │
     │                                        │
  accept() ── blocks ── ◄─── 3-way handshake ── connect()
     │  returns NEW fd for this client        │
  recv() ◄──────────── "hello" ────────────  send()
  send() ───────────── "HELLO" ───────────► recv()
     │                                        │
  close()                                  close()
```

| Call | Purpose |
|------|---------|
| `socket(AF_INET, SOCK_STREAM, 0)` | create an IPv4 TCP socket → fd |
| `setsockopt(..., SO_REUSEADDR, ...)` | allow restarting the server on the same port immediately |
| `bind(fd, addr, len)` | attach the socket to a local IP:port |
| `listen(fd, backlog)` | start accepting connections, with a queue of `backlog` pending ones |
| `accept(fd, &client, &len)` | wait for a client. Returns a **new fd** for that connection |
| `connect(fd, addr, len)` | (client) connect to a server |
| `send`/`recv` (or `write`/`read`) | transfer bytes |
| `htons`/`htonl`, `ntohs`/`ntohl` | convert between host and **network byte order** (big-endian) |
| `inet_pton` / `inet_ntop` | text IP ↔ binary address |

**Examples** — [examples/10_socket_server.c](examples/10_socket_server.c) and [examples/10_socket_client.c](examples/10_socket_client.c)
```c
/* server */
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in addr = {0};
addr.sin_family = AF_INET;
addr.sin_port = htons(9090);                     /* byte order! */
addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);   /* 127.0.0.1 */
bind(server_fd, (struct sockaddr *)&addr, sizeof addr);
listen(server_fd, 5);
int client_fd = accept(server_fd, (struct sockaddr *)&client, &len);
ssize_t n = recv(client_fd, buf, sizeof buf - 1, 0);
/* ... uppercase buf ... */
send(client_fd, buf, n, 0);
close(client_fd); close(server_fd);

/* client */
int fd = socket(AF_INET, SOCK_STREAM, 0);
inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
connect(fd, (struct sockaddr *)&addr, sizeof addr);
send(fd, msg, strlen(msg), 0);
recv(fd, buf, sizeof buf - 1, 0);
```
```
terminal 1                                        terminal 2
$ ./server                                        $ ./client "hello from client"
server: listening on 127.0.0.1:9090               client: sent "hello from client", got back "HELLO FROM CLIENT"
server: client connected from 127.0.0.1:46506
server: received "hello from client"
server: done
```
You can also test the server with `nc 127.0.0.1 9090`.

**Key points / pitfalls**
- **Always convert ports and addresses to network byte order** (`htons`, `htonl`). Forgetting this is the classic bug: port 9090 becomes 33315 on little-endian machines.
- TCP is a **byte stream, not messages**. One `send` may arrive as several `recv`s, and several sends may arrive in one. Real protocols add framing (a length prefix or a delimiter) and loop on `recv`.
- `recv` returning **0** means the peer closed the connection.
- This server handles **one client** and exits. Real servers loop on `accept` and handle clients concurrently with `fork`, threads (§6), or `poll`/`epoll`.
- `bind: Address already in use` → another process holds the port, or the previous run is in TIME_WAIT. `SO_REUSEADDR` helps.
- Binding to `INADDR_ANY` (0.0.0.0) instead of loopback exposes the server to the network.

**Interview Qs**
- *Steps for a TCP server?* `socket` → `bind` → `listen` → `accept` → `recv`/`send` → `close`.
- *Steps for a TCP client?* `socket` → `connect` → `send`/`recv` → `close`.
- *Why `htons`?* Network protocols use big-endian byte order. `htons` converts a 16-bit value from host order.
- *TCP vs UDP?* TCP is connection-oriented, reliable and ordered. UDP is connectionless and faster, but can lose or reorder packets.

---

## 5. _Generic Keyword

**What it is** — C11's `_Generic` picks an expression **at compile time** based on the **type** of a controlling expression. It is C's way of getting type-generic macros, a limited form of function overloading. `<tgmath.h>` uses it so that `sqrt(x)` works for float, double and long double.

**Syntax**
```c
_Generic( expr,
    type1: result1,
    type2: result2,
    default: result_default )      /* default is optional; without it, an unlisted type is an error */
```
`expr` is **not evaluated**. Only its type matters.

**Example** — [examples/10_generic.c](examples/10_generic.c)
```c
#define TYPE_NAME(x) _Generic((x), int: "int", double: "double", char *: "char *", default: "other")

#define PRINT(x) _Generic((x),   \
    int:          print_int,     \
    double:       print_double,  \
    char *:       print_str,     \
    const char *: print_str)(x)  /* select a FUNCTION, then call it */

#define ABS(x) _Generic((x), int: abs, long: labs, float: fabsf, double: fabs)(x)

#define MAX(a, b) _Generic((a) + (b), int: max_i, double: max_d)(a, b)   /* no double evaluation */
```
Output:
```
TYPE_NAME: int double float char char * long other
TYPE_NAME('x') = int   (character constants are int in C!)
TYPE_NAME(c + 1) = int (char promoted to int in arithmetic)
int: 42
double: 3.142
string: "generic"
ABS(-7) = 7, ABS(-7L) = 7, ABS(-2.5) = 2.5
MAX(3, 9) = 9, MAX(2.5, 1.0) = 2.5, MAX(2, 1.5) = 2.0
```

**Key points / pitfalls**
- Types must match **exactly**: `short` fell through to `default`. `char *` and `const char *` are different types. List every type you need.
- In C, `'x'` has type **`int`**, not `char` (C++ differs). Arithmetic promotes `char`/`short` to `int`.
- Arrays decay to pointers in the controlling expression, so `char[10]` matches `char *`.
- Using `(a) + (b)` as the controlling expression applies the usual arithmetic conversions, so mixed `int` + `double` selects `double`.
- `_Generic` selects; it doesn't convert. The chosen function still receives the original argument.

**Interview Qs**
- *What is `_Generic`?* A C11 compile-time selection on the type of an expression, used to build type-generic macros.
- *Does C support function overloading?* No, but `_Generic` macros can emulate it.

---

## 6. Multithreading

**What it is**
- A **thread** is an independent flow of execution **inside one process**. All threads share the same memory (globals, heap) but each has **its own stack** and registers.
- Threads let a program use multiple CPU cores, or keep working while waiting for I/O.
- C uses **POSIX threads (pthreads)** (`<pthread.h>`, compile with `-pthread`). C11 also defines `<threads.h>` (`thrd_create`, `mtx_lock`), but it is less widely used.

| Function | Purpose |
|----------|---------|
| `pthread_create(&tid, NULL, func, arg)` | start `void *func(void *arg)` in a new thread |
| `pthread_join(tid, &retval)` | wait for a thread to finish (and collect its return value) |
| `pthread_detach(tid)` | let a thread clean itself up; no join needed |
| `pthread_self()` | the calling thread's ID |
| `pthread_mutex_lock` / `unlock` | mutual exclusion: one thread at a time in a critical section |
| `pthread_cond_wait` / `signal` | condition variables: wait for or notify about a state change |

**Example** — [examples/10_threads.c](examples/10_threads.c)
```c
typedef struct { int id; long from, to; long result; } Task;   /* pass args via a struct */

void *partial_sum(void *arg)
{
    Task *t = arg;
    for (long i = t->from; i <= t->to; i++) t->result += i;
    return NULL;
}

for (int i = 0; i < 4; i++) pthread_create(&th[i], NULL, partial_sum, &tasks[i]);
for (int i = 0; i < 4; i++) pthread_join(th[i], NULL);

/* race condition */
void *inc_unsafe(void *arg) { for (...) counter_unsafe++; }        /* NOT atomic */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *inc_safe(void *arg) {
    for (...) {
        pthread_mutex_lock(&lock);
        counter_safe++;                                            /* critical section */
        pthread_mutex_unlock(&lock);
    }
}
```
```
$ gcc -Wall -Wextra -std=c11 -pthread 10_threads.c -o threads && ./threads
thread 0 summed 1..250000 = 31250125000
thread 1 summed 250001..500000 = 93750125000
thread 2 summed 500001..750000 = 156250125000
thread 3 summed 750001..1000000 = 218750125000
total = 500000500000 (expected 500000500000)
expected count  = 4000000
without mutex   = 1262955  <- lost updates (varies run to run)
with mutex      = 4000000
```

**Why `counter++` loses updates**: it is really three steps (load, add, store). Two threads can interleave them:
```
Thread A: load 5          add → 6   store 6
Thread B:      load 5  add → 6               store 6     ← one increment lost
```
ThreadSanitizer finds this automatically:
```
$ gcc -g -pthread -fsanitize=thread 10_threads.c && ./a.out
WARNING: ThreadSanitizer: data race
    #0 inc_unsafe 10_threads.c:34
```

**Key points / pitfalls**
- **Data race**: two threads access the same memory at the same time, at least one writes, and there is no synchronisation. That is **UB**. Protect shared data with a mutex, or use C11 `<stdatomic.h>` (`atomic_long counter; atomic_fetch_add(&counter, 1);`).
- **Deadlock**: thread 1 holds lock A and waits for B, while thread 2 holds B and waits for A. Always acquire locks **in the same order**.
- Keep critical sections **short**. Locking inside a tight loop (as in the demo) is correct but slow.
- Don't pass the address of a loop variable to `pthread_create` (`&i`). The loop changes `i` before the thread reads it. Give each thread its own data (`&tasks[i]`).
- Don't return a pointer to a thread's local variable from the thread function. Its stack is gone after it exits.
- Functions with hidden static state are not thread-safe: `strtok`, `localtime`, `rand`. Use `strtok_r`, `localtime_r`, `rand_r`.
- `volatile` does **not** make code thread-safe. Use mutexes or atomics.

**Interview Qs**
- *Process vs thread?* Processes have separate address spaces. Threads in a process share memory but each has its own stack.
- *What is a race condition and how do you prevent it?* The result depends on the timing of unsynchronised access to shared data. Prevent it with mutexes, atomics, or by not sharing.
- *What is a deadlock?* Threads waiting on each other's locks forever. Avoid it with a consistent lock order.
- *What does `pthread_join` do?* It blocks until the given thread terminates and collects its return value.

---

### Quick revision
- **Variadic**: `va_list`, `va_start(ap, last)`, `va_arg(ap, T)`, `va_end`. Pass a count, sentinel or format. `float`→`double`, `char`→`int`. Use `vprintf` to forward.
- **Syscalls**: `open`/`read`/`write`/`lseek`/`close` on int fds (0, 1, 2 = stdin, stdout, stderr). Unbuffered. Partial reads and writes happen. `read` 0 = EOF.
- **Signals**: install with `sigaction`. In the handler, only set a `volatile sig_atomic_t` flag. `SIGKILL`/`SIGSTOP` can't be caught.
- **Sockets**: server `socket→bind→listen→accept→recv/send→close`, client `socket→connect→send/recv→close`. Use `htons`. TCP is a byte stream.
- **_Generic**: compile-time selection by type, giving type-generic macros. Exact type match. `'x'` is `int`.
- **Threads**: `pthread_create`/`join`, compile with `-pthread`. Shared data needs a mutex or atomics. Watch for races and deadlocks. Use `-fsanitize=thread`.
