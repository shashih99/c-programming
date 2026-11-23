/* 07_struct_io.c - write/read structs in binary with fwrite/fread, random access with fseek */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[16];
    float salary;
} Employee;

int main(void)
{
    const char *path = "employees.dat";
    Employee staff[] = {
        {101, "Asha",  52000.0f},
        {102, "Ravi",  48500.5f},
        {103, "Meena", 61000.0f},
    };
    size_t n = sizeof staff / sizeof staff[0];

    FILE *fp = fopen(path, "wb");
    if (!fp) { perror("fopen wb"); return EXIT_FAILURE; }
    size_t written = fwrite(staff, sizeof(Employee), n, fp);   /* whole array at once */
    fclose(fp);
    printf("wrote %zu records (%zu bytes each)\n", written, sizeof(Employee));

    fp = fopen(path, "rb");
    if (!fp) { perror("fopen rb"); return EXIT_FAILURE; }

    Employee e;
    printf("sequential read:\n");
    while (fread(&e, sizeof e, 1, fp) == 1)                    /* one record at a time */
        printf("  %d %-6s %.2f\n", e.id, e.name, e.salary);

    long idx = 2;                                              /* jump straight to record #2 */
    fseek(fp, idx * (long)sizeof(Employee), SEEK_SET);
    if (fread(&e, sizeof e, 1, fp) == 1)
        printf("random access record %ld: %s\n", idx, e.name);
    fclose(fp);

    /* update record #1 in place with "r+b" */
    fp = fopen(path, "r+b");
    if (!fp) { perror("fopen r+b"); return EXIT_FAILURE; }
    fseek(fp, 1 * (long)sizeof(Employee), SEEK_SET);
    if (fread(&e, sizeof e, 1, fp) != 1) { fclose(fp); return EXIT_FAILURE; }
    e.salary += 1500.0f;
    fseek(fp, -(long)sizeof(Employee), SEEK_CUR);              /* step back over it */
    fwrite(&e, sizeof e, 1, fp);
    rewind(fp);
    Employee all[3];
    size_t got = fread(all, sizeof(Employee), 3, fp);
    fclose(fp);
    printf("after update (%zu read): %s now earns %.2f\n", got, all[1].name, all[1].salary);

    remove(path);
    return 0;
}
