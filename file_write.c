#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    
    char *file_path = "list.bin";
    FILE *File = fopen(file_path, "w");
    if (File == NULL) {
        perror("open");
        exit(1);
    }else{
        printf("Pipe escritura abierto\n");
    }

    for(int i=0; i<5; i++){
        fwrite(&i, sizeof(int), 1, File);
        printf("Cadena %d escrita en FIFO\n", i);
    }
    fclose(File); 


    return 0;

}