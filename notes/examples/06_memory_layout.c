/* 06_memory_layout.c - where things live: text, rodata, data, bss, heap, stack */
#include <stdio.h>
#include <stdlib.h>

int global_init = 10;          /* .data  : initialised globals/statics          */
int global_uninit;             /* .bss   : uninitialised (zeroed) globals/statics */
static int static_global = 5;  /* .data                                         */
const char *msg = "hello";     /* msg in .data, the literal "hello" in .rodata  */

void func(void) {}             /* .text  : machine code                         */

void stack_depth(int n)
{
    int local;
    printf("  depth %d: &local = %p\n", n, (void *)&local);
    if (n < 2) stack_depth(n + 1);
}

int main(void)
{
    static int static_local;   /* .bss (zero, lives for the whole program)      */
    int local = 1;             /* stack                                         */
    int *heap = malloc(sizeof *heap);   /* heap                                 */
    if (!heap) return 1;

    printf("text   : func           = %p\n", (void *)func);
    printf("rodata : \"hello\"        = %p\n", (void *)msg);
    printf("data   : global_init    = %p\n", (void *)&global_init);
    printf("data   : static_global  = %p\n", (void *)&static_global);
    printf("bss    : global_uninit  = %p (value %d)\n", (void *)&global_uninit, global_uninit);
    printf("bss    : static_local   = %p (value %d)\n", (void *)&static_local, static_local);
    printf("heap   : heap           = %p\n", (void *)heap);
    printf("stack  : local          = %p\n", (void *)&local);
    printf("stack grows downward:\n");
    stack_depth(0);

    free(heap);
    return 0;
}
