/* 09_storage_classes.c - auto, register, static (local and global), extern */
#include <stdio.h>

int global_counter = 0;             /* static storage, external linkage */
static int file_private = 100;      /* static storage, internal linkage (this file only) */

void counter_demo(void)
{
    auto int a = 0;                 /* 'auto' is the default for locals: rarely written */
    static int s = 0;               /* initialised ONCE, keeps value between calls */
    register int r = 0;             /* hint: keep in a register (cannot take &r) */
    a++; s++; r++;
    global_counter++;
    printf("  auto a = %d, static s = %d, register r = %d, global = %d\n", a, s, r, global_counter);
}

int next_id(void)                   /* classic use of a static local */
{
    static int id = 1000;
    return id++;
}

void use_extern(void)
{
    extern int defined_later;       /* declaration: the definition is further down */
    printf("extern defined_later = %d\n", defined_later);
}

int defined_later = 7;              /* definition */

int main(void)
{
    for (int i = 0; i < 3; i++)
        counter_demo();

    int id1 = next_id();            /* call separately: the order in which function   */
    int id2 = next_id();            /* ARGUMENTS are evaluated is unspecified, so      */
    int id3 = next_id();            /* printf("%d %d", next_id(), next_id()) may print */
    printf("ids: %d %d %d\n", id1, id2, id3);   /* them in any order               */
    printf("file_private = %d\n", file_private);
    use_extern();

    {
        int x = 1;                  /* block scope */
        {
            int x = 2;              /* shadows the outer x */
            printf("inner x = %d\n", x);
        }
        printf("outer x = %d\n", x);
    }
    return 0;
}
