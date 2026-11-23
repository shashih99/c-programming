/* 03_string_functions.c - common <string.h> and <ctype.h> functions */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char dst[32];

    strcpy(dst, "Hello");                          /* copy */
    printf("strcpy  : %s\n", dst);

    strcat(dst, ", World");                        /* append */
    printf("strcat  : %s (len %zu)\n", dst, strlen(dst));

    char small[6];
    strncpy(small, "abcdefgh", sizeof small - 1);  /* copy at most 5 chars */
    small[sizeof small - 1] = '\0';                /* strncpy may NOT terminate! */
    printf("strncpy : %s\n", small);

    char buf[16];
    snprintf(buf, sizeof buf, "%s-%d", "id", 42);  /* safest way to build strings */
    printf("snprintf: %s\n", buf);

    printf("strcmp(\"apple\",\"banana\") = %d\n", strcmp("apple", "banana") < 0 ? -1 : 1);
    printf("strcmp(\"abc\",\"abc\")      = %d\n", strcmp("abc", "abc"));
    printf("strncmp(\"hello\",\"help\",3) = %d\n", strncmp("hello", "help", 3));

    const char *text = "the quick brown fox";
    printf("strchr(text,'q')  -> \"%s\"\n", strchr(text, 'q'));
    printf("strrchr(text,'o') -> \"%s\"\n", strrchr(text, 'o'));
    printf("strstr(text,\"brown\") at index %td\n", strstr(text, "brown") - text);
    printf("strstr(text,\"cat\") = %s\n", strstr(text, "cat") ? "found" : "NULL");

    char csv[] = "red,green,,blue";               /* strtok MODIFIES its input */
    printf("strtok  : ");
    for (char *tok = strtok(csv, ","); tok; tok = strtok(NULL, ","))
        printf("[%s] ", tok);
    printf("\n");

    char word[] = "Hello123";
    int letters = 0, digits = 0;
    for (int i = 0; word[i]; i++) {
        if (isalpha((unsigned char)word[i])) letters++;
        if (isdigit((unsigned char)word[i])) digits++;
        word[i] = toupper((unsigned char)word[i]);
    }
    printf("ctype   : %s letters=%d digits=%d\n", word, letters, digits);

    char mem[8];
    memset(mem, '*', 7); mem[7] = '\0';
    printf("memset  : %s\n", mem);
    return 0;
}
