#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[50];
    struct Node* next;
} Node;

void printList(Node* head) {
    while (head) {
        printf("%s ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = malloc(sizeof(Node));
    strcpy(head->data, "Hello");

    head->next = malloc(sizeof(Node));
    strcpy(head->next->data, "World");
    head->next->next = NULL;

    printList(head);

    return 0;
}