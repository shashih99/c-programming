/* 08_goto_cleanup.c - single-exit cleanup with goto (the "exception handling" idiom in C) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copies src to dst through a heap buffer. Every failure jumps to the right cleanup label,
   which releases ONLY what has been acquired so far, in reverse order. */
int copy_file(const char *src, const char *dst)
{
    int status = -1;                     /* assume failure */
    FILE *in = NULL, *out = NULL;
    char *buf = NULL;

    in = fopen(src, "rb");
    if (!in) { perror(src); goto cleanup; }

    out = fopen(dst, "wb");
    if (!out) { perror(dst); goto cleanup; }

    buf = malloc(4096);
    if (!buf) { perror("malloc"); goto cleanup; }

    size_t n;
    while ((n = fread(buf, 1, 4096, in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) { perror("fwrite"); goto cleanup; }
    }
    if (ferror(in)) { perror("fread"); goto cleanup; }

    status = 0;                          /* success */

cleanup:                                 /* free(NULL) and the NULL checks make this safe */
    free(buf);
    if (out && fclose(out) != 0) { perror("fclose"); status = -1; }
    if (in) fclose(in);
    return status;
}

int main(void)
{
    FILE *fp = fopen("src_demo.txt", "w");
    if (!fp) { perror("setup"); return EXIT_FAILURE; }
    fputs("copy me\n", fp);
    fclose(fp);

    printf("copy existing file : %s\n", copy_file("src_demo.txt", "dst_demo.txt") == 0 ? "ok" : "failed");
    fflush(stdout);
    printf("copy missing file  : %s\n", copy_file("missing.txt", "dst_demo.txt") == 0 ? "ok" : "failed");
    fflush(stdout);
    printf("copy to bad path   : %s\n", copy_file("src_demo.txt", "/no/dir/out.txt") == 0 ? "ok" : "failed");

    remove("src_demo.txt");
    remove("dst_demo.txt");
    return EXIT_SUCCESS;
}
