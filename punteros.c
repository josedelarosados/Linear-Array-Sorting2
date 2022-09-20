#include <stdio.h>

int main(){
int *a; //puntero                                                            
int m[50];


a = &m[0]; //& direccion       
printf("Direcion de a: %p\n", &a);
printf("Direcion de m[0]: %p\n", &m[0]);

m[0] = 4;
printf("%d\n", *a); //* indireccion                                           

m[0] = 883;
printf("%d\n", *a); //cambia dinamicamente, la direccion es fija              

*a = 999; //accediendo al valor                                                
printf("%d\n", *a);
printf("%d\n", m[0]);

// UN PUNTERO ES UNA VARIABLE QUE CONTIENE LA DIRECCION DE OTRA VARIABLE

// TIPO * IDENTIFICADOR
// TAMBIEN:
// * : ACCESO AL ELEMENTO
// & : OBTENCION DE LA DIRECCION

}
