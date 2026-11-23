/* 01_control.c - if/else, switch, loops, break/continue */
#include <stdio.h>

int main(void)
{
    int marks = 72;
    if (marks >= 90)      printf("Grade A\n");
    else if (marks >= 70) printf("Grade B\n");
    else                  printf("Grade C\n");

    int day = 3;
    switch (day) {
    case 1:  printf("Mon\n"); break;
    case 2:  printf("Tue\n"); break;
    case 3:  printf("Wed\n");          /* no break here... */
             /* fall through */
    case 4:  printf("Thu (fell through)\n"); break;
    default: printf("Other\n");
    }

    printf("for:      ");
    for (int i = 1; i <= 5; i++) printf("%d ", i);
    printf("\n");

    printf("while:    ");
    int n = 5;
    while (n > 0) printf("%d ", n--);
    printf("\n");

    printf("do-while: ");
    int k = 10;
    do { printf("%d ", k); } while (k < 5);  /* body runs once even though condition is false */
    printf("\n");

    printf("odd < 10, stop at 7: ");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;   /* skip evens */
        if (i > 7) break;           /* leave loop */
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
