/* 02_main_args.c - command-line arguments and return codes */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = \"%s\"\n", i, argv[i]);

    if (argc < 3) {
        fprintf(stderr, "usage: %s <num1> <num2>\n", argv[0]);
        return EXIT_FAILURE;            /* non-zero = failure */
    }
    int a = atoi(argv[1]);              /* argv entries are strings: convert */
    int b = atoi(argv[2]);
    printf("sum = %d\n", a + b);
    return EXIT_SUCCESS;                /* 0 */
}
