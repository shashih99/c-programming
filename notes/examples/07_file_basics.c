/* 07_file_basics.c - fopen modes, writing and reading text files */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char *path = "notes_demo.txt";

    /* ---- write ("w": create or TRUNCATE) ---- */
    FILE *fp = fopen(path, "w");
    if (fp == NULL) { perror("fopen for write"); return EXIT_FAILURE; }
    fputc('#', fp);                             /* one char        */
    fputs(" Scores\n", fp);                     /* a string        */
    fprintf(fp, "%s %d\n", "asha", 91);         /* formatted       */
    fprintf(fp, "%s %d\n", "ravi", 78);
    fclose(fp);

    /* ---- append ("a": write at end, create if missing) ---- */
    fp = fopen(path, "a");
    if (!fp) { perror("fopen for append"); return EXIT_FAILURE; }
    fprintf(fp, "%s %d\n", "meena", 85);
    fclose(fp);

    /* ---- read char by char ---- */
    fp = fopen(path, "r");
    if (!fp) { perror("fopen for read"); return EXIT_FAILURE; }
    int ch, chars = 0, lines = 0;               /* ch is int, not char: must hold EOF */
    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n') lines++;
    }
    printf("fgetc : %d chars, %d lines\n", chars, lines);

    /* ---- read line by line (rewind to start) ---- */
    rewind(fp);
    char line[64];
    printf("fgets :\n");
    while (fgets(line, sizeof line, fp) != NULL)
        printf("  | %s", line);                 /* line already ends in '\n' */

    /* ---- read formatted (skip header line first) ---- */
    rewind(fp);
    fgets(line, sizeof line, fp);
    char name[16];
    int score, total = 0, n = 0;
    while (fscanf(fp, "%15s %d", name, &score) == 2) {   /* check items matched */
        total += score;
        n++;
    }
    printf("fscanf: %d students, average %.1f\n", n, (double)total / n);

    /* ---- position ---- */
    fseek(fp, 0, SEEK_END);
    printf("ftell at end = %ld bytes\n", ftell(fp));
    fclose(fp);

    remove(path);                               /* clean up demo file */
    return 0;
}
