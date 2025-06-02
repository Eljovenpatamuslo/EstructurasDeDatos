#include "heap.h"

int comparadora(const void* dato1,const void* dato2){
    int data1 = *((int*)dato1);
    int data2 = *((int*)dato2);
    if(data1 > data2) return 1;
    if(data1 < data2) return -1;
    else return 0;
}

int comparadora_evil(const void* dato1,const void* dato2){
    int data1 = *((int*)dato1);
    int data2 = *((int*)dato2);
    if(data1 < data2) return 1;
    if(data1 > data2) return -1;
    else return 0;
}


void imprimir_entero(void* dato){
    printf("%i",*((int*)dato));
} 

static void *copiar_int(void* dato){
  int *copia = malloc(sizeof(int));
  *copia = *((int *) dato);
  return copia; 
}

int main(){
    int dato;
    dato = 1;
    BHeap arbol = bheap_crear(10,comparadora);
    arbol = bheap_insertar(arbol, &dato);
    int dato1 = 2;
    arbol = bheap_insertar(arbol, &dato1);
    int dato2 = 3;
    arbol = bheap_insertar(arbol, &dato2);
    int dato3 = 4;
    arbol = bheap_insertar(arbol, &dato3);
    int dato4 = 5;
    arbol = bheap_insertar(arbol, &dato4);

    //arbol = bheap_eliminar(arbol,&dato3);
    void* arr[4];
    arr[0] = &dato;
    arr[1] = &dato1;
    arr[2] = &dato2;
    arr[3] = &dato3;
    bheap_recorrer(arbol,imprimir_entero);
    BHeap arbol2 = bheap_crear_desde_arr(arr,4,copiar_int,comparadora_evil);
    bheap_recorrer(arbol2,imprimir_entero);
    return 0;
}