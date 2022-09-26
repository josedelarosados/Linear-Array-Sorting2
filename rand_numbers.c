#include <stdio.h>  
#include <stdlib.h>  
  
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
    int i;
    FILE *File = fopen(path, "w");
 
    for (i = 0; i <n; i++){
        fprintf(File, "%d\n", (rand()%max)+min);
     }   
     return 0;  
}  