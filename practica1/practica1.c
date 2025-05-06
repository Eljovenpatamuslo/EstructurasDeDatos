#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

typedef struct {
    int* direccion;
    int capacidad;
} ArregloEnteros;

void bubble_sort(float arreglo[], int longitud) {
    for (int iter = 0 ; iter < longitud - 1 ; iter++) {
        for (int i = 0 ; i < longitud - iter - 1; i++) {
            if (arreglo[i] > arreglo[i + 1]) {
                float aux = arreglo[i];
                arreglo[i] = arreglo[i + 1];
                arreglo[i + 1] = aux;
            }
        }
    }
}

float mediana(float *arreglo, int longitud){
    if(longitud % 2 != 0) return arreglo[(longitud/2)];
    float medianaPar = (arreglo[longitud / 2] + arreglo[(longitud / 2) - 1]) / 2;
    return medianaPar;
}

int string_len(char* str){
    int longitud = 0;
    for(; str[longitud] != '\0'; longitud++);
    return longitud;
}

void string_reverse(char* str){
    
    for(int i = (string_len(str) - 1), x = 0; i > x ; i--, x++){
        char aux = str[x];
        str[x] = str[i];
        str[i] = aux;
    }
}

int string_concat(char* str1, char* str2, int max){
    int longitudOriginal = string_len(str1);
    int i = 0;
    for(; str2[i] != '\0' && i < max;i++){
        str1[i + longitudOriginal] = str2[i]; 
    }
    str1[i + longitudOriginal] = '\0';
    return i;
}

int string_compare(char* str1, char* str2){
    if(string_len(str1) > string_len(str2)) return 1;
    if(string_len(str1) < string_len(str2)) return -1;
    int mayor = 0,menor = 0;
    for(int i = 0; str1[i] != '\0' && !mayor && !menor; i++){
        if(str1[i] > str2[i]){
            mayor = 1;
        }else if (str1[i] < str2[i]){
           menor = 1;
        }
    }
    if(mayor) return 1;
    if(menor) return -1;
    return 0;
}

int string_subcadena(char* str1, char* str2){
    int longitudStr2 = string_len(str2);
    int coincidir = 0;
    int terminar = 0;
    int i=0;
    for(; str1[i] != '\0' && coincidir != longitudStr2;i++){
        terminar = 0;
        for(int x = 0; str2[x] != '\0' && !terminar; x++){
            if(str1[i] == str2[x]){
                coincidir++;
                terminar = 1;
            }
        }
        if(!terminar) coincidir = 0;
    }
    if(coincidir == longitudStr2) return i-longitudStr2;
    return -1;
}

void string_unir(char* arregloStrings[], int n, char* sep, char* res){
    int sizeSep = string_len(sep);
    res[0] = '\0';
    string_concat(res,arregloStrings[0],sizeof(arregloStrings[0]));
    for(int i = 1;i < n; i++){
        string_concat(res,sep,sizeSep);
        string_concat(res,arregloStrings[i],sizeof(arregloStrings[i]));
    }
}


int main(){
    /*int size = -1;
    printf("Ingrese el tamaño del arreglo\n");
    scanf("%i",&size);
    float* arreglo = malloc(sizeof(float) * size);
    for(int i = 0; i < size; i++){
        scanf("%f",&arreglo[i]);
    }
    bubble_sort(arreglo,size);
    for(int i = 0; i < size; i++){
        printf("%f\n",arreglo[i]);
    }

    printf("La mediana del arreglo ingresado es: %f",mediana(arreglo,size));
*/
    /*char* str1 = malloc(sizeof(char) * 10);
    str1[0] = 'a';
    str1[1] = 'b';
    str1[2] = 'c';
    str1[3] = 'd';
    str1[4] = '\0';

    char* str2 = malloc(sizeof(char) * 5);
    str2[0] = 'c';
    str2[1] = 'd';
    str2[2] = '\0';
    printf("%i\n",string_len(str1));
    //string_reverse(str1);
    printf("%s\n",str1);
    //printf("%i\n",string_concat(str1,str2,string_len(str2)-1));
    printf("%s\n",str1);
    //printf("%i\n",string_compare(str2,str1));
    printf("%i\n",string_subcadena(str1,str2));
    char* arregloStrings[] = {"hola","pata"};
    char* res = malloc(sizeof(char)*100);
    string_unir(arregloStrings,2," so ",res);
    printf("%s",res);*/
    
    //printf("%i",string_subcadena("atas","batatas"));
    Matriz* matrix = matriz_crear(4,4);
    matriz_escribir(matrix,1,1,2.5);
    matriz_escribir(matrix,2,1,3.5);
    //printf("%li",matrix->numFilas);
    matrix = matriz_insertar_fila(matrix,2);
    /*for(int i = 0;i<matrix->numFilas;i++){
        for(int j = 0;j<matrix->numColumnas;j++){
            printf("%.2f ",matrix->filCol[i][j]);
        }
        printf("\n");
    }
    matriz_destruir(matrix);*/
    return 0;
}