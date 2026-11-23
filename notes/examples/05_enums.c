/* 05_enums.c - enum values, explicit values, switch, flags */
#include <stdio.h>

enum Color { RED, GREEN, BLUE };                  /* 0, 1, 2 */
enum Level { LOW = 10, MEDIUM = 20, HIGH };       /* HIGH = 21 */
typedef enum { MON = 1, TUE, WED, THU, FRI, SAT, SUN, DAY_COUNT = 7 } Day;

enum Perm {                                       /* bit flags */
    PERM_READ  = 1 << 0,                          /* 1 */
    PERM_WRITE = 1 << 1,                          /* 2 */
    PERM_EXEC  = 1 << 2,                          /* 4 */
};

const char *color_name(enum Color c)
{
    switch (c) {                                  /* -Wall warns if a case is missing */
    case RED:   return "red";
    case GREEN: return "green";
    case BLUE:  return "blue";
    }
    return "?";
}

int main(void)
{
    printf("RED=%d GREEN=%d BLUE=%d\n", RED, GREEN, BLUE);
    printf("LOW=%d MEDIUM=%d HIGH=%d\n", LOW, MEDIUM, HIGH);

    for (enum Color c = RED; c <= BLUE; c++)
        printf("color %d = %s\n", c, color_name(c));

    Day d = WED;
    printf("WED = %d, weekend? %s\n", d, (d == SAT || d == SUN) ? "yes" : "no");

    int perms = PERM_READ | PERM_WRITE;           /* combine */
    printf("perms = %d, can write? %s, can exec? %s\n", perms,
           (perms & PERM_WRITE) ? "yes" : "no",
           (perms & PERM_EXEC) ? "yes" : "no");
    perms &= ~PERM_WRITE;                         /* remove */
    printf("after removing write: perms = %d\n", perms);

    printf("sizeof(enum Color) = %zu\n", sizeof(enum Color));
    return 0;
}
