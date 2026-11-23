/* 01_io.c - basic input/output with scanf/printf */
#include <stdio.h>

int main(void)
{
    int age;
    float height;
    char name[32];

    printf("Enter name, age and height: ");
    if (scanf("%31s %d %f", name, &age, &height) != 3) {   /* check how many items were read */
        printf("Invalid input\n");
        return 1;
    }
    printf("Name: %s | Age: %d | Height: %.2f\n", name, age, height);
    return 0;
}
