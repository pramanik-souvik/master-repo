#include <stdio.h>
#include <string.h>
#define MAX 5

int main() {
    char stack[MAX][100];
    int top = -1;

    strcpy(stack[++top], "Numb");
    strcpy(stack[++top], "In The End");
    strcpy(stack[++top], "Crawling");

    printf("Songs added to the stack playlist 🎶\n");
    for (int i = 0; i <= top; i++) {
        printf("%d. %s\n", i + 1, stack[i]);
    }

    printf("\nPlaying songs (LIFO order):\n");
    while (top >= 0) {
        printf("Now Playing: %s\n", stack[top--]);
    }

    return 0;
}