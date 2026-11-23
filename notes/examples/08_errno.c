/* 08_errno.c - errno, perror, strerror, exit status, safe number parsing */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

/* parse a whole string as int; returns 0 on success, -1 on error */
int parse_int(const char *s, int *out)
{
    char *end;
    errno = 0;                                   /* MUST reset: functions only SET errno */
    long v = strtol(s, &end, 10);
    if (end == s)               { fprintf(stderr, "  \"%s\": not a number\n", s); return -1; }
    if (*end != '\0')           { fprintf(stderr, "  \"%s\": trailing junk \"%s\"\n", s, end); return -1; }
    if (errno == ERANGE || v < INT_MIN || v > INT_MAX)
                                { fprintf(stderr, "  \"%s\": out of int range\n", s); return -1; }
    *out = (int)v;
    return 0;
}

int main(void)
{
    FILE *fp = fopen("/no/such/dir/file.txt", "r");
    if (fp == NULL) {
        int saved = errno;                        /* save it: the next call may overwrite errno */
        printf("errno = %d\n", saved);
        printf("strerror: %s\n", strerror(saved));
        perror("perror  ");                       /* "<msg>: <strerror(errno)>" on stderr */
        fflush(stderr);
    }

    errno = 0;
    double r = sqrt(-1.0);
    printf("sqrt(-1) = %f, errno = %d (%s)\n", r, errno, errno == EDOM ? "EDOM" : "other");

    const char *inputs[] = {"42", "abc", "12xy", "99999999999", "-7"};
    for (int i = 0; i < 5; i++) {
        int v;
        if (parse_int(inputs[i], &v) == 0)
            printf("  \"%s\" -> %d\n", inputs[i], v);
        fflush(stdout); fflush(stderr);
    }

    printf("EXIT_SUCCESS = %d, EXIT_FAILURE = %d\n", EXIT_SUCCESS, EXIT_FAILURE);
    return EXIT_SUCCESS;
}
