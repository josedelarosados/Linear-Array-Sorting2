#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(){

    char *file_path = "list0.bin";
    FILE *File = fopen(file_path, "r");
    if (File == NULL) {
        perror("open");
        exit(1);
    }else{
        printf("File escritura abierto\n");
    }
    
    // int num[10];
    int *b;
    b = malloc(sizeof(int)*10); //40 bytes de memoria en heap

    // fread(&num, sizeof(int), 10, File);
    
    // for (int i=0; i<10; i++){
    //     printf("dato leido: %d\n", num[i]);
    // }

    fread(b, sizeof(int), 10, File);

    printf("%d\n", *b);

    for (int i=0; i<10; i++){
        printf("dato leido: %d\n", b[i]);
    }

    qsort(b, 10, sizeof(int), cmpfunc);

    printf("\n Datos ordenados: \n\n");
    for (int i=0; i<10; i++){
        printf("dato %d: %d\n", i+1, b[i]);
    }

    free(b);

    return 0;
}