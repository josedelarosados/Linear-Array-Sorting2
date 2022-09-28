#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
  
int main(int argc, char** argv)  
{
    if (argc != 5){
        printf("Faltan argumentos: [path] [max] [min] [n]\n");
        exit(1);
    } 

    int max, min, n;
    char *path = argv[1];
    sscanf(argv[2], "%d", &max); 
    sscanf(argv[3], "%d", &min);
    sscanf(argv[4], "%d", &n);

    FILE *File = fopen(path, "w");

    int num=0;
    srand(time(NULL));
    for (int i = 0; i <n; i++){
        // fprintf(File, "%d\n", (rand()%(max-min+1))+min);
        num = (rand()%(max-min+1))+min;
        fwrite(&num, sizeof(int), 1, File);
     }   
     return 0;  
}  