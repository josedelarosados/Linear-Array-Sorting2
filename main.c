#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char** argv){

    if (argc != 9){
        printf("Faltan argumentos: [Pie rl] [Pipe wl] [Pipe wr] [Pipe rr] [file] [pid] [n] [flag]\n");
        exit(1);
    } 

    int pid, n, f;
    char *path_rlfifo = argv[1]; //Paths de pipes
    char *path_wlfifo = argv[2];
    char *path_wrfifo = argv[3];
    char *path_rrfifo = argv[4];
    char *path_file   = argv[5]; //path de archivo inicial
    sscanf(argv[6], "%d", &pid); 
    sscanf(argv[7], "%d", &n); //tamaño de lista de numeros inicial
    sscanf(argv[8], "%d", &f); // Bandera de mensajes
    FILE *rlpFile;
    FILE *wlpFile;
    FILE *wrpFile;
    FILE *rrpFile;

    int parity = pid%2;
    //printf("Paridad en pid %d: %d\n", pid, parity);
    if (parity == 0){
        rlpFile = fopen(path_rlfifo, "r");
        wlpFile = fopen(path_wlfifo, "w");
        wrpFile = fopen(path_wrfifo, "w");
        rrpFile = fopen(path_rrfifo, "r");
    } else {
        wrpFile = fopen(path_wrfifo, "w");
        rrpFile = fopen(path_rrfifo, "r");
        rlpFile = fopen(path_rlfifo, "r");
        wlpFile = fopen(path_wlfifo, "w");
    }

    FILE *file = fopen(path_file, "r");
    if (file == NULL || rlpFile == NULL || wlpFile == NULL || wrpFile == NULL || rrpFile == NULL ) {
        perror("open");
        exit(1);
    }

    int *datos;
    datos = malloc(sizeof(int)*n);
    fread(datos, sizeof(int), n, file);
    qsort(datos, n, sizeof(int), cmpfunc);
    // printf("\n Datos ordenados en pid %d: \n\n", pid);
    // for (int i=0; i<n; i++){
    //     printf("dato %d: %d\n", i+1, datos[i]);
    // }

    int *datos_recibidos;
    datos_recibidos = malloc(sizeof(int)*n);
    setbuf(rlpFile, NULL);
    setbuf(wrpFile, NULL);
    setbuf(wlpFile, NULL);
    setbuf(rrpFile, NULL);

    if (parity == 0){
        fread(datos_recibidos, sizeof(int), n, rlpFile);
        // fwrite(datos, sizeof(int), n, wlpFile);
    } else {
        fwrite(datos, sizeof(int), n, wrpFile);
        // fread(datos_recibidos, sizeof(int), n, rrpFile);
    }

    if (f){
        printf("\n Datos recibidos en pid %d: \n\n", pid);
        for (int i=0; i<n; i++){
            printf("dato %d: %d\n", i+1, datos_recibidos[i]);
        }
    }

    fclose(rlpFile);
    fclose(wlpFile);
    fclose(wrpFile);
    fclose(rrpFile);
    fclose(file);
    free(datos);
    free(datos_recibidos);

    return 0;
}