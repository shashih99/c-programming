/* 07_read_whole_file.c - read an entire file into a heap buffer
 * Usage: ./prog [file]   (defaults to reading its own source) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(const char *path, long *out_size)
{
    FILE *fp = fopen(path, "rb");               /* binary: exact bytes, no translation */
    if (!fp) return NULL;

    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return NULL; }
    long size = ftell(fp);                      /* file size in bytes */
    if (size < 0) { fclose(fp); return NULL; }
    rewind(fp);

    char *buf = malloc(size + 1);               /* +1 for '\0' */
    if (!buf) { fclose(fp); return NULL; }

    size_t got = fread(buf, 1, size, fp);
    fclose(fp);
    if (got != (size_t)size) { free(buf); return NULL; }

    buf[size] = '\0';                           /* make it a C string */
    if (out_size) *out_size = size;
    return buf;                                 /* caller must free */
}

int main(int argc, char *argv[])
{
    const char *path = argc > 1 ? argv[1] : "07_read_whole_file.c";
    long size;
    char *text = read_file(path, &size);
    if (!text) { perror(path); return EXIT_FAILURE; }

    int lines = 0;
    for (long i = 0; i < size; i++)
        if (text[i] == '\n') lines++;
    printf("%s: %ld bytes, %d lines\n", path, size, lines);
    printf("first line: %.*s\n", (int)strcspn(text, "\n"), text);
    free(text);
    return 0;
}
