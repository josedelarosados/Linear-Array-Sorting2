#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void* a, const void* b){
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

void minor_list(int *a, int *b, int n, int *x){
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
  
void major_list(int *a, int *b, int n, int *x){
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

int main(int argc, char** argv){

    if (argc != 10){
        printf("Faltan argumentos: [rl] [wl] [wr] [rr] [file] [pid] [n] [flag] [p]\n");
        exit(1);
    } 

    int pid, n, f, p;
    char *path_rlfifo = argv[1]; //Paths de pipes
    char *path_wlfifo = argv[2];
    char *path_wrfifo = argv[3];
    char *path_rrfifo = argv[4];
    char *path_file   = argv[5]; //path de archivo inicial
    sscanf(argv[6], "%d", &pid); 
    sscanf(argv[7], "%d", &n); // tamaño de lista de numeros inicial
    sscanf(argv[8], "%d", &p); // T(p) = p
    sscanf(argv[9], "%d", &f); // Bandera de mensajes
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
    int *datos_ordenados;
    datos = (int *)malloc(sizeof(int)*n);
    datos_ordenados = (int *)malloc(sizeof(int)*n);

    fread(datos, sizeof(int), n, file);
    qsort(datos, n, sizeof(int), compare_ints);
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

    for (int step=0; step<p; step++){
        if (step%2 == 0){
            if (parity == 0){
                fwrite(datos, sizeof(int), n, wrpFile);
                fread(datos_recibidos, sizeof(int), n, rrpFile);
                minor_list(datos, datos_recibidos, n, datos_ordenados);
            } else {
                fread(datos_recibidos, sizeof(int), n, rlpFile);
                fwrite(datos, sizeof(int), n, wlpFile);
                major_list(datos, datos_recibidos, n, datos_ordenados);
            }
        } else {
            if (parity == 0){
                fread(datos_recibidos, sizeof(int), n, rlpFile);
                fwrite(datos, sizeof(int), n, wlpFile);
                major_list(datos, datos_recibidos, n, datos_ordenados);
            } else {
                fwrite(datos, sizeof(int), n, wrpFile);
                fread(datos_recibidos, sizeof(int), n, rrpFile);
                minor_list(datos, datos_recibidos, n, datos_ordenados);
            }
        }
        for (int i=0; i<n; i++){
            datos[i]=datos_ordenados[i];
        }
    }

        if (f){
            for (int i=0; i<n; i++){
                // printf("dato %d en pid %d: %d\n", i+1, pid, datos[i]);
                printf("dato %d en pid %d: %d\n", i+1, pid, datos[i]);
            }
            printf("\n");
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