#include <stdio.h>
#include <stdlib.h>

int main(){

    char *file_path = "list.bin";
    FILE *File = fopen(file_path, "r");
    if (File == NULL) {
        perror("open");
        exit(1);
    }else{
        printf("File escritura abierto\n");
    }
    
    int num[4];

    fread(&num, sizeof(int), 5, File);
    
    for (int i=0; i<5; i++){
        printf("dato leido: %d\n", num[i]);
    }

    printf("%d\n",sizeof(num[0]));
    fclose(File);

    return 0;
}