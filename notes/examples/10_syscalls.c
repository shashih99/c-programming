/* 10_syscalls.c - low-level POSIX I/O: open, read, write, lseek, close (Linux/macOS) */
#define _POSIX_C_SOURCE 200809L          /* expose POSIX functions under -std=c11 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>                       /* open, O_* flags */
#include <unistd.h>                      /* read, write, lseek, close, STDOUT_FILENO */
#include <sys/stat.h>                    /* fstat, mode bits */

int main(void)
{
    const char *path = "syscall_demo.txt";

    /* open: returns a small int "file descriptor", or -1 on error */
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);   /* rw-r--r-- */
    if (fd == -1) { perror("open"); return 1; }
    printf("opened %s as fd %d (0,1,2 are stdin, stdout, stderr)\n", path, fd);

    const char *text = "Hello from write()\nSecond line\n";
    ssize_t n = write(fd, text, strlen(text));                  /* unbuffered: goes to the kernel now */
    if (n == -1) { perror("write"); close(fd); return 1; }
    printf("write() wrote %zd bytes\n", n);
    close(fd);

    fd = open(path, O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }

    struct stat st;
    if (fstat(fd, &st) == 0)
        printf("fstat: size = %lld bytes, mode = %o\n", (long long)st.st_size, (unsigned)(st.st_mode & 0777));

    char buf[64];
    ssize_t got;
    printf("read() loop:\n");
    fflush(stdout);                                             /* flush stdio before mixing with write(1, ...) */
    while ((got = read(fd, buf, 10)) > 0)                       /* 0 = EOF, -1 = error */
        write(STDOUT_FILENO, buf, got);                         /* fd 1 directly */

    off_t pos = lseek(fd, 6, SEEK_SET);                         /* move to byte 6 */
    got = read(fd, buf, 4);
    printf("lseek(6) -> %lld, next 4 bytes: \"%.*s\"\n", (long long)pos, (int)got, buf);

    close(fd);
    unlink(path);                                               /* POSIX delete */

    if (open("/no/such/file", O_RDONLY) == -1)
        perror("open /no/such/file");
    return 0;
}
