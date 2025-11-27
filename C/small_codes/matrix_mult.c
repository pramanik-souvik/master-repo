#include <stdio.h>

int main(){
    int a[2][2]={{1,2},{3,4}}, 
        b[2][2]={{5,6},{7,8}}, 
        c[2][2]={0};

    // Multiply matrices
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                c[i][j]+=a[i][k]*b[k][j];

    // Print matrix A
    printf("Matrix A:\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++) printf("%d ", a[i][j]);
        printf("\n");
    }

    // Print matrix B
    printf("\nMatrix B:\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++) printf("%d ", b[i][j]);
        printf("\n");
    }

    printf("\nMatrix C will be the Multiplication of the Matrix A and Matrix B...\n");
    // Print matrix C (result)
    printf("\nMatrix C = (A x B):\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++) printf("%d ", c[i][j]);
        printf("\n");
    }

    return 0;
}