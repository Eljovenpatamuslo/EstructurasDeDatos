#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "heap.h"
void print_int(void* n){
    printf("%d\n",*(int*)n);
}

void* copy_int(void* n){
    return n;
}

void destr_int(void* n){
    (void) n;
    return;
}

int comp_int(void* n1, void* n2){
    int _n1 = *(int*)n1;
    int _n2 = *(int*)n2;
    return _n1 - _n2;
}

void print_arr(void** arr, int largo) {
    for (int i = 0; i < largo; i++) {
        print_int(arr[i]);
    }
    printf("\n");
}

void test_bheap(){
    // Crear el heap
    BHeap heap = bheap_crear(comp_int, copy_int, destr_int);

    // Insertar 5 elementos
    int valores[] = {8, 42, 23, 15, 16, 5, 13};
    for (int i = 0; i < 7; i++) {
        bheap_insertar(&valores[i], heap);
    }
    
    printf("Recorrido del heap:\n");
    bheap_recorrer(print_int, heap);
    printf("\n");
    
    printf("Extrayendo elementos del heap (en orden):\n");
    while (!bheap_es_vacio(heap)) {
        int* max = (int*)bheap_pop(heap);
        printf("%d ", *max);
    }
    printf("\n");

    // Destruir heap
    bheap_destruir(heap);
}

void test_heapsort(int n){
    void** arr = malloc(sizeof(void*) * n);
    assert(arr);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(int));
        *(int*)arr[i] = rand() % (n + 1); 
    }
    
    printf("Arreglo original:\n");
    print_arr(arr, n);

    heapSort(arr, n, comp_int);

    printf("Arreglo ordenado con heapSort:\n");
    print_arr(arr, n);

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

void test_pqueue(){
    // Crear el heap
    PriorityQueue pq = cola_prioridad_crear(comp_int, copy_int, destr_int);

    // Insertar 5 elementos
    int valores[] = {14, 58, 19, 52, 2, 98, 71};
    for (int i = 0; i < 7; i++) {
        cola_prioridad_insertar(&valores[i], pq);
    }
    
    printf("Recorrido de la Priority Queue:\n");
    bheap_recorrer(print_int, pq);
    printf("\n");
    
    printf("Extrayendo elementos de la Queue (en orden):\n");
    while (!cola_prioridad_es_vacia(pq)) {
        int* max = (int*)cola_prioridad_maximo(pq);
        if(max != NULL) printf("%d ", *max);
        cola_prioridad_eliminar_maximo(pq);
    }
    printf("\n");

    // Destruir heap
    cola_prioridad_destruir(pq);
}

int main(int argv, char* argc[]) {

    test_bheap();
    int test_size = atoi(argc[1]); 
    test_heapsort(test_size);
    test_pqueue();
    return 0;
}