/* 07_delete_rename.c - remove(), rename(), checking existence, tmpfile() */
#include <stdio.h>
#include <stdlib.h>

int exists(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp) { fclose(fp); return 1; }
    return 0;
}

int main(void)
{
    FILE *fp = fopen("old_name.txt", "w");
    if (!fp) { perror("fopen"); return EXIT_FAILURE; }
    fputs("temporary\n", fp);
    fclose(fp);
    printf("old_name.txt exists? %d\n", exists("old_name.txt"));

    if (rename("old_name.txt", "new_name.txt") == 0)
        printf("renamed -> new_name.txt exists? %d\n", exists("new_name.txt"));
    else
        perror("rename");

    if (remove("new_name.txt") == 0)
        printf("removed -> new_name.txt exists? %d\n", exists("new_name.txt"));
    else
        perror("remove");

    if (remove("no_such_file.txt") != 0)
        perror("remove no_such_file.txt");      /* shows the reason from errno */

    FILE *tmp = tmpfile();                       /* anonymous, auto-deleted on close/exit */
    if (tmp) {
        fputs("scratch data", tmp);
        rewind(tmp);
        char buf[32];
        if (fgets(buf, sizeof buf, tmp))
            printf("tmpfile contains: %s\n", buf);
        fclose(tmp);
    }
    return 0;
}
