#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 10;

    int *p = &x;
    printf("Value of x: %d\n", x);

    printf("Pointer p points to: %p\n", (void*)p);
    printf("Value via pointer: %d\n", *p);

    *p = 20;
    printf("New value of x: %d\n", x);

    return 0;
}