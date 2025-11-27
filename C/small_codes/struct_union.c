#include <stdio.h>
#include <string.h>

struct Point { 
    int x;
    int y; 
};

union Data { 
    int score; 
    float health; 
    char name[20]; 
};

int main() {

    struct Point player = {5, 7};
    printf("Player starting at position: (%d, %d)\n", player.x, player.y);

    union Data d;

    strcpy(d.name, "Neymar");
    printf("Player Name: %s\n", d.name);

    d.score = 150;
    printf("Player Score: %d\n", d.score);

    d.health = 87.5;
    printf("Player Health: %.1f%%\n", d.health);

    player.x += 3;
    player.y -= 2;
    printf("Player moved to: (%d, %d)\n", player.x, player.y);

    return 0;
}