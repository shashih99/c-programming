/* 03_strings.c - char arrays vs string literals, '\0', reading strings */
#include <stdio.h>
#include <string.h>

int my_strlen(const char *s)
{
    int n = 0;
    while (s[n] != '\0')
        n++;
    return n;
}

int main(void)
{
    char s1[] = "hello";                 /* array of 6: h e l l o \0 (modifiable copy) */
    char s2[10] = "hi";                  /* rest filled with \0 */
    char s3[] = {'a', 'b', 'c', '\0'};   /* explicit terminator */
    const char *p = "world";             /* pointer to READ-ONLY literal */

    printf("s1 = %s, sizeof = %zu, strlen = %zu\n", s1, sizeof(s1), strlen(s1));
    printf("s2 = %s, sizeof = %zu, strlen = %zu\n", s2, sizeof(s2), strlen(s2));
    printf("s3 = %s, my_strlen = %d\n", s3, my_strlen(s3));
    printf("p  = %s, sizeof(p) = %zu (pointer)\n", p, sizeof(p));

    s1[0] = 'H';                         /* OK: s1 is our own array */
    printf("modified s1 = %s\n", s1);
    /* p[0] = 'W';  -> undefined behaviour: string literals are read-only */

    printf("chars of s1: ");
    for (int i = 0; s1[i]; i++)          /* loop until '\0' (which is 0 = false) */
        printf("'%c'(%d) ", s1[i], s1[i]);
    printf("\n");

    char line[32];
    printf("Enter a line: ");
    if (fgets(line, sizeof line, stdin)) {          /* safe: reads at most 31 chars */
        line[strcspn(line, "\n")] = '\0';           /* strip trailing newline */
        printf("You typed: \"%s\" (%zu chars)\n", line, strlen(line));
    }
    return 0;
}
