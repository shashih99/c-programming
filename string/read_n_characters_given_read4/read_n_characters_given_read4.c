#include <stdio.h>
#include <string.h>

/**
 * Read N Characters Given Read4 (LeetCode 157)
 *
 * We may only read the file through read4(), which copies up to 4 chars
 * into buf4 and returns how many it actually read (0..4).
 * Implement read(buf, n): copy up to n chars into buf, return count read.
 *
 * Time:  O(n)   Space: O(1) (a 4-char temp buffer)
 */

/* ---------- simulated file + read4 (LeetCode provides this) ---------- */
static const char *g_file = "";
static int g_pos = 0;

static void setFile(const char *content) {
    g_file = content;
    g_pos = 0;
}

int read4(char *buf4) {
    int len = (int)strlen(g_file);
    int count = 0;
    while (count < 4 && g_pos < len) {
        buf4[count++] = g_file[g_pos++];
    }
    return count;
}

/* ---------------------------- solution ---------------------------- */
int readN(char *buf, int n) {
    char buf4[4];
    int total = 0;

    while (total < n) {
        int got = read4(buf4);          /* pull next chunk from file   */
        if (got == 0) break;            /* EOF                         */

        int take = got;                 /* don't exceed n              */
        if (take > n - total) take = n - total;

        memcpy(buf + total, buf4, take);
        total += take;

        if (got < 4) break;             /* short read => EOF reached   */
    }
    return total;
}

/* ----------------------------- tests ------------------------------ */
static int run(const char *file, int n, const char *expected) {
    char buf[1024] = {0};
    setFile(file);
    int got = readN(buf, n);
    buf[got] = '\0';
    int ok = (got == (int)strlen(expected)) && strcmp(buf, expected) == 0;
    printf("%s file=\"%s\" n=%d -> %d \"%s\" (expected \"%s\")\n",
           ok ? "PASS" : "FAIL", file, n, got, buf, expected);
    return ok;
}

int main(void) {
    int pass = 0, total = 0;
    total++; pass += run("abc", 4, "abc");              /* file shorter than n  */
    total++; pass += run("abcde", 5, "abcde");          /* not multiple of 4    */
    total++; pass += run("abcdABCD1234", 12, "abcdABCD1234"); /* exact multiple */
    total++; pass += run("leetcode", 5, "leetc");       /* n smaller than file  */
    total++; pass += run("", 3, "");                    /* empty file           */
    total++; pass += run("abcdef", 0, "");              /* n = 0                */
    total++; pass += run("abcdefgh", 4, "abcd");        /* n exactly one chunk  */
    printf("\n%d/%d tests passed\n", pass, total);
    return pass == total ? 0 : 1;
}
