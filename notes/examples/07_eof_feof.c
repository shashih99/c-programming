/* 07_eof_feof.c - EOF, getc, feof, ferror, and the while(!feof()) bug */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const char *path = "eof_demo.txt";
    FILE *fp = fopen(path, "w");
    if (!fp) { perror("fopen"); return EXIT_FAILURE; }
    fputs("abc\n", fp);
    fclose(fp);

    printf("EOF macro = %d\n", EOF);

    fp = fopen(path, "r");
    if (!fp) { perror("fopen"); return EXIT_FAILURE; }

    /* WRONG: feof() only becomes true AFTER a read has failed */
    int count = 0;
    while (!feof(fp)) {
        int c = getc(fp);
        (void)c;
        count++;                       /* counts the failed read too */
    }
    printf("while(!feof) loop ran %d times (file has 4 chars)\n", count);

    /* RIGHT: test the return value of the read itself */
    rewind(fp);                        /* also clears the EOF flag */
    count = 0;
    int c;
    while ((c = getc(fp)) != EOF)
        count++;
    printf("while((c = getc(fp)) != EOF) ran %d times\n", count);

    /* after the loop: WHY did it stop? */
    if (feof(fp))        printf("stopped: end of file reached\n");
    else if (ferror(fp)) printf("stopped: read error\n");

    clearerr(fp);                      /* reset EOF / error flags */
    printf("after clearerr, feof = %d\n", feof(fp));
    fclose(fp);
    remove(path);
    return 0;
}
