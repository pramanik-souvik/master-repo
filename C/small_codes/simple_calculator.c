#include <stdio.h>

int main(){
    int a,b,op;
    printf("Enter 2 numbers: ");
    scanf("%d %d",&a,&b);
    printf("Op: \n1 - add\n2 - sub \n3 - mul \n4 - div\nSelect Op: ");
    scanf("%d",&op);
    switch(op){
        case 1: printf("%d\n",a+b); break;
        case 2: printf("%d\n",a-b); break;
        case 3: printf("%d\n",a*b); break;
        case 4: printf("%d\n",a/b); break;
        default: printf("Invalid\n");
    }
    return 0;
}