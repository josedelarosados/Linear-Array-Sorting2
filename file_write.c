#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int main(int argc, char** argv){

    if (argc != 3){
        printf("Faltan argumentos: [n] [f]\n");
        exit(1);
    } 
    int n,f;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &f);

    char *file_path;

    if (f){
        file_path = "list_max.bin";
    }else{
        file_path = "list_min.bin";
    }

    FILE *File = fopen(file_path, "w");
    if (File == NULL) {
        perror("open");
        exit(1);
    }else{
        // printf("Pipe escritura abierto\n");
    }

    int num;
    if (f){
        num=INT_MAX;
    }else{
        num=0;
    }

    for(int i=0; i<n; i++){
        // num = rand()%10;
        fwrite(&num, sizeof(int), 1, File);
        // printf("Cadena %d escritan\n", i);
    }
    fclose(File); 
    return 0;
}