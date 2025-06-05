#include <stdio.h>
#include <stdlib.h>

typedef int (*FuncionComparadora)(void *dato1,void *dato2);



void insertion_sort(void** arr, int length, FuncionComparadora comp){
    for (int i = 1; i < length;i++) {
        int* aux = arr[i];
        int j = i - 1;

        // Mueve los elementos de arr[0..i-1], que son más grandes que el dato, una posicion adelante
        while (j >= 0 && comp(arr[j],aux)) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = aux;
    }
}

int comp_int(void* dato1, void* dato2){
    return *((int*)dato1) > *((int*)dato2);
}

void print_int(void* dato){
    printf("%i\n", *((int*)dato));
}

int main(){
    void* arr[6];
    for(int i=0 ; i<6; i++){
        int* valor = malloc(sizeof(int));
        *valor = rand()%100;
        arr[i] = valor;
    }
    for(int i = 0; i<6; i++){
        print_int(arr[i]);
    }

    insertion_sort(arr,6,comp_int);
    printf("\nordenado:\n");
    for(int i = 0; i<6; i++){
        print_int(arr[i]);
        free(arr[i]);
    }
}