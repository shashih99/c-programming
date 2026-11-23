/* 08_file_errors.c - checking every file operation: fopen, ferror, fclose, writing to /dev/full */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    /* 1. fopen failure */
    FILE *fp = fopen("missing.txt", "r");
    if (!fp)
        printf("fopen missing.txt failed: %s\n", strerror(errno));

    /* 2. ferror: reading from a stream opened for writing */
    fp = fopen("err_demo.txt", "w");
    if (!fp) { perror("fopen"); return EXIT_FAILURE; }
    int c = fgetc(fp);                              /* invalid on a write-only stream */
    printf("fgetc on write-only stream -> %d, ferror = %d, feof = %d\n",
           c, ferror(fp) != 0, feof(fp) != 0);
    clearerr(fp);
    printf("after clearerr, ferror = %d\n", ferror(fp) != 0);
    fclose(fp);
    remove("err_demo.txt");

    /* 3. write errors often appear only at fflush/fclose (buffering!) */
    fp = fopen("/dev/full", "w");                   /* Linux: every write fails with ENOSPC */
    if (fp) {
        int r = fprintf(fp, "hello");               /* goes into the buffer: looks fine */
        printf("fprintf to /dev/full returned %d (buffered, no error yet)\n", r);
        errno = 0;
        if (fclose(fp) == EOF)                      /* flush happens here -> error */
            printf("fclose failed: %s\n", strerror(errno));
    }
    return EXIT_SUCCESS;
}
