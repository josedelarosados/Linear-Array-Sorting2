#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    
    char *file_path = "list_0.bin";
    FILE *File = fopen(file_path, "w");
    if (File == NULL) {
        perror("open");
        exit(1);
    }else{
        printf("Pipe escritura abierto\n");
    }

    int num;

    for(int i=0; i<10; i++){
        // num = rand()%10;
        num=999999;
        fwrite(&num, sizeof(int), 1, File);
        printf("Cadena %d escritan\n", i);
    }
    fclose(File); 


    return 0;

}