#include <stdio.h>

int main() {
    FILE *fp = fopen("test.txt", "w");
    if(fp == NULL){ perror("File opening failed"); return 1; }
    fprintf(fp, "Hello, World!\nI am Souvik and I am learning C.");
    fclose(fp);

    char buffer[50];
    fp = fopen("test.txt", "r");
    if(fp == NULL){ perror("File opening failed"); return 1; }
    
    printf("Read from file:\n");
    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
    return 0;
}