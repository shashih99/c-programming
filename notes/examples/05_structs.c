/* 05_structs.c - define, init, access (. and ->), typedef, nesting, arrays, pass/return */
#include <stdio.h>
#include <string.h>

struct Point {                  /* struct tag "Point" */
    int x;
    int y;
};

typedef struct {                /* typedef: use "Student" instead of "struct ..." */
    int id;
    char name[20];
    float gpa;
    struct Point home;          /* nested struct */
} Student;

void print_student(const Student *s)          /* pass by pointer: no copy */
{
    printf("  #%d %-6s gpa=%.1f home=(%d,%d)\n",
           s->id, s->name, s->gpa, s->home.x, s->home.y);
}

void raise_gpa(Student *s, float by) { s->gpa += by; }

struct Point midpoint(struct Point a, struct Point b)   /* pass & return by value */
{
    struct Point m = { (a.x + b.x) / 2, (a.y + b.y) / 2 };
    return m;
}

int main(void)
{
    struct Point p1 = {1, 2};                   /* positional init */
    struct Point p2 = {.y = 10, .x = 6};        /* designated init (C99) */
    printf("p1 = (%d, %d), p2 = (%d, %d)\n", p1.x, p1.y, p2.x, p2.y);

    struct Point m = midpoint(p1, p2);
    printf("midpoint = (%d, %d)\n", m.x, m.y);

    struct Point copy = p1;                     /* struct assignment copies all members */
    copy.x = 99;
    printf("p1.x = %d, copy.x = %d (independent copies)\n", p1.x, copy.x);

    Student s = {1, "Asha", 8.2f, {3, 4}};
    Student *ps = &s;
    printf("s.name = %s, ps->name = %s, (*ps).name = %s\n", s.name, ps->name, (*ps).name);

    raise_gpa(&s, 0.5f);
    strcpy(s.name, "Asha K");                   /* arrays inside structs: use strcpy */

    Student cls[] = {
        s,
        {2, "Ravi", 7.4f, {0, 0}},
        {.id = 3, .name = "Meena", .gpa = 9.1f},   /* unlisted members -> 0 */
    };
    int n = sizeof cls / sizeof cls[0];
    printf("class of %d:\n", n);
    for (int i = 0; i < n; i++)
        print_student(&cls[i]);

    printf("sizeof(struct Point) = %zu, sizeof(Student) = %zu\n",
           sizeof(struct Point), sizeof(Student));
    return 0;
}
