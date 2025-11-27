#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char song[100];
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front; 
    Node* rear;
} Queue;


void enqueue(Queue* q, const char* name){
    Node* n = malloc(sizeof(Node));
    strcpy(n->song, name);
    n->next = NULL;

    if(q->rear) 
        q->rear->next = n;
    else 
        q->front = n;
    
    q->rear = n;
}


void printPlaylist(Queue* q){
    Node* curr = q->front;
    printf("\nPlaylist:\n");
    while(curr){ 
        printf("%s\n", curr->song);
        curr = curr->next;
    }
}

int main(){
    Queue q = {NULL,NULL};

    enqueue(&q, "Numb");
    enqueue(&q, "In The End");
    enqueue(&q, "Crawling");

    printPlaylist(&q);

    return 0;
}
