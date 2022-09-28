#include <stdio.h>  
#include <stdlib.h>  

void lista_menor(int *a, int *b, int n, int *x){
    int i_a = 0;
    int i_b = 0;
    for (int i=0; i<n; i++){
        if (a[i_a] <= b[i_b]){
            x[i] = a[i_a];
            i_a = i_a + 1;
        } else {
            x[i] = b[i_b];
            i_b = i_b + 1;
        }
    }
}
  
void lista_mayor(int *a, int *b, int n, int *x){
    int i_a = n-1;
    int i_b = n-1;
    for (int i=0; i<n; i++){
        if (a[i_a] > b[i_b]){
            x[n-i-1] = a[i_a];
            i_a = i_a - 1;
        } else {
            x[n-i-1] = b[i_b];
            i_b = i_b - 1;
        }
    }
}

int main(int argc, char** argv)  
{
    int n = 10;
    
    int *a;
    a = malloc(sizeof(int)*n);

    int *b;
    b = malloc(sizeof(int)*n);

    int *c;
    c = malloc(sizeof(int)*n);

    int arr1[] = {1, 1, 3, 4, 4, 6, 7, 8, 9, 9};
    int arr2[] = {1, 2, 3, 3, 5, 6, 7, 8, 8, 9};

    a = arr1;
    b = arr2;

    // for (int i=0; i<n; i++){
    //     a[i] = rand() % 10;
    //     b[i] = rand() % 10;
    // }

    int i;
    printf("Vector a:\n");
    for (i=0; i<n; i++){
        printf("a[%d]: %d\n", i, a[i]);
        // printf("b[%d]: %d\n", i, b[i]);
    }

    printf("\nVector b:\n");
    for (i=0; i<n; i++){
        // printf("a[%d]: %d\n", i, a[i]);
        printf("b[%d]: %d\n", i, b[i]);
    }

    // int i_a = 0, i_b = 0;
    // for (i=0; i<n; i++){
    //     if (a[i_a] <= b[i_b]){
    //         c[i] = a[i_a];
    //         i_a = i_a + 1;
    //     } else {
    //         c[i] = b[i_b];
    //         i_b = i_b + 1;
    //     }
    // }

    lista_menor(a, b, n, c);

    printf("\nVector guardado:\n");
    for (i=0; i<n; i++){
        // printf("a[%d]: %d\n", i, a[i]);
        printf("c[%d]: %d\n", i, c[i]);
    }

    // Vector mas grande
    // i_a = n-1;
    // i_b = n-1;
    // for (i=0; i<n; i++){
    //     if (a[i_a] > b[i_b]){
    //         c[n-i-1] = a[i_a];
    //         i_a = i_a - 1;
    //     } else {
    //         c[n-i-1] = b[i_b];
    //         i_b = i_b - 1;
    //     }
    // }

    lista_mayor(a, b, n, c);

    printf("\nVector guardado:\n");
    for (i=0; i<n; i++){
        // printf("a[%d]: %d\n", i, a[i]);
        printf("c[%d]: %d\n", i, c[i]);
    }

    free(a);
    free(b);
    free(c);
    return 0;
}  